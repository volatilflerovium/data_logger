# ------------------------------------------------------------------------------
# Header
# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.6)
project(Data-Logger)

#//find_package (Threads)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-Wall")

# ------------------------------------------------------------------------------
# Executable
# ------------------------------------------------------------------------------

include_directories(${CMAKE_BINARY_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(SOURCES1
	example.cpp
	data_logger.cpp
)

add_executable(example ${SOURCES1})
