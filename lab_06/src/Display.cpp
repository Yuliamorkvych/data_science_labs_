#include "Display.hpp"
Display::Display(std::string name) : windowName(name) { cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE); }
Display::~Display() { cv::destroyWindow(windowName); }
void Display::show(const cv::Mat& frame) { if (!frame.empty()) cv::imshow(windowName, frame); }
void Display::setupInteractiveElements(FrameProcessor& processor) {
    cv::createTrackbar("Canny Thresh", windowName, processor.getCannyThresholdPtr(), 255, FrameProcessor::onTrackbar);
    cv::setMouseCallback(windowName, FrameProcessor::onMouse, &processor);
}
