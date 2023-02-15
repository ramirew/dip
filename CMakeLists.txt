cmake_minimum_required(VERSION 3.0.0)

project(DPI VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define OpenMP
find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Define sources
file(GLOB_RECURSE SOURCES_FILES
    "classification/*.cpp"
    "classification/*.cxx"
)

file(GLOB_RECURSE METRICS_SOURCES_FILES
    "metrics/*.cpp"
    "metrics/*.cxx"
)

file(GLOB_RECURSE FEATURE_EXTRACTION_SOURCES_FILES
    "feature_ext_sel/*.cpp"
    "feature_ext_sel/*.cxx"
)



# Define headers
file(GLOB_RECURSE HEADERS_FILES
"*.h"
"*.hpp"
)

# Set sources
add_library(classification STATIC "${SOURCES_FILES}")
add_library(classificationMetrics STATIC "${METRICS_SOURCES_FILES}")
add_library(featureExtraction STATIC "${FEATURE_EXTRACTION_SOURCES_FILES}")




# Include dirs
include_directories(classification)
include_directories(metrics)
include_directories(feature_ext_sel)

include_directories(${OpenMP_CXX_LIBRARIES})

# C++ flags
set(USE_PTHREAD ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
