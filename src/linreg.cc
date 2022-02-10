// Adapted from https://stackoverflow.com/questions/5083465/fast-efficient-least-squares-fit-algorithm-in-c
#include "linreg.h"

std::vector<double> linreg(const std::vector<double> &x, const std::vector<double> &y) {
    int n = x.size();
    assert(n == y.size());
    double sum_x = 0.0, sum_x2 = 0.0, sum_xy = 0.0, sum_y = 0.0, sum_y2 = 0.0;

    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_x2 += x[i] * x[i];
        sum_xy += x[i] * y[i];
        sum_y += y[i];
        sum_y2 += y[i] * y[i];
    }

    double denom = n * sum_x2 - sum_x * sum_x;

    if (denom == 0)
        return std::vector<double>();

    std::vector<double> parameters;
    parameters.push_back((n * sum_xy - sum_x * sum_y) / denom);
    parameters.push_back((sum_y * sum_x2 - sum_x * sum_xy) / denom);
    return parameters;
}
