#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include "FrameProcessor.hpp"
class Display {
private:
    std::string windowName;
public:
    Display(std::string name = "Lab 6 OpenCV");
    ~Display();
    void show(const cv::Mat& frame);
    void setupInteractiveElements(FrameProcessor& processor);
};
