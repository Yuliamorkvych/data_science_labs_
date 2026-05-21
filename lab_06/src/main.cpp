#include <iostream>
#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Display.hpp"
int main() {
    std::cout << "Запуск Лабораторної роботи №6..." << std::endl;
    CameraProvider camera(0);
    KeyProcessor keyProcessor; FrameProcessor frameProcessor; Display display("OpenCV Processing");
    display.setupInteractiveElements(frameProcessor);
    while (true) {
        cv::Mat frame = camera.getFrame();
        if (frame.empty()) {
            frame = cv::Mat::zeros(480, 640, CV_8UC3);
            cv::putText(frame, "No Camera in WSL - Emulation Mode", cv::Point(50, 240), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 255), 2);
        }
        frameProcessor.process(frame, keyProcessor.getMode());
        display.show(frame);
        int key = cv::waitKey(30);
        if ((key & 0xFF) == 27) break;
        keyProcessor.processKey(key);
    }
    return 0;
}
