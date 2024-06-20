#pragma once
#include <bits/stdc++.h>

using namespace std;

class Matrix
{
    public:
        int rows, cols;
        vector<vector<double>> data;
        Matrix();
        Matrix(vector<vector<double>> data);
        Matrix operator*(Matrix &other);
        Matrix transpose();
        Matrix inverse();
        vector<double> get_col(int col);
        // void print();
};