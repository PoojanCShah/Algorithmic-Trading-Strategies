#include <iostream>
#include <bits/stdc++.h>
#include "rsi.h"
using namespace std;

RSI::RSI(const string &symbol, int past_days, double max_position, double overbought_threshold, double oversold_threshold)
{
    this->symbol = symbol;
    if (past_days == 0)
    {
        past_days = 14;
    }
    this->past_days = past_days;
    this->max_position = max_position;
    this->overbought_threshold = overbought_threshold;
    this->oversold_threshold = oversold_threshold;
    data.read_data(symbol, "RSI", 0);
}

double RSI::rsi(int day)
{
    double gain = 0;
    double loss = 0;
    for (int i = 0; i < past_days; i++)
    {
        if (data.close[day - i] > data.close[day - i - 1])
        {
            gain += data.close[day - i] - data.close[day - i - 1];
        }
        else
        {
            loss += data.close[day - i - 1] - data.close[day - i];
        }
    }
    return 100.0 * gain / (gain + loss);
}

int RSI::if_buy_sell(int day)
{
    // cout << "rsi_value: " << rsi(day) << endl;
    double rsi_value = rsi(day);
    if (rsi_value <= oversold_threshold)
    {
        return 1;
    }
    if (rsi_value >= overbought_threshold)
    {
        return -1;
    }
    return 0;
}