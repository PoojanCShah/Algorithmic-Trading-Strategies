#include <bits/stdc++.h>
#include "strategy.h"
using namespace std;

class ADX : public Strategy {
public:
    double adx_threshold;
   int n;
    ADX(string symbol,int n, int max_position, double adx_threshold);

    // double true_range(int day);
    // double dm_plus(int day);
    // double dm_minus(int day);
    // double atr(int day);
    // double di_plus(int day);
    // double di_minus(int day);
    // double dx(int day);
    // double adx(int day);
    int if_buy_sell(int day);

    // make vectors for each of the commented functions
    vector<double> true_range;
    vector<double> dm_plus;
    vector<double> dm_minus;
    vector<double> atr;
    vector<double> di_plus;
    vector<double> di_minus;
    vector<double> dx;
    vector<double> adx;

    void precompute();

    
    };