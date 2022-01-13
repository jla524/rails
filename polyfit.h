#include <iostream>
#include "eigen3/Eigen/Dense"

template<typename T>
std::vector<T> polyfit(const std::vector<T> &xValues, const std::vector<T> &yValues, const int degree) {
    using namespace Eigen;
    int nCoefficients = degree + 1;
    size_t nCount = xValues.size();
    Eigen::MatrixXf X(nCount, nCoefficients);
    Eigen::MatrixXf Y(nCount, 1);
    
    // fill X and Y matrix
    for (size_t i = 0; i < nCount; i++) {
        T nVal = 1.0f;
        Y(i, 0) = yValues[i];
        for (int j = 0; j < nCoefficients; j++) {
            X(i, j) = nVal;
            nVal *= xValues[i];
        }
    }
    
    VectorXf coeffs = X.jacobiSvd(ComputeThinU | ComputeThinV).solve(Y);
    return std::vector<T>(coeffs.data(), coeffs.data() + nCoefficients);
}
