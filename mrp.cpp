#include <bits/stdc++.h>
#include "mrp.h"
using namespace std;

MRP::MRP(const string &sym1, const string &sym2, int max_pos, int look_back, double thresh, double stop_loss_thresh)

{
    symbol1 = sym1;
    symbol2 = sym2;
    max_position = max_pos;
    lookback_period = look_back;
    threshold = thresh;
    stop_loss_threshold = stop_loss_thresh;
    data.read_pairs(symbol1, symbol2);
}

double MRP::spread(int day)
{
    return data.price1[day] - data.price2[day];
}

void MRP::precompute()
{

    for (int i = 0; i < data.size(); i++)
    {
        if (i == 0)
        {
            prefix_sum.push_back(spread(i));
            prefix_square_sum.push_back(spread(i) * spread(i));
        }
        else
        {
            prefix_sum.push_back(prefix_sum[i - 1] + spread(i));
            prefix_square_sum.push_back(prefix_square_sum[i - 1] + spread(i) * spread(i));
        }
    }
}

double MRP::rolling_mean(int day)
{
    double mean = (prefix_sum[day] - prefix_sum[day - lookback_period]) / (double)lookback_period;
    return mean;
}

double MRP::rolling_sd(int day)
{
    double mean = rolling_mean(day);
    double sd = sqrt((prefix_square_sum[day] - prefix_square_sum[day - lookback_period]) / ((double)lookback_period) - mean * mean);
    return sd;
}

double MRP::z_score(int day)
{
    double zscore = (spread(day) - rolling_mean(day)) / rolling_sd(day);
    return zscore;
}

double MRP::z_score_check(int today, int day)
{
    double zscore = (spread(today) - rolling_mean(day)) / rolling_sd(day);
    return zscore;
}

void MRP::run_basic()
{
    precompute();

    for (int day = lookback_period; day < data.size(); day++)
    {

        if (z_score(day) > threshold)
        {
            if (abs(position - 1) <= max_position)
            {
                Order order1(data.date[day], "SELL", data.price1[day], 1);
                Order order2(data.date[day], "BUY", data.price2[day], 1);
                orders1.push_back(order1);
                orders2.push_back(order2);
                cash += data.price1[day] - data.price2[day];
                position--;
            }
        }
        else if (z_score(day) < -threshold)
        {
            if (abs(position + 1) <= max_position)
            {
                Order order1(data.date[day], "BUY", data.price1[day], 1);
                Order order2(data.date[day], "SELL", data.price2[day], 1);
                orders1.push_back(order1);
                orders2.push_back(order2);
                cash += data.price2[day] - data.price1[day];
                position++;
            }
        }
        daily_cashflow.push_back(cash);
        dates.push_back(data.date[day]);
    }

    square_off();
}

void MRP::run_stop_loss()
{

    precompute();

    for (int day = lookback_period; day < data.size(); day++)
    {
   
        int today_shares = 0;
        if (z_score(day) > threshold)
        {
            if (abs(position - 1) <= max_position)
            {
                today_shares = -1;
            }
        }
        else if (z_score(day) < -threshold)
        {
            if (abs(position + 1) <= max_position)
            {
                today_shares = 1;
            }
        }

        for (int i = 0; i < orders1.size(); i++)
        {
            if (!stock_done[i])
            {
                if (orders1[i].direction == "BUY")
                {
                    if (z_score_check(day, days[i]) > stop_loss_threshold)
                    {
                        today_shares = -orders1[i].quantity;
                    }
                    stock_done[i] = true;
                }
                else
                {
                    if (z_score_check(day, days[i]) < -stop_loss_threshold)
                    {
                        today_shares = orders1[i].quantity;
                    }
                    stock_done[i] = true;
                }
            }
        }

            if (today_shares > 0)
            {
                Order order1(data.date[day], "BUY", data.price1[day], today_shares);
                Order order2(data.date[day], "SELL", data.price2[day], today_shares);
                orders1.push_back(order1);
                orders2.push_back(order2);
                cash += today_shares * (data.price2[day] - data.price1[day]);
                position += today_shares;
            }
            else if (today_shares < 0)
            {
                Order order1(data.date[day], "SELL", data.price1[day], -today_shares);
                Order order2(data.date[day], "BUY", data.price2[day], -today_shares);
                orders1.push_back(order1);
                orders2.push_back(order2);
                cash += today_shares * (data.price2[day] - data.price1[day]);
                position += today_shares;
            }
            daily_cashflow.push_back(cash);
            dates.push_back(data.date[day]);
            stock_done.push_back(false);
            days.push_back(day);
        

    }

        square_off();
}

void MRP::write_daily_cashflow()
{
    ofstream file("daily_cashflow.csv");
    file << "Date,Cashflow\n";
    for (int i = 0; i < dates.size(); i++)
    {
        file << dates[i] << "," << fixed << setprecision(2) << daily_cashflow[i] << "\n";
    }
    file.close();
}

void MRP::write_order_statistics()
{
    ofstream file1("order_statistics_1.csv");
    ofstream file2("order_statistics_2.csv");
    file1 << "Date,Order_dir,Quantity,Price\n";
    file2 <<  "Date,Order_dir,Quantity,Price\n";

    for (int i = 0; i < orders1.size(); i++)
    {
        file1 << orders1[i].date << "," << orders1[i].direction <<"," << orders1[i].quantity<<"," << fixed << setprecision(2) << orders1[i].price  << "\n";
    }
    for (int i = 0; i < orders2.size(); i++)
    {
        file2 << orders2[i].date << "," << orders2[i].direction <<"," << orders2[i].quantity<<"," << fixed << setprecision(2) << orders2[i].price  << "\n";
    }
    file1.close();
    file2.close();
}

void MRP::write_final_pnl()
{
    ofstream file("final_pnl.txt");
    file << fixed << setprecision(2) << cash << "\n";
    file.close();
}

void MRP::write()
{

    write_daily_cashflow();
    write_order_statistics();
    write_final_pnl();
}

void MRP::square_off()
{
    int end_day = data.date.size() - 1;
    int remaining_shares = 0;
    for (auto order : orders1)
    {
        if (order.direction == "BUY")
        {
            remaining_shares += order.quantity;
        }
        else
        {
            remaining_shares -= order.quantity;
        }
    }
    cash += (data.price1[end_day] - data.price2[end_day]) * remaining_shares;
    cout << "Final PnL: " << cash << endl;
}

// make two different ordeer statistics file for both the stocks
