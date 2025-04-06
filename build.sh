#!/bin/bash

# Create dist directory if it doesn't exist
mkdir -p dist

# Build with emcc
emcc wrapper.cpp ./CDT/CDT/src/CDT.cpp \
    -I./CDT/CDT/include \
    -std=c++17 \
    -O3 \
    -s WASM=1 \
    -s MODULARIZE=1 \
    -s EXPORT_NAME="CDTModule" \
    -s ENVIRONMENT='web,node' \
    -s EXPORT_ES6=1 \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s SINGLE_FILE=1 \
    --bind \
    -o dist/cdt.js
