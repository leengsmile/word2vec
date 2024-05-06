cmake_minimum_required(VERSION 3.20)

project(word2vec
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -O3 -Wall -std=c++14")
# https://stackoverflow.com/questions/41361631/optimize-in-cmake-by-default
# if(NOT CMAKE_BUILD_TYPE)
#   set(CMAKE_BUILD_TYPE Release)
# endif()
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(W2V_HEADER_DIR ${PROJECT_SOURCE_DIR}/include)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

include_directories(${W2V_HEADER_DIR})

file(GLOB SOURCES
  src/application/*.cpp
  src/io/*.cpp
)

add_executable(
    word2vec
    src/main.cpp
    ${SOURCES}
)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(word2vec PUBLIC OpenMP::OpenMP_CXX)
endif()