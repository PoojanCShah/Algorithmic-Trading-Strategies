# Algorithmic-Trading-Strategies

This is an implementation of various trading algorithms and their backtesting on past stock data. Intuition and specifications of various strategies can be found in [this](strategies.pdf) document. We back test our trading on the NIFTY50 stocks which covers major sectors of the Indian economy .


To run this project, clone this repository and follow the commands for each of the strategies as described below : 

### Basic 

`make strategy=BASIC symbol=SBIN n=5 x=2 start_date="b" end_date="a"`

### DMA : Daily Moving Average 

`make strategy=DMA symbol=SBIN n=50 x=3 p=2 start_date="a" end_date="b"`

### DMA++

`make strategy="DMA++" symbol=SBIN x=4 p=5 n=14 max_hold_days=28 c1=2 c2=0.2
start_date="a" end_date="b"`

### MACD :  Moving Average Convergence Divergence 

`make strategy=MACD symbol=SBIN x=3 start_date="a" end_date="b"`

### RSI : Relative Strength Index 

`make strategy=RSI symbol=SBIN x=3 n=14 oversold_threshold=30 overbought_threshold=70
start_date="a" end_date="b"`

### ADX :Average Directional Index

`make strategy=ADX symbol=SBIN x=3 n=14 adx_threshold=25 start_date="a" end_date="b"`

### Regression model

`make strategy="LINEAR_REGRESSION" symbol=SBIN x=3 p=2 train_start_date="a"
train_end_date="b" start_date="c" end_date="d"`

### Best Of All 

`make strategy="BEST_OF_ALL" symbol=SBIN start_date="a" end_date="b"`

### Mean Reverting Pairs

`make strategy=PAIRS symbol1=SBIN symbol2=ADANIENT x=5 n=20 threshold=2
stop_loss_threshold=4 start_date="a" end_date="b"`

As output, csv files `daily_cashflow.csv` , `order_statistics.csv` and`final_pnl.txt` will be produced.