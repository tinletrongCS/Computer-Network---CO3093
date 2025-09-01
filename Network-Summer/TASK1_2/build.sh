#!/bin/bash

OUTPUT=cs23_server

CXX=g++
CXXFLAGS="-std=c++17 -Wall -I."

SOURCES=$(find . -name "*.cpp")
echo "$CXX $CXXFLAGS -o $OUTPUT $SOURCES"

$CXX $CXXFLAGS -o $OUTPUT $SOURCES

if [ $? -eq 0 ]; then
    echo "Build successful: ./$OUTPUT"
else
    echo "Build failed."
fi