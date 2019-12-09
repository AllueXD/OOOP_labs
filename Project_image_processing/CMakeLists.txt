cmake_minimum_required(VERSION 3.14)
project(Project_image_processing)

set(CMAKE_CXX_STANDARD 17)


add_executable(Project_image_processing main.cpp ImageProcessing.h)

include_directories("D:\\Programming\\opencv\\build\\include")
target_link_directories(${PROJECT_NAME} PRIVATE D:\\Programming\\bin)
target_link_libraries(${PROJECT_NAME} PRIVATE
        opencv_imgproc412d
        opencv_imgcodecs412d
        opencv_core412d
)
