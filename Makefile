# // make strategy=BASIC symbol=SBIN n=5 x=2 start_date="b" end_date="a"

.DEFAULT_GOAL := run
n ?= 0
x ?= 5
p ?= -1
c1 ?= 2
c2 ?= 0.2
max_hold_days ?= 28
oversold_threshold ?= 30
overbought_threshold ?= 70
adx_threshold ?= 25
train_start_date ?= 10/02/2004
train_end_date ?= 10/02/2014
stop_loss_threshold ?= -1

ifeq ($(strategy),PAIRS)
run:
	rm -f *.csv
	python3 download_data_pairs.py $(symbol1) $(symbol2) $(start_date) $(end_date) $(n)
	g++ -o main_pairs main_pairs.cpp
	./main_pairs $(symbol1) $(symbol2) $(n) $(x) $(threshold) $(stop_loss_threshold)
	python3 clean.py
else
run: download_data.py main.cpp
	rm -f *.csv
	python3 download_data.py $(strategy) $(symbol) $(start_date) $(end_date) $(n) $(train_start_date) $(train_end_date)
	g++ -o main main.cpp
	./main $(strategy) $(symbol) ${start_date} ${end_date} $(n) $(x) $(p) $(c1) $(c2) $(max_hold_days) $(oversold_threshold) $(overbought_threshold) $(adx_threshold) $(train_start_date) $(train_end_date)
	python3 clean.py
endif
