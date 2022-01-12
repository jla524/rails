#include <iostream>
#include "detect.h"

cv::Mat process(cv::Mat image) {
    cv::Mat processed = blur(grayscale(image));
    cv::Mat edges = findEdges(processed);
    cv::Mat region = mask(edges);
    std::vector<cv::Vec4i> lines = findLines(region);
    return region;
}

int main(int argc, char **argv) {
    std::string path;

    if (argc < 2) {
        std::cout << "Please provide a file name." << std::endl;
        return 1;
    }

    path = argv[1];
    cv::VideoCapture cap(path);

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;
        imshow("Frame", process(frame));
        // Press q to exit
        if (cv::waitKey(25) == 113)
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
