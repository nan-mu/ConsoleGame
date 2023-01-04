#include "roundManager.h"

int main() {
    // 麻了，windows你就是个贵物，你还抱着你这gkb干吗呀哎呦
    system("chcp 65001");
    auto t =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // 转为字符串
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d-%H-%M-%S");
    std::string str_time = ss.str();
    auto file_logger = spdlog::basic_logger_st(
        "basic_logger", "../logs/p21_" + str_time + ".log");
    spdlog::set_default_logger(file_logger);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e][%l]: %v");
    spdlog::info("game start!");

    roundManager p21;  // 初始化回合管理员
    //  交付环境下不使用debug，但在此处使用Player提供的接口编写ai逻辑，并在此处将玩家
    p21.debug();  // debug内加载了用于测试的玩家对象
    // p21.pvp(2, false);  // 交付环境使用

    return printf("\n");
}
