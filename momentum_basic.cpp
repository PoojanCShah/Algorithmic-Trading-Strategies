#include <iostream>
#include <bits/stdc++.h>
#include "momentum_basic.h"
#include <fstream>
using namespace std;

MomentumBasic::MomentumBasic(const string &symbol, int past_days, double max_position)
{
    this->symbol = symbol;
    this->start_date = start_date;
    this->end_date = end_date;
    this->max_position = max_position;
    data.read_data(symbol, "BASIC", 0);
    if (past_days == 0)
    {
        past_days = 7;
    }
    this->past_days = past_days;
}

void MomentumBasic::precompute()
{
    count.resize(data.close.size());
    int c = 0;
    for (int i = 0; i < past_days; i++)
    {
        if (data.close[i + 1] > data.close[i])
            c++;
        else
            c--;
    }
    for (int i = past_days; i < data.close.size(); i++)
    {
        count[i] = c;
        if (i != data.close.size() - 1)
        {
            if (data.close[i + 1] > data.close[i])
                c++;
            else
                c--;
            if (data.close[i - past_days + 1] > data.close[i - past_days])
                c--;
            else
                c++;
        }
    }
}

int MomentumBasic::if_buy_sell(int day)
{
    if (count[day] == past_days)
    {
        return 1;
    }
    if (count[day] == -past_days)
    {
        return -1;
    }
    return 0;
}