import os

for csvfile in os.listdir('data'):
    if csvfile.endswith('.csv'):
        os.remove(os.path.join('data', csvfile))    