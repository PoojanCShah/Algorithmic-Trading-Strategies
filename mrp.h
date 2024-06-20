#include <bits/stdc++.h>
#include "stockdata.h"
#include "order.h"
using namespace std;
class MRP
{
public:
    MRP(const string &sym1, const string &sym2, int max_pos, int look_back, double thresh, double stop_loss_thresh);

    StockData data;
    string symbol1;
    string symbol2;
    int max_position;
    int lookback_period;
    double threshold;
    double stop_loss_threshold;

    vector<Order> orders1;
    vector<Order> orders2;
    vector<pair<int, int>> strategic_orders; // day and int -1 is sell +1 is buy
    vector<bool> stock_done;
    vector<double> daily_cashflow;
    vector<string> dates;
    vector<int> days;

    double cash = 0;
    int position = 0;

    double spread(int day);
    vector<double> prefix_sum;
    vector<double> prefix_square_sum;
    double z_score_check(int today, int day);

    void precompute();
    double rolling_mean(int day);
    double rolling_sd(int day);
    double z_score(int day);
    void run_basic();
    void run_stop_loss();

    void write_daily_cashflow();
    void write_order_statistics();
    void write_final_pnl();
    void write();

    void square_off();
};