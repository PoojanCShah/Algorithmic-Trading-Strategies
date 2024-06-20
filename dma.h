#include <iostream>
#include <bits/stdc++.h>
#include "strategy.h"
using namespace std;

class DMA : public Strategy
{
public:
    DMA(const string &symbol, int past_days, double max_position, int sd_threshold);
    int sd_threshold;
    int if_buy_sell(int day);
    vector<double> prefix_sum;
    vector<double> prefix_square_sum;
    void precompute();
};