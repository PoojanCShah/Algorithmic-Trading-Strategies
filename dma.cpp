#include <iostream>
#include <bits/stdc++.h>
#include "dma.h"
#include <fstream>
using namespace std;

DMA::DMA(const string &symbol, int past_days, double max_position, int sd_threshold)
{
    this->symbol = symbol;
    if (past_days == 0)
    {
        past_days = 50;
    }
    if (sd_threshold == -1){
        sd_threshold = 2;
    }
    this->past_days = past_days;
    this->max_position = max_position;
    this->sd_threshold = sd_threshold;
    data.read_data(symbol, "DMA", 0);
}

void DMA::precompute()
{
    for (int i = 0; i < data.size(); i++)
    {
        if (i == 0)
        {
            prefix_sum.push_back(data.close[i]);
            prefix_square_sum.push_back(data.close[i] * data.close[i]);
        }
        else
        {
            prefix_sum.push_back(prefix_sum[i - 1] + data.close[i]);
            prefix_square_sum.push_back(prefix_square_sum[i - 1] + data.close[i] * data.close[i]);
        }
    }
}

int DMA::if_buy_sell(int day)
{
    double mean = (prefix_sum[day] - prefix_sum[day - past_days]) / past_days;
    double sd = sqrt((prefix_square_sum[day] - prefix_square_sum[day - past_days]) / past_days - mean * mean);
    if (data.close[day] > mean +  sd_threshold * sd)
    {
        return 1;
    }
    if (data.close[day] < mean -  sd_threshold * sd )
    {
        return -1;
    }
    return 0;
}