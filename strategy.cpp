#include <iostream>
#include <bits/stdc++.h>
#include "strategy.h"
#include <fstream>
using namespace std;

Strategy::Strategy()
{
}

void Strategy::precompute()
{
}

void Strategy::run()
{
    precompute();
    for (int day = past_days; day < data.size(); day++)
    {
        int action = if_buy_sell(day);
        if (action == 1)
        {
            if (position < max_position)
            {
                Order order(data.date[day], "BUY", data.close[day], 1);
                cash -= order.price * order.quantity;
                this->orders.push_back(order);
                position++;
            }
        }
        else if (action == -1)
        {
            if (position > -max_position)
            {
                Order order(data.date[day], "SELL", data.close[day], 1);
                cash += order.price * order.quantity;
                this->orders.push_back(order);
                position--;
            }
        }
        daily_cashflow.push_back(cash);
        dates.push_back(data.date[day]);
    }
    square_off();
}

int Strategy::if_buy_sell(int day)
{
    assert(false);
    return 0;
}

void Strategy::square_off()
{
    int end_day = data.date.size() - 1;
    int remaining_shares = 0;
    for (auto order : orders)
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
    cash += data.close[end_day] * remaining_shares;
    cout << "Final PnL: " << cash << endl;
}

void Strategy::write_daily_cashflow()
{
    ofstream file("daily_cashflow.csv");
    file << "Date,Cashflow\n";
    for (int i = 0; i < dates.size(); i++)
    {
        file << dates[i] << "," << fixed << setprecision(2) << daily_cashflow[i] << "\n";
    }
    file.close();
}

void Strategy::write_order_statistics()
{
    ofstream file("order_statistics.csv");
    file << "Date,Order_dir,Quantity,Price\n";
    for (int i = 0; i < orders.size(); i++)
    {
        file << orders[i].date << "," << orders[i].direction << "," << orders[i].quantity << "," << fixed << setprecision(2) << orders[i].price << "\n";
    }
    file.close();
}

void Strategy::write_final_pnl()
{
    ofstream file("final_pnl.txt");
    file << fixed << setprecision(2) << cash << "\n";
    file.close();
}

void Strategy::write()
{

    write_daily_cashflow();
    write_order_statistics();
    write_final_pnl();
}
