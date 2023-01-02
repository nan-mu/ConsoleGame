# 指定最小版本
cmake_minimum_required(VERSION 3.5)

# 指定项目名称，使用c++(cxx)，头文件路径
project(ConsoleGame LANGUAGES CXX)
include_directories(${PROJECT_SOURCE_DIR}/include)

# 编译静态依赖库
add_library(global SHARED include/global.h src/global.cpp)
add_library(card SHARED include/card.h src/card.cpp)
add_library(player SHARED include/player.h src/player.cpp)
add_library(eventLoop SHARED include/eventLoop.h src/eventLoop.cpp)
add_library(roundManager SHARED include/roundManager.h src/roundManager.cpp)

# add_library(p21 STATIC
#  include/global.h src/global.cpp
#  include/card.h src/card.cpp
#  include/player.h src/player.cpp
#  include/eventLoop.h src/eventLoop.cpp
#  include/roundManager.h src/roundManager.cpp
# )

# 可执行文件出口
# add_executable(ConsoleGame 
#  main.cpp
#  include/global.h src/global.cpp
#  include/card.h src/card.cpp
#  include/player.h src/player.cpp
#  include/eventLoop.h src/eventLoop.cpp
#  include/roundManager.h src/roundManager.cpp
# )
# add_executable(test test.cpp)
add_executable(ConsoleGame main.cpp)

# 链接静态库
# target_link_libraries(card PRIVATE global)
# target_link_libraries(player PRIVATE card)
# target_link_libraries(player PRIVATE global)
target_link_libraries(roundManager global)
# target_link_libraries(roundManager PRIVATE card)
# target_link_libraries(roundManager PRIVATE player)
# target_link_libraries(roundManager PRIVATE eventLoop)
# target_link_libraries(ConsoleGame PRIVATE global)
# target_link_libraries(ConsoleGame PRIVATE roundManager)
target_link_libraries(ConsoleGame roundManager global eventLoop player card global)

