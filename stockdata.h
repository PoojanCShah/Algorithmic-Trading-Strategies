#pragma once
#include <bits/stdc++.h>
using namespace std;

class StockData
{
    public:
        // DATE,SERIES,OPEN,HIGH,LOW,PREV. CLOSE,LTP,CLOSE,VWAP,52W H,52W L,VOLUME,VALUE,NO OF TRADES,SYMBOL
        const vector<string> COLUMNS = {"DATE", "SERIES", "OPEN", "HIGH", "LOW", "PREV. CLOSE", "LTP", "CLOSE", "VWAP", "52W H", "52W L", "VOLUME", "VALUE", "NO OF TRADES", "SYMBOL"}; 
        vector<string> date;
        vector<double> open;
        vector<double> high;
        vector<double> low;
        vector<double> prev_close;
        vector<double> ltp;
        vector<double> close;
        vector<double> vwap;
        vector<long long> volume;
        vector<double> value;
        vector<long long> no_of_trades;
        vector<double> price1;
        vector<double> price2;
        int data_size = 0;
        int size();
        StockData();
        void read_data(const string &symbol, const string &strategy, int is_train);
        void read_pairs(const string &symbol1, const string &symbol2);
};