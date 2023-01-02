#include "player.h"

player::player(std::string _name) { name = _name; }
player::player() {}
bool player::mayIReqCard() {
    char res = 'n';
    printf("%s想要牌吗？(y/n):", name.c_str());
    while ((res = getchar()) == 'y') {
        // printf("catch y");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return (res == 'y');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}
void player::showCard() {
    printf("\n你现在的手牌有：");
    for (size_t i = 0; i < hand.size(); i++) {
        printf("|%s| ", hand[i].getName().c_str());
    }
    printf("\n");
}

std::string player::getName() { return name; }