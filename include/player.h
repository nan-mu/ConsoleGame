#pragma once
#include "card.h"
#include "global.h"

class player {
   private:
    std::string name = "defined";  // 玩家名字

   public:
    bool isBot = false;      // 是否为ai
    std::vector<card> hand;  // 玩家手上的牌数组
    bool mayIReqCard();  // 后期会写ai，所以单独写一个真人要牌，ai要牌就重载
    bool mayEReqCard(int point);  // 不重载了，新建一个把
    std::string getName();        // 访问玩家名字
    std::string showCard();       // 为玩家明牌
    player(std::string _name);
    player();
};