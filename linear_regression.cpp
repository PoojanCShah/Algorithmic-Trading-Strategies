#include <bits/stdc++.h>
#include "linear_regression.h"
#include "matrix.h"
using namespace std;

LinearRegression::LinearRegression(const string &symbol, int max_position, int threshold)
{
    this->symbol = symbol;
    this->max_position = max_position;
    if (threshold == -1){
        threshold = 2;
    }
    this->threshold = threshold;
    train_data.read_data(symbol, "LINEAR_REGRESSION", 1);
    data.read_data(symbol, "LINEAR_REGRESSION", 0);
    past_days = 1;
}

void LinearRegression::train()
{
    vector<double> one(train_data.size() - 1, 1);
    vector<vector<double>> X(8, vector<double>(train_data.size() - 1));
    X[0] = one;
    copy(train_data.close.begin(), train_data.close.end() - 1, X[1].begin());
    copy(train_data.open.begin(), train_data.open.end() - 1, X[2].begin());
    copy(train_data.vwap.begin(), train_data.vwap.end() - 1, X[3].begin());
    copy(train_data.low.begin(), train_data.low.end() - 1, X[4].begin());
    copy(train_data.high.begin(), train_data.high.end() - 1, X[5].begin());
    copy(train_data.no_of_trades.begin(), train_data.no_of_trades.end() - 1, X[6].begin());
    copy(train_data.open.begin() + 1, train_data.open.end(), X[7].begin());
    Matrix X_mat_T(X);
    Matrix X_mat = X_mat_T.transpose();
    vector<double> Y(train_data.close.begin() + 1, train_data.close.end());
    vector<vector<double>> y = {Y};
    Matrix y_mat(y);
    y_mat = y_mat.transpose();
    Matrix XTX = X_mat_T * X_mat;
    Matrix XTX_inv = XTX.inverse();
    Matrix XTY = X_mat_T * y_mat;
    beta = XTX_inv * XTY;
}

void LinearRegression::precompute(){
    train();
    vector<double> one(data.size() - 1, 1);
    vector<vector<double>> X(8, vector<double>(data.size() - 1));
    X[0] = one;
    copy(data.close.begin(), data.close.end() - 1, X[1].begin());
    copy(data.open.begin(), data.open.end() - 1, X[2].begin());
    copy(data.vwap.begin(), data.vwap.end() - 1, X[3].begin());
    copy(data.low.begin(), data.low.end() - 1, X[4].begin());
    copy(data.high.begin(), data.high.end() - 1, X[5].begin());
    copy(data.no_of_trades.begin(), data.no_of_trades.end() - 1, X[6].begin());
    copy(data.open.begin() + 1, data.open.end(), X[7].begin());
    Matrix X_mat_T(X);
    Matrix X_mat = X_mat_T.transpose();
    prediction = (X_mat * beta).get_col(0);
    return;
}

int LinearRegression::if_buy_sell(int day)
{
    bool buy = (prediction[day - 1] - data.close[day]) * 100 >= threshold * data.close[day]; 
    bool sell = (data.close[day] - prediction[day - 1]) * 100 >= threshold * data.close[day];
    if(buy){
        return 1;
    }
    else if(sell){
        return -1;
    }
    return 0;
}