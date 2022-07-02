cmake_minimum_required(VERSION 3.16)

include(GenerateExportHeader)
project(qubic_verify CXX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_COMPILER "g++")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")  
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpsabi") 
endif()


set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

include_directories("../algorithms")
include_directories("../")

add_library(qubic_verify SHARED qubic_verify_lib.cpp "../algorithms/FourQ.cpp")
generate_export_header(qubic_verify
    BASE_NAME qubic_verify
    EXPORT_MACRO_NAME QUBIC_VERIFY_EXPORT
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/qubic_verify_Export_${CMAKE_SYSTEM_NAME}.h
)