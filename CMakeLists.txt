cmake_minimum_required(VERSION 3.0.0)

project(DPI VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define sources
file(GLOB_RECURSE SOURCES_FILES
    "DPI/*.cpp"
    "DPI/*.cxx"
)

file(GLOB_RECURSE METRICS_SOURCES_FILES
    "metrics/*.cpp"
)

file(GLOB_RECURSE Preprocesamiento_SOURCES_FILES
    "Preprocesamiento/*.cpp"
)

# Define headers
file(GLOB_RECURSE HEADERS_FILES
    "*.h"
    "*.hpp"
)

# Set sources
add_library(DPI STATIC "${SOURCES_FILES}")
add_library(DPIMetrics STATIC "${METRICS_SOURCES_FILES}")
add_library(DPIPreprocesamiento STATIC "${Preprocesamiento_SOURCES_FILES}")

# Include dirs
include_directories(DPI)
include_directories(metrics)
include_directories(DPIPreprocesamiento)


# C++ flags
set(USE_PTHREAD ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")






