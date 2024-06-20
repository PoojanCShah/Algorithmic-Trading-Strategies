#pragma once
#include <iostream>
#include <bits/stdc++.h>
#include "stockdata.h"
#include "order.h"
using namespace std;

class Strategy
{
    public:
        StockData data;
        string symbol;
        Strategy();
        string start_date;
        string end_date;
        int past_days;
        int max_position;
        int position = 0;
        double cash = 0;
        vector<double> daily_cashflow;
        vector<string> dates;
        vector<Order> orders;
        void square_off();
        void write_daily_cashflow();
        void write_order_statistics();
        void write_final_pnl();
        void write();
        void run();
        virtual int if_buy_sell(int day);
        virtual void precompute();
};