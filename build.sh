#!/bin/bash

# Build with emcc
emcc wrapper.cpp ./CDT/CDT/src/CDT.cpp \
    -I./CDT/CDT/include \
    -s WASM=1 \
    -s MODULARIZE=1 \
    -s EXPORT_NAME="CDTModule" \
    -s ENVIRONMENT=web \
    -s ALLOW_MEMORY_GROWTH=1 \
    --bind \
    -o dist/cdt.js
