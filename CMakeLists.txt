cmake_minimum_required(VERSION 3.10)

#set project name 
project(webrtc_apm VERSION 0.1)

set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED True)


add_library(audio_processing_module 
            src/audio_processing_module.cc
)

include_directories(webrtc/include
    webrtc/include/third_party/absel-cpp
)

find_library(PYBIND11_LIB pybind11 )

link_directories(webrtc/lib
)


link_libraries(
    webrtc
    $PYBIND11_LIB
)

add_definitions(
    -O3 -Wall -fPIC
)


##g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) src/main.cc -o apm$(python3-config --extension-suffix)



