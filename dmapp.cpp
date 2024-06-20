#include "dmapp.h"

DMAPP::DMAPP(const string &symbol, int past_days, double max_position, int sd_threshold, int max_hold_days, double c1, double c2)
{
    this->symbol = symbol;
    this->max_position = max_position;
    this->max_hold_days = max_hold_days;
    if (past_days == 0)
    {
        past_days = 14;
    }
    if (sd_threshold == -1){
        sd_threshold = 5;
    }
    this->past_days = past_days;
    this->sd_threshold = sd_threshold;
    this->c1 = c1;
    this->c2 = c2;
    data.read_data(symbol, "DMA++", 0);
}

void DMAPP::precompute()
{
    vector<double> er(data.size());
    vector<double> sf(data.size());
    ama.resize(data.size());
    double change = 0;
    double abs_change = 0;
    for (int i = 0; i < past_days; i++)
    {
        assert(i + 1 < data.size());
        assert(i >= 0);
        change += data.close[i + 1] - data.close[i];
        abs_change += abs(data.close[i + 1] - data.close[i]);
    }
    for (int i = past_days; i < data.size(); i++)
    {
        er[i] = change / abs_change;
        if (i == past_days)
        {
            sf[i] = 0.5;
            ama[i] = data.close[i];
        }
        else
        {
            double k = er[i] / (c2 + 1.0) * 2.0;
            sf[i] = sf[i - 1] + c1 * ((k - 1) / (k + 1) - sf[i - 1]);
            ama[i] = ama[i - 1] + sf[i] * (data.close[i] - ama[i - 1]);
        }
        if (i != data.size() - 1)
        {
            change += data.close[i + 1] - data.close[i];
            abs_change += abs(data.close[i + 1] - data.close[i]);
            change -= data.close[i - past_days + 1] - data.close[i - past_days];
            abs_change -= abs(data.close[i - past_days + 1] - data.close[i - past_days]);
        }
    }
    // cout << "ER: ";
    // for (int i = 0; i < data.size(); i++)
    // {
    //     cout << er[i] << " ";
    // }
    // cout << endl;
    // cout << "   -------------------" << endl;
    // cout << "SF: ";
    // for (int i = 0; i < data.size(); i++)
    // {
    //     cout << sf[i] << " ";
    // }
    // cout << endl;
    // cout << "   -------------------" << endl;
    // cout << "AMA: ";
    // for (int i = 0; i < data.size(); i++)
    // {
    //     cout << ama[i] << " ";
    // }
    // cout << endl;
}

int DMAPP::if_buy_sell(int day)
{

    double q = (data.close[day] - ama[day]) / (data.close[day]) * 100;
    int p = 0;
    if (q > sd_threshold)
    {
        p = 1;
    }
    if (q < -sd_threshold)
    {
        p = -1;
    }
    if (hold_days.empty()){
        if (p == 1){
            hold_days.push(day);
            long_position = true;
            return 1;
        }
        if (p == -1){
            hold_days.push(day);
            long_position = false;
            return -1;
        }
    }
    else{
        bool to_pop = (day - hold_days.front() >= max_hold_days);
        to_pop |= (long_position && p == -1) || (!long_position && p == 1);
        bool to_push = ((long_position && p == 1) || (!long_position && p == -1)) && (hold_days.size() < max_position || to_pop);
        if (to_pop){
            hold_days.pop();
        }
        if (to_push){
            hold_days.push(day);
        }
        if (to_push && to_pop){
            return 0;
        }
        else if (to_push){
            return long_position ? 1 : -1;
        } 
        else if (to_pop){
            return long_position ? -1 : 1;
        }
    }
    return 0;
}