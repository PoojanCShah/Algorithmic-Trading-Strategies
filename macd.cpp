
#include <iostream>
#include <bits/stdc++.h>
#include "macd.h"

using namespace std;

MACD::MACD(const string &symbol, double max_position)
{
    this->symbol = symbol;
    this->max_position = max_position;
    past_days = 0;
    data.read_data(symbol, "MACD", 0);
}



void MACD::precompute()
{
    const double ALPHA_LONG = 2.0/27.0;
    const double ALPHA_SHORT = 2.0/13.0;
    const double ALPHA_SIGNAL = 2.0/10.0;

    long_ewm.resize(data.close.size());
    short_ewm.resize(data.close.size());
    macd.resize(data.close.size());
    signal.resize(data.close.size());

    long_ewm[0] = data.close[0];
    short_ewm[0] = data.close[0];
    macd[0] = 0;

    for (int i = 1; i < data.close.size(); i++)
    {
        long_ewm[i] = ALPHA_LONG * data.close[i] + (1 - ALPHA_LONG) * long_ewm[i - 1];
        short_ewm[i] = ALPHA_SHORT * data.close[i] + (1 - ALPHA_SHORT) * short_ewm[i - 1];
        macd[i] = short_ewm[i] - long_ewm[i];
    }

    signal[0] = 0;
    for (int i = 1; i < data.close.size(); i++)
    {
        signal[i] = ALPHA_SIGNAL * macd[i] + (1 - ALPHA_SIGNAL) * signal[i - 1];
    }
}

int MACD::if_buy_sell(int day)
{
    double macd_value = macd[day];


    double signal_value = signal[day];
    if (macd_value > signal_value)
    {
        return 1;
    }
    if (macd_value < signal_value)
    {
        return -1;
    }
    return 0;
}