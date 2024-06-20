#include <bits/stdc++.h>
#include "stockdata.cpp"
#include "strategy.cpp"
#include "order.cpp"
// Strategies
#include "mrp.cpp"
using namespace std;

int main(int argc, char **argv)
{
    // ./main $(symbol1) $(symbol2) $(n) $(x) $(threshold) $(stop_loss_threshold)
    if (argc != 7)
    {
        cout << "Usage: ./main $(strategy) $(symbol1) $(symbol2) ${start_date} ${end_date} $(n) $(threshold)" << endl;
        return 1;
    }
    cout << "Strategy: MRP Started..." << endl;
    string symbol1 = argv[1];
    string symbol2 = argv[2];
    int n = stoi(argv[3]);
    int x = stoi(argv[4]);
    double threshold = stod(argv[5]);
    double stop_loss_threshold = stod(argv[6]);

    MRP strat(symbol1, symbol2, x, n, threshold, stop_loss_threshold);
    
    if (stop_loss_threshold == -1)
    {
        strat.run_basic();
    }
    else
    {
        strat.run_stop_loss();
    }
    strat.write();
    cout<<strat.cash<<endl;
    cout << "Strategy: MRP Ended..." << endl;
    return 0;
}
