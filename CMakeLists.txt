cmake_minimum_required(VERSION 3.1)

project(libfvad LANGUAGES C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB SOURCE ${PROJECT_SOURCE_DIR}/src/*.c ${PROJECT_SOURCE_DIR}/src/vad/*.c ${PROJECT_SOURCE_DIR}/src/signal_processing/*.c)

add_library(${PROJECT_NAME} SHARED ${SOURCE})