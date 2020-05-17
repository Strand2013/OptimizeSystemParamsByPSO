project(zbOperation)
cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 11)
SET(HEADER include)
INCLUDE_DIRECTORIES(${HEADER})
ADD_SUBDIRECTORY(src)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

# 添加可执行文件的源文件
ADD_EXECUTABLE(zbOperationRun ${DIR_SRCS})
TARGET_LINK_LIBRARIES(zbOperationRun Code)