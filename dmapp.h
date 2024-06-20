#include <bits/stdc++.h>
#include "strategy.h"
using namespace std;

class DMAPP : public Strategy
{
public:
    DMAPP(const string &symbol, int past_days, double max_position, int sd_threshold, int max_hold_days, double c1, double c2);
    int sd_threshold;
    int max_hold_days;
    double c1;
    double c2;
    bool long_position;
    queue<int> hold_days;
    vector<double> ama;
    int if_buy_sell(int day);
    void precompute();
};