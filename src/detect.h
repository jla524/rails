#include <opencv2/opencv.hpp>

cv::Mat grayscale(cv::Mat image);
cv::Mat blur(cv::Mat image);
cv:: Mat detectEdges(cv::Mat image);
cv::Mat mask(cv::Mat image);
cv::Mat findAverage(cv::Mat image);

cv::Mat showLines(cv::Mat image, cv::Mat lines);
void findAverage(cv::Mat image, cv::Mat lines);
void makePoints(cv::Mat, int average);
