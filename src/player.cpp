#include "player.h"

player::player(std::string _name) { name = _name; }
player::player() {}
bool player::mayIReqCard() {
    char res = 'n';
    printf("\n%s想要牌吗？(y/n):", name.c_str());
    while ((res = getchar()) == 'y') {
        // printf("catch y");
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