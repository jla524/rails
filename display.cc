#include <iostream>
#include "opencv2/opencv.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Please provide a file name." << std::endl;
        return 1;
    }

    std::string path = argv[1];
    cv::VideoCapture cap(path);

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;
        imshow("Frame", frame);
        // Press ESC key to exit
        if (cv::waitKey(25) == 27)
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
