#include "CameraProvider.hpp"
#include <opencv2/imgcodecs.hpp>
#include <unistd.h>

CameraProvider::CameraProvider(int deviceId) { 
    // Тепер читаємо «потоковий» файл .ts, який ідеально працює на льоту
    cap.open("/mnt/c/ffmpeg/live_cam.ts", cv::CAP_FFMPEG); 
}

CameraProvider::~CameraProvider() { 
    if (cap.isOpened()) cap.release(); 
}

bool CameraProvider::isOpened() const { 
    return cap.isOpened(); 
}

cv::Mat CameraProvider::getFrame() { 
    cv::Mat frame; 
    if (cap.isOpened()) {
        cap >> frame; 
        
        // Якщо наздогнали запис, робимо мікропаузу
        if (frame.empty()) {
            usleep(30000);
            cap.set(cv::CAP_PROP_POS_FRAMES, cap.get(cv::CAP_PROP_POS_FRAMES) - 1);
            cap >> frame;
        }
    }
    
    if (frame.empty()) {
        frame = cv::Mat::zeros(480, 640, CV_8UC3);
    }
    return frame; 
}
