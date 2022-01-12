#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/cvdef.h>

cv::Mat grayscale(cv::Mat image);
cv::Mat blur(cv::Mat image);
cv:: Mat detectEdges(cv::Mat image);
cv::Mat mask(cv::Mat image);
std::vector<cv::Vec4i> getLines(cv::Mat image);

cv::Mat findAverage(cv::Mat image);
void findAverage(cv::Mat image, cv::Mat lines);
cv::Mat showLines(cv::Mat image, cv::Mat lines);
void makePoints(cv::Mat, int average);
