#include "detect.h"

cv::Mat grayscale(cv::Mat image) {
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    return grayImage;
}

cv::Mat blur(cv::Mat image) {
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(5, 5), 0);
    return blurredImage;
}

cv::Mat detectEdges(cv::Mat image) {
    cv::Mat edges;
    Canny(image, edges, 50, 100, 5);
    return edges;
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
    cv::Mat mask = cv::Mat(height, width, image.type());
    cv::fillPoly(mask, points, cv::Scalar(255));
    cv::Mat maskedImage;
    cv::bitwise_and(image, mask, maskedImage);
    return maskedImage;
}

std::vector<cv::Vec4i> getLines(cv::Mat image) {
    std::vector<cv::Vec4i> lines;
    HoughLinesP(image, lines, 2, CV_PI / 180, 80, 30, 5);
    return lines;
}
