#include <iostream>
#include <bits/stdc++.h>
#include "strategy.h"
using namespace std;

class RSI : public Strategy
{
public:
    RSI(const string &symbol, int past_days, double max_position, double overbought_threshold, double oversold_threshold);
    double overbought_threshold;
    double oversold_threshold;
    double rsi(int day);
    int if_buy_sell(int day);
};