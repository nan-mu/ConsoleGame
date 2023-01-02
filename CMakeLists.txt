# 指定最小版本
cmake_minimum_required(VERSION 3.5)

# 指定项目名称，使用c++(cxx)，头文件路径
project(ConsoleGame LANGUAGES CXX)
include_directories(include)

# 编译静态依赖库
# add_library(card STATIC include/card.h src/card.cpp)
# add_library(player STATIC include/player.h src/player.cpp)
# add_library(eventLoop STATIC include/eventLoop.h src/eventLoop.cpp)
# add_library(roundManager STATIC include/roundManager.h src/roundManager.cpp)

# add_library(p21 STATIC
#  include/card.h src/card.cpp
#  include/player.h src/player.cpp
#  include/eventLoop.h src/eventLoop.cpp
#  include/roundManager.h src/roundManager.cpp
# )

# 可执行文件出口
add_executable(ConsoleGame 
 main.cpp
 include/global.h src/global.cpp
 include/card.h src/card.cpp
 include/player.h src/player.cpp
 include/eventLoop.h src/eventLoop.cpp
 include/roundManager.h src/roundManager.cpp
)
# add_executable(test test.cpp)

# 链接静态库
# target_link_libraries(player card)
# target_link_libraries(roundManager card)
# target_link_libraries(roundManager player)
# target_link_libraries(roundManager eventLoop)
# target_link_libraries(ConsoleGame roundManager)
# target_link_libraries(ConsoleGame p21)