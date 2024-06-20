#include "stockdata.h"

StockData::StockData()
{
    
}

int StockData::size()
{
    return this->data_size;
}

void StockData::read_data(const string &symbol, const string &strategy, int is_train)
{
    string train = is_train ? "train_" : "";
    ifstream file("data/" + train + symbol + "_" + strategy + ".csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string date, series;
        char comma;
        double open, high, low, prev_close, ltp, close, vwap, _52w_h, _52w_l, value;
        long long volume, no_of_trades;
        getline(ss, date, ',');
        getline(ss, series, ',');
        ss >> open >> comma >> high >> comma >> low >> comma >> prev_close >> comma >> ltp >> comma >> close >> comma >> vwap >> comma >> _52w_h >> comma >> _52w_l >> comma >> volume >> comma >> value >> comma >> no_of_trades;
        this->date.push_back(date);
        this->open.push_back(open);
        this->high.push_back(high);
        this->low.push_back(low);
        this->prev_close.push_back(prev_close);
        this->ltp.push_back(ltp);
        this->close.push_back(close);
        this->vwap.push_back(vwap);
        this->volume.push_back(volume);
        this->value.push_back(value);
        this->no_of_trades.push_back(no_of_trades);
    }
    file.close();
    this->data_size = this->date.size();
}

void StockData::read_pairs(const string &symbol1, const string &symbol2)
{
    ifstream file("data/" + symbol1 + "_" + symbol2 + "_pairs" + ".csv");
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string date;
        double price1, price2;
        char comma;
        getline(ss, date, ',');
        ss >> price1 >> comma >> price2;
        this->date.push_back(date);
        this->price1.push_back(price1);
        this->price2.push_back(price2);
    }
    file.close();
    this->data_size = this->date.size();
}
