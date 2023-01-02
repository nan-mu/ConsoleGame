# 指定最小版本
cmake_minimum_required(VERSION 3.5)

# 指定项目名称，使用c++(cxx)，头文件路径
project(ConsoleGame LANGUAGES CXX)
include_directories(include)

# 编译静态依赖库
add_library(card STATIC card.h card.cpp)
add_library(player STATIC player.h player.cpp)
add_library(eventLoop STATIC eventLoop.h eventLoop.cpp)
add_library(roundManager STATIC roundManager.h roundManager.cpp)

# 可执行文件出口
add_executable(ConsoleGame main.cpp)
# add_executable(test test.cpp)

# 链接静态库
target_link_libraries(ConsoleGame card)
target_link_libraries(ConsoleGame player)
target_link_libraries(ConsoleGame eventLoop)
target_link_libraries(ConsoleGame roundManager)