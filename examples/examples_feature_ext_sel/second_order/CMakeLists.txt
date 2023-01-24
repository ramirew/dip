cmake_minimum_required(VERSION 3.0.0)

# ! yournameproject
# Depende del nombre del projecto que se desea llamar
# lo recomendado es apuntar a nombre de la carpeta del proyecto

project(yournameproject VERSION 0.1.0)


include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(classification STATIC IMPORTED)
set_target_properties(classification PROPERTIES
    IMPORTED_LOCATION "/home/${user}/dip/build/libclassification.a"
    INTERFACE_INCLUDE_DIRECTORIES "/home/${user}/dip/classification"
)

add_library(featureExtraction STATIC IMPORTED)
set_target_properties(featureExtraction PROPERTIES
    IMPORTED_LOCATION "/home/${user}/dip/build/libfeatureExtraction.a"
    INTERFACE_INCLUDE_DIRECTORIES "/home/${user}/dip/feature_ext_sel"
)

add_library(classificationMetrics  STATIC IMPORTED)
set_target_properties(classificationMetrics  PROPERTIES
    IMPORTED_LOCATION "/home/${user}/dip/build/libclassificationMetrics.a"
    INTERFACE_INCLUDE_DIRECTORIES "/home/${user}/dip/metrics"
)

find_package(OpenMP)

if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# ! dir se debe de apuntar al archivo 
# en caso que este en una carptera nombreCarpeta/main.cpp 
# si esta en la razi de projecto solo  main.cpp

add_executable(yournameproject dir)
target_link_libraries(yournameproject classification featureExtraction classificationMetrics -ldcmdata -ldcmimgle -ldcmimage -ldcmjpeg -lpthread)




 





