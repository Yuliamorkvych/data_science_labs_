#include "FrameProcessor.hpp"
#include <string>
FrameProcessor::FrameProcessor() : cannyThreshold(50), isDrawing(false), hasRectangle(false) {}
int* FrameProcessor::getCannyThresholdPtr() { return &cannyThreshold; }
void FrameProcessor::onTrackbar(int value, void* userdata) {}
void FrameProcessor::onMouse(int event, int x, int y, int flags, void* userdata) {
    FrameProcessor* p = reinterpret_cast<FrameProcessor*>(userdata);
    if (!p) return;
    if (event == cv::EVENT_LBUTTONDOWN) {
        p->isDrawing = true; p->startPoint = cv::Point(x, y); p->endPoint = cv::Point(x, y); p->hasRectangle = true;
    } else if (event == cv::EVENT_MOUSEMOVE && p->isDrawing) {
        p->endPoint = cv::Point(x, y);
    } else if (event == cv::EVENT_LBUTTONUP && p->isDrawing) {
        p->endPoint = cv::Point(x, y); p->isDrawing = false;
    }
}
void FrameProcessor::drawFPS(cv::Mat& frame) {
    static int64 lastTick = cv::getTickCount(); static double fps = 0.0; static int frameCount = 0;
    frameCount++; int64 currentTick = cv::getTickCount();
    double timeElapsed = (currentTick - lastTick) / cv::getTickFrequency();
    if (timeElapsed >= 1.0) { fps = frameCount / timeElapsed; frameCount = 0; lastTick = currentTick; }
    cv::putText(frame, "FPS: " + std::to_string(static_cast<int>(fps)), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
}
void FrameProcessor::process(cv::Mat& frame, KeyProcessor::Mode mode) {
    if (frame.empty()) return;
    switch (mode) {
        case KeyProcessor::Mode::INVERT: cv::bitwise_not(frame, frame); break;
        case KeyProcessor::Mode::CANNY: {
            cv::Mat gray, edges; cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            cv::Canny(gray, edges, cannyThreshold, cannyThreshold * 3); cv::cvtColor(edges, frame, cv::COLOR_GRAY2BGR); break;
        }
        case KeyProcessor::Mode::BLUR: cv::GaussianBlur(frame, frame, cv::Size(15, 15), 0); break;
        default: break;
    }
    if (hasRectangle) cv::rectangle(frame, startPoint, endPoint, cv::Scalar(0, 0, 255), 2);
    drawFPS(frame);
}
