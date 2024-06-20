#include "adx.h"

ADX::ADX(string symbol, int n, int max_position, double adx_threshold)
{
    this->symbol = symbol;
    this->max_position = max_position;
    this->adx_threshold = adx_threshold;
    if (n == 0){
        n = 14;
    }
    this->n = n;
    data.read_data(symbol, "ADX", 0);
    past_days = 1;
}

void ADX::precompute()
{
    true_range.resize(data.close.size());
    dm_plus.resize(data.close.size());
    dm_minus.resize(data.close.size());
    atr.resize(data.close.size());
    di_plus.resize(data.close.size());
    di_minus.resize(data.close.size());
    dx.resize(data.close.size());
    adx.resize(data.close.size());

    const double ALPHA = 2.0 /( 1.0 + (double)n);

    for (int i = 1; i < data.close.size(); i++)
    {
        double high_t = data.high[i];
        double low_t = data.low[i];
        double prev_close_t = data.prev_close[i];
        true_range[i] = max(high_t - low_t, max(high_t - prev_close_t, low_t - prev_close_t));
        dm_plus[i] = max(0.0, high_t - data.high[i - 1]);
        dm_minus[i] = max(0.0, low_t - data.low[i - 1]);
    }

    atr[1] = true_range[1];
    for (int i = 2; i < data.close.size(); i++)
    {
        atr[i] = (atr[i - 1] * (1 - ALPHA) + true_range[i] * ALPHA);
    }

    di_plus[1] = (dm_plus[1] / atr[1]);
    di_minus[1] = (dm_minus[1] / atr[1]);
    for (int i = 2; i < data.close.size(); i++)
    {
        di_plus[i] = (dm_plus[i] / atr[i]) * ALPHA + di_plus[i - 1] * (1 - ALPHA);
        di_minus[i] = (dm_minus[i] / atr[i]) * ALPHA + di_minus[i - 1] * (1 - ALPHA);
    }

    for (int i = 1; i < data.close.size(); i++)
    {
        dx[i] = ((abs(di_plus[i] + di_minus[i]) < 1e-6) ? 0 : 100 * (di_plus[i] - di_minus[i]) / (di_plus[i] + di_minus[i]));
    }

    adx[1] = dx[1];
    for (int i = 2; i < data.close.size(); i++)
    {
        adx[i] = (adx[i - 1] * (1 - ALPHA) + dx[i] * ALPHA);
    }
}

int ADX::if_buy_sell(int day)
{
    if(abs(dx[day]) < 1e-6)
    {
        return 0;
    }
    else if (adx[day] > adx_threshold)
    {
        return 1;
    }
    else
    {
        return -1;
    }
    return 0;
}
