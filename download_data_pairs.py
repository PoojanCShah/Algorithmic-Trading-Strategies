import pandas as pd
import os, sys
from jugaad_data.nse import stock_df
from datetime import datetime, date, timedelta

if not os.path.exists("data"):
    os.makedirs("data")

def download_data(name, symbol1,symbol2, start_date, end_date, n):
    df1 = stock_df(symbol=symbol1, from_date=start_date - timedelta(max(5 * n, 10)), to_date=end_date, series="EQ")
    df2 = stock_df(symbol=symbol2, from_date=start_date - timedelta(max(5 * n, 10)), to_date=end_date, series="EQ")
    df1.drop_duplicates(subset=["DATE"], inplace=True)
    df2.drop_duplicates(subset=["DATE"], inplace=True)
    dates1 = df1["DATE"].to_list()
    dates2 = df2["DATE"].to_list()
    prices1 = df1["CLOSE"].to_list()
    prices2 = df2["CLOSE"].to_list()
    data = []
    for d1, p1 in zip(dates1, prices1):
        for d2, p2 in zip(dates2, prices2):
            if d1 == d2:
                data.append([d1, p1, p2])
    data = data[::-1]
    for i in range(len(data)):
        if data[i][0].date() >= start_date:
            start = i
            break
    data = data[start - n:]
    data = pd.DataFrame(data, columns=["DATE", symbol1, symbol2])
    data["DATE"] = data["DATE"].apply(lambda x: x.strftime("%d/%m/%Y"))
    data.to_csv(f"data/{name}.csv", index=False)

if __name__ == "__main__":
    _, symbol1, symbol2, start_date, end_date, n = sys.argv
    name = f'{symbol1}_{symbol2}_pairs'
    start_date = datetime.strptime(start_date, "%d/%m/%Y").date()
    end_date = datetime.strptime(end_date, "%d/%m/%Y").date()
    n = int(n)
    download_data(name, symbol1, symbol2, start_date, end_date, n)