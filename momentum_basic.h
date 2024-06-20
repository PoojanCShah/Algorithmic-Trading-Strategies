#include <iostream>
#include <bits/stdc++.h>
#include "strategy.h"
using namespace std;

class MomentumBasic : public Strategy
{
public:
    MomentumBasic(const string &symbol, int past_days, double max_position);
    int if_buy_sell(int day);
    void precompute();
    vector<int> count;
};