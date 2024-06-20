#pragma once
#include "matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(vector<vector<double>> data)
{
    this->data = data;
    this->rows = data.size();
    this->cols = data[0].size();
}

Matrix Matrix::operator*(Matrix &other)
{
    vector<vector<double>> result;
    for (int i = 0; i < this->rows; i++)
    {
        vector<double> row;
        for (int j = 0; j < other.cols; j++)
        {
            double sum = 0;
            for (int k = 0; k < this->cols; k++)
            {
                sum += this->data[i][k] * other.data[k][j];
            }
            row.push_back(sum);
        }
        result.push_back(row);
    }
    return Matrix(result);
}

Matrix Matrix::transpose()
{
    vector<vector<double>> result(this->cols, vector<double>(this->rows));
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            result[j][i] = this->data[i][j];
        }
    }
    return Matrix(result);
}

Matrix Matrix::inverse()
{
    int n = this->rows;
    assert(this->rows == this->cols);
    vector<vector<double>> augmented(n, vector<double>(2 * n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented[i][j] = data[i][j];
        }
        augmented[i][i + n] = 1;
    }
    for (int i = 0; i < n; ++i) {
        double div = augmented[i][i];
        for (int j = 0; j < 2 * n; ++j) {
            augmented[i][j] /= div;
        }
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                double factor = augmented[j][i];
                for (int k = 0; k < 2 * n; ++k) {
                    augmented[j][k] -= factor * augmented[i][k];
                }
            }
        }
    }
    vector<vector<double>> inv(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inv[i][j] = augmented[i][j + n];
        }
    }
    return Matrix(inv);
}

vector<double> Matrix::get_col(int col)
{
    vector<double> result;
    for (int i = 0; i < this->rows; i++)
    {
        result.push_back(this->data[i][col]);
    }
    return result;
}