#include <opencv2/opencv.hpp>
#include <opencv2/core/cvdef.h>

std::vector<std::vector<int>> findAverage(cv::Mat image, std::vector<cv::Vec4i> lines);
std::vector<int> makePoints(cv::Mat image, std::vector<std::vector<double>> coeffs);
cv::Mat showLines(cv::Mat image, std::vector<std::vector<int>> lines);
