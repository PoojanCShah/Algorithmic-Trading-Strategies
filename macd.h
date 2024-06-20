#include <iostream>
#include <bits/stdc++.h>
#include "strategy.h"
using namespace std;

class MACD : public Strategy
{
public:
    MACD(const string &symbol, double max_position);

    vector<double> long_ewm;
    vector<double> short_ewm;
    vector<double> macd;
    vector<double> signal;

    void precompute();  
    int if_buy_sell(int day);
};