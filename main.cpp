#include <bits/stdc++.h>
#include <omp.h>
#include "stockdata.cpp"
#include "strategy.cpp"
#include "order.cpp"
// Strategies
#include "momentum_basic.cpp"
#include "macd.cpp"
#include "rsi.cpp"
#include "adx.cpp"
#include "dma.cpp"
#include "dmapp.cpp"
#include "linear_regression.cpp"
#include "matrix.cpp"

using namespace std;

int main(int argc, char **argv)
{
     // ./main $(strategy) $(symbol) ${start_date} ${end_date} $(n) $(x) $(p) $(c1) $(c2) $(max_hold_days) $(oversold_threshold) $(overbought_threshold) $(adx_threshold) $(train_start_date) $(train_end_date)
     if (argc != 16)
     {
          cout << "Usage: ./main $(strategy) $(symbol) ${start_date} ${end_date} $(n) $(x) $(p) $(c1) $(c2) $(max_hold_days) $(oversold_threshold) $(overbought_threshold) $(adx_threshold) $(train_start_date) $(train_end_date)" << endl;
          return 1;
     }
     string strategy = argv[1];
     string symbol = argv[2];
     string start_date = argv[3];
     string end_date = argv[4];
     int n = stoi(argv[5]);
     int x = stoi(argv[6]);
     double p = stod(argv[7]);
     double c1 = stod(argv[8]);
     double c2 = stod(argv[9]);
     int max_hold_days = stoi(argv[10]);
     double oversold_threshold = stod(argv[11]);
     double overbought_threshold = stod(argv[12]);
     double adx_threshold = stod(argv[13]);
     string train_start_date = argv[14];
     string train_end_date = argv[15];

     cout << "Strategy: " << strategy << "Started..." << endl;

     if (strategy == "BASIC")
     {
          MomentumBasic strat(symbol, n, x);
          strat.run();
          strat.write();
     }
     else if (strategy == "DMA")
     {
          DMA strat(symbol, n, x, p);
          strat.run();
          strat.write();
     }
     else if (strategy == "DMA++")
     {
          DMAPP strat(symbol, n, x, p, max_hold_days, c1, c2);
          strat.run();
          strat.write();
     }
     else if (strategy == "MACD")
     {
          MACD strat(symbol, x);
          strat.run();
          strat.write();
     }
     else if (strategy == "RSI")
     {
          RSI strat(symbol, n, x, overbought_threshold, oversold_threshold);
          strat.run();
          strat.write();
     }
     else if (strategy == "ADX")
     {
          ADX strat(symbol, n, x, adx_threshold);
          strat.run();
          strat.write();
     }
     else if (strategy == "LINEAR_REGRESSION")
     {
          LinearRegression strat(symbol, x, p);
          strat.run();
          strat.write();
     }
     else if (strategy == "BEST_OF_ALL")
     {
          MomentumBasic strat1(symbol, n, x);
          DMA strat2(symbol, n, x, p);
          DMAPP strat3(symbol, n, x, p, max_hold_days, c1, c2);
          MACD strat4(symbol, x);
          RSI strat5(symbol, n, x, overbought_threshold, oversold_threshold);
          ADX strat6(symbol, n, x, adx_threshold);
          LinearRegression strat7(symbol, x, p);

#pragma omp parallel sections
          {

#pragma omp section
               {
                    strat1.run();
               }
#pragma omp section
               {
                    strat2.run();
               }
#pragma omp section
               {
                    strat3.run();
               }
#pragma omp section
               {
                    strat4.run();
               }
#pragma omp section
               {
                    strat5.run();
               }
#pragma omp section
               {
                    strat6.run();
               }
#pragma omp section
               {
                    strat7.run();
               }

#pragma omp barrier
               vector<string> name = {"MomentumBasic", "DMA", "DMAPP", "MACD", "RSI", "ADX", "LinearRegression"};
               vector<Strategy> all_strats = {strat1, strat2, strat3, strat4, strat5, strat6, strat7};
               for (int i = 0; i < all_strats.size(); i++)
               {
                    cout << name[i] << " " << all_strats[i].cash << endl;
               }
               Strategy strat_win = *max_element(all_strats.begin(), all_strats.end(), [](Strategy &a, Strategy &b)
                                                 { return a.cash < b.cash; });
               strat_win.write();
          }
     }
     else
     {
          cout << "Invalid strategy" << endl;
          return 1;
     }
     cout << "Strategy: " << strategy << "Ended..." << endl;

     return 0;
}
