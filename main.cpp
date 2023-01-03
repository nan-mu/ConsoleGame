#include "roundManager.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

using namespace std;

int main() {
    // 麻了，windows你就是个贵物，你还抱着你这gkb干吗呀哎呦
    system("chcp 65001");

    // 测试spdlog
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical(
        "Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    spdlog::set_level(spdlog::level::debug);  // Set global log level to debug
    spdlog::debug("This message should be displayed..");

    // change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    // Compile time log levels
    // define SPDLOG_ACTIVE_LEVEL to desired level
    SPDLOG_TRACE("Some trace message with param {}", 42);
    SPDLOG_DEBUG("Some debug message");

    // Set the default logger to file logger
    auto file_logger =
        spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
    spdlog::set_default_logger(file_logger);
    roundManager p21;  // 初始化回合管理员
    // 交付环境下不使用debug，但在此处使用Player提供的接口编写ai逻辑，并在此处将玩家
    // p21.debug();  // debug内加载了用于测试的玩家对象
    p21.pvp();  // 交付环境使用

    return printf("\n");
}
