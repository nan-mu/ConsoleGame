#include "CBlackJack.h"
#include "import.h"

using namespace std;

int main() {
    system(
        "chcp 65001");  // 麻了，windows你就是个贵物，你还抱着你这gkb干吗呀哎呦
    roundManager p21;  // 初始化回合管理员
    // 交付环境下不使用debug，但在此处使用Player提供的接口编写ai逻辑，并在此处将玩家
    // p21.debug();  // debug内加载了用于测试的玩家对象
    p21.pvp();  // 交付环境使用

    return printf("\n");
}
