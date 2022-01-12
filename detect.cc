#include "detect.h"
#include "Polyfit/PolyfitEigen.hpp"

cv::Mat grayscale(cv::Mat image) {
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    return grayImage;
}

cv::Mat blur(cv::Mat image) {
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(7, 7), 0);
    return blurredImage;
}

cv::Mat mask(cv::Mat image) {
    int height = image.rows;
    int width = image.cols;
    std::vector<cv::Point> triangle;
    triangle.push_back(cv::Point(width / 10, height));
    triangle.push_back(cv::Point(width / 5 * 3, height / 2));
    triangle.push_back(cv::Point(width, height));
    std::vector<std::vector<cv::Point>> points;
    points.push_back(triangle);
    cv::Mat mask = cv::Mat::zeros(height, width, image.type());
    cv::fillPoly(mask, points, cv::Scalar(255));
    cv::Mat maskedImage;
    cv::bitwise_and(image, mask, maskedImage);
    return maskedImage;
}

cv::Mat findEdges(cv::Mat image) {
    cv::Mat edges;
    Canny(image, edges, 50, 100, 5);
    return edges;
}

std::vector<cv::Vec4i> findLines(cv::Mat image) {
    std::vector<cv::Vec4i> lines;
    HoughLinesP(image, lines, 2, CV_PI / 180, 100, 20, 5);
    return lines;
}

std::vector<int> makePoints(cv::Mat image, std::vector<std::vector<double>> coeffs) {
    double y_int, slope;
    for (std::vector<double> coeff : coeffs) {
        y_int += coeff[0];
        slope += coeff[1];
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
        std::vector<double> coeff = polyfit_Eigen(x, y, 1);
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
