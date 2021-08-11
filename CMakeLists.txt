cmake_minimum_required(VERSION 3.10)

#set project name 
project(webrtc_apm VERSION 0.1)

add_executable(webrtc_apm src/test.cc)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED True)

##g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) src/main.cc -o apm$(python3-config --extension-suffix)



