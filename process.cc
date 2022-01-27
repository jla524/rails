#include "process.h"

cv::Mat grayscale(cv::Mat image) {
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    return grayImage;
}

cv::Mat blur(cv::Mat image) {
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(3, 3), 0);
    return blurredImage;
}

cv::Mat mask(cv::Mat image) {
    int height = image.rows;
    int width = image.cols;
    std::vector<cv::Point> triangle;
    triangle.push_back(cv::Point(width / 7, height));
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
    Canny(image, edges, 50, 100, 3);
    return edges;
}

std::vector<cv::Vec4i> findLines(cv::Mat image) {
    std::vector<cv::Vec4i> lines;
    HoughLinesP(image, lines, 2, CV_PI / 180, 380, 50, 3);
    return lines;
}

cv::Mat combineImages(cv::Mat image1, double weight1, cv::Mat image2, double weight2) {
    cv::Mat combined;
    cv::addWeighted(image1, weight1, image2, weight2, 1, combined);
    return combined;
}
