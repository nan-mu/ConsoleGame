#pragma once

#include "card.h"
#include "import.h"

class player {
   private:
    bool isBot = true;             // 是否为ai
    std::string name = "defined";  // 玩家名字

   public:
    std::vector<card> hand;  // 玩家手上的牌数组
    bool mayIReqCard();  // 后期会写ai，所以单独写一个真人要牌，ai要牌就重载
    std::string getName();  // 访问玩家名字
    void showCard();        // 为玩家明牌
    player(std::string _name);
    player();
};