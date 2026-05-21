#!/bin/bash
echo "=== Встановлення залежностей проєкту ==="
sudo apt-get update
sudo apt-get install -y build-essential cmake libopencv-dev ffmpeg
