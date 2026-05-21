#!/bin/bash
echo "=== Компіляція проєкту ==="
mkdir -p build
cd build
cmake ..
make
