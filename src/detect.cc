// Adapted from https://medium.com/analytics-vidhya/building-a-lane-detection-system-f7a727c6694
#include "detect.h"
#include "linreg.h"

std::vector<std::vector<int>> findAverage(cv::Mat image, std::vector<cv::Vec4i> lines) {
    if (lines.empty())
        return std::vector<std::vector<int>>();
    std::vector<std::vector<double>> left_coeffs, right_coeffs;
    for (cv::Vec4i line : lines) {
        std::vector<double> x, y;
        x.push_back(line[0]);
        x.push_back(line[2]);
        y.push_back(line[1]);
        y.push_back(line[3]);
        std::vector<double> coeff = linreg(x, y);
        if (coeff[1] < 0)
            left_coeffs.push_back(coeff);
        else
            right_coeffs.push_back(coeff);
    }
    std::vector<std::vector<int>> points;
    points.push_back(makePoints(image, left_coeffs));
    points.push_back(makePoints(image, right_coeffs));
    return points;
}

std::vector<int> makePoints(cv::Mat image, std::vector<std::vector<double>> coeffs) {
    double y_int, slope;
    for (std::vector<double> coeff : coeffs) {
        slope += coeff[0];
        y_int += coeff[1];
    }
    y_int /= coeffs.size();
    slope /= coeffs.size();
    int y1 = image.rows;
    int y2 = (int) (y1 / 5 * 3);
    std::vector<int> points;
    points.push_back((int) (y1 - y_int) / slope);
    points.push_back(y1);
    points.push_back((int) (y2 - y_int) / slope);
    points.push_back(y2);
    return points;
}

cv::Mat showLines(cv::Mat image, std::vector<std::vector<int>> lines) {
    cv::Mat linedImage = cv::Mat::zeros(image.rows, image.cols, image.type());
    if (lines.empty())
        return linedImage;
    for (std::vector<int> line : lines) {
        cv::Point pt1 = cv::Point(line[0], line[1]);
        cv::Point pt2 = cv::Point(line[2], line[3]);
        cv::line(linedImage, pt1, pt2, cv::Scalar(0, 255, 0), 10);
    }
    return linedImage;
}
