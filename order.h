#pragma once
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Order
{
    public:
        string date;
        string direction;
        double price;
        int quantity;
        Order(const string& date, const string& direction, double price, int quantity);
};