#pragma once
#include <opencv2/opencv.hpp>
#include "KeyProcessor.hpp"
class FrameProcessor {
private:
    int cannyThreshold;
    cv::Point startPoint;
    cv::Point endPoint;
    bool isDrawing;
    bool hasRectangle;
public:
    FrameProcessor();
    void process(cv::Mat& frame, KeyProcessor::Mode mode);
    int* getCannyThresholdPtr();
    static void onTrackbar(int value, void* userdata);
    static void onMouse(int event, int x, int y, int flags, void* userdata);
    void drawFPS(cv::Mat& frame);
};
