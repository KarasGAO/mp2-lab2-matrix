cmake_minimum_required(VERSION 3.30)
set(PROJECT_NAME_STR Matrix)
project(${PROJECT_NAME_STR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include2)
file(GLOB PATH_STR ${CMAKE_CURRENT_SOURCE_DIR}/include2/*.h
				${CMAKE_CURRENT_SOURCE_DIR}/samples/*.cpp)
add_executable(${PROJECT_NAME_STR} ${PATH_STR} samples/*.cpp)
