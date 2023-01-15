#include "player.h"

player::player(std::string _name) { name = _name; }
player::player() {
    name = "电脑玩家" + std::to_string(randNumber(3));
    isBot = true;
}
bool player::mayEReqCard(int point) {
    bool des;
    if (point >= 21)
        des = false;
    else {
        if ((21 - point) < (int)randNumber(2))
            des = false;
        else
            des = true;
    }
    if (des) {
        printf("\n电脑选择要牌");
        spdlog::info("电脑选择要牌");
    } else {
        printf("\n电脑选择不要牌");
        spdlog::info("电脑选择不要牌\n");
    }
    return des;
}
bool player::mayIReqCard() {
    char res = 'n';
    printf("\n%s想要牌吗？(y/n):", name.c_str());
    while ((res = getchar()) == 'y') {
        // 清除缓存
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        spdlog::info("要牌阶段: 玩家|{}|选择要牌", name);
        return (res == 'y');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    spdlog::info("要牌阶段: 玩家|{}|选择不要牌", name);
    return false;
}
std::string player::showCard() {
    std::string cardsStr = "";
    cardsStr += "" + name + "现在的手牌有:";
    for (size_t i = 0; i < hand.size(); i++)
        cardsStr += " |" + hand[i].getName() + "|";
    if (!hand.size()) cardsStr += "null";
    spdlog::info("展示手牌: 玩家|{}|，{}", name, cardsStr);
    return cardsStr;
}
std::string player::getName() { return name; }