from jugaad_data.nse import stock_df
from datetime import datetime, date, timedelta
from threading import Thread
import sys
import os

if not os.path.exists("data"):
    os.makedirs("data")

def download_data(name, symbol, start_date, end_date, n):
    df = stock_df(symbol=symbol, from_date=start_date - timedelta(max(5 * n, 10)), to_date=end_date, series="EQ")
    df.drop_duplicates(subset=["DATE"], inplace=True)
    df = df.iloc[::-1]
    idx = 0
    for i in range(len(df)):
        if (df.iloc[i]["DATE"]).date() >= start_date:
            idx = i
            break
    idx = idx - n
    df = df.iloc[idx:]
    df["DATE"] = df["DATE"].apply(lambda x: x.strftime("%d/%m/%Y"))
    df.to_csv(f"data/{name}.csv", index=False)


if __name__ == "__main__":
    """
    start and end dates are in DD/MM/YYYY format
    """
    _, strategy, symbol, start_date, end_date, n, train_start_date, train_end_date = sys.argv
    n = int(n)
    start_date = (datetime.strptime(start_date, "%d/%m/%Y")).date()
    end_date = datetime.strptime(end_date, "%d/%m/%Y").date()
    train_start_date = (datetime.strptime(train_start_date, "%d/%m/%Y")).date()
    train_end_date = datetime.strptime(train_end_date, "%d/%m/%Y").date()

    if strategy == "LINEAR_REGRESSION":
        n = 1
        download_data("train_" + symbol + "_" + strategy, symbol, train_start_date, train_end_date, n)
        download_data(symbol + "_" + strategy, symbol, start_date, end_date, n)
    elif strategy == "ADX":
        n = 1
        download_data(symbol + "_" + strategy, symbol, start_date, end_date, n)
    elif strategy == "BEST_OF_ALL":
        train_start_date = date(year=start_date.year - 1, month=start_date.month, day=start_date.day)
        train_end_date = date(year=end_date.year - 1, month=end_date.month, day=end_date.day)
        t1 = Thread(target=download_data, args=(symbol + "_LINEAR_REGRESSION", symbol, start_date, end_date, 1))
        t2 = Thread(target=download_data, args=(symbol + "_ADX", symbol, start_date, end_date, 1))
        t3 = Thread(target=download_data, args=("train_" + symbol + "_LINEAR_REGRESSION", symbol, train_start_date , train_end_date, 1))
        t4 = Thread(target=download_data, args=(symbol + "_BASIC", symbol, start_date, end_date, 7))
        t5 = Thread(target=download_data, args=(symbol + "_RSI", symbol, start_date, end_date, 14))
        t6 = Thread(target=download_data, args=(symbol + "_DMA", symbol, start_date, end_date, 50))
        t7 = Thread(target=download_data, args=(symbol + "_DMA++", symbol, start_date, end_date, 14))
        t8 = Thread(target=download_data, args=(symbol + "_MACD", symbol, start_date, end_date, 0))
        for t in [t1, t2, t3, t4, t5, t6, t7, t8]:
            t.start()
        for t in [t1, t2, t3, t4, t5, t6, t7, t8]:
            t.join()
    else:
        download_data(symbol + "_" + strategy, symbol, start_date, end_date, n)