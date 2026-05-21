#!/bin/bash
echo "=== Запуск Лабораторної роботи №6 ==="

# Автоматично запускаємо ffmpeg на Windows у фоновому режимі, щоб він писав камеру у файл .ts
echo "Запуск трансляції вебкамери хоста..."
/mnt/c/ffmpeg/ffmpeg-master-latest-win64-gpl/bin/ffmpeg.exe -y -rtbufsize 150M -f dshow -video_size 640x480 -i video="USB2.0 HD UVC WebCam" -vcodec mpeg4 -f mpegts "C:\ffmpeg\live_cam.ts" > /dev/null 2>&1 &

# Запам'ятовуємо PID процесу ffmpeg, щоб потім його коректно закрити
FFMPEG_PID=$!

# Налаштовуємо дисплей для X-сервера
export DISPLAY=:0

# Запускаємо нашу програму
cd build
./Lab6Executable

# Після закриття графічного вікна OpenCV — зупиняємо фоновий ffmpeg на Windows
echo "Зупинка трансляції камери..."
kill $FFMPEG_PID 2>/dev/null
