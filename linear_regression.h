#include <bits/stdc++.h>
#include "strategy.h"
#include "matrix.h"
using namespace std;

class LinearRegression : public Strategy
{
public:
    LinearRegression(const string &symbol, int max_position, int threshold);
    void precompute();
    int if_buy_sell(int day);
    StockData train_data;
    vector<double> prediction;
    int threshold;
    Matrix beta;
    void train();
};