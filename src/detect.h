#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/cvdef.h>

cv::Mat grayscale(cv::Mat image);
cv::Mat blur(cv::Mat image);
cv::Mat mask(cv::Mat image);
cv::Mat findEdges(cv::Mat image);
std::vector<cv::Vec4i> findLines(cv::Mat image);
