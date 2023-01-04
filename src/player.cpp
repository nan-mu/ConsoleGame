#include "player.h"

player::player(std::string _name) { name = _name; }
player::player() {}
bool player::mayIReqCard() {
    char res = 'n';
    printf("%s想要牌吗？(y/n):", name.c_str());
    while ((res = getchar()) == 'y') {
        // printf("catch y");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        spdlog::info("玩家 {} 选择要牌", name);
        return (res == 'y');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    spdlog::info("玩家 {} 选择不要牌", name);
    return false;
}
void player::showCard() {
    printf("\n%s现在的手牌有：", name.c_str());
    std::string cardsStr = "";

    for (size_t i = 0; i < hand.size(); i++) {
        cardsStr += "|" + hand[i].getName() + "| ";
    }
    if (hand.size())
        printf("%s", cardsStr.c_str());
    else
        printf("null");
    spdlog::info("玩家 {} 现有手牌有: {}", name,
                 cardsStr.empty() ? "null" : cardsStr);
    printf("\n");
}

std::string player::getName() { return name; }