# 指定最小版本
cmake_minimum_required(VERSION 3.5)

# set(CMAKE_TOOLCHAIN_FILE /home/nan/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
set(spdlog_DIR /home/nan/vcpkg/packages/spdlog_x64-linux/share/spdlog)
set(fmt_DIR /home/nan/vcpkg/packages/fmt_x64-linux/share/fmt)

# 指定项目名称，使用c++(cxx)，头文件路径
project(ConsoleGame)
include_directories(${PROJECT_SOURCE_DIR}/include)

# this is heuristically generated, and may not be correct
find_package(spdlog CONFIG REQUIRED)

# 创建出口并添加源码
add_executable(ConsoleGame main.cpp src/global.cpp src/card.cpp src/player.cpp src/eventLoop.cpp src/roundManager.cpp)

target_link_libraries(ConsoleGame PRIVATE spdlog::spdlog)