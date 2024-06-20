#include <iostream>
#include <bits/stdc++.h>
#include "order.h"
using namespace std;

Order::Order(const string& date, const string& direction, double price, int quantity)
{
    this->date = date;
    this->direction = direction;
    this->price = price;
    this->quantity = quantity;
}