#pragma once
#include "eventLoop.h"
#include "include.h"
#include "player.h"

class roundManager : private EventLoop {
   private:
    std::vector<card> cardLib;      // 牌库
    std::vector<card> tempCardLib;  // 临时牌库，用于打乱牌库顺序
    std::vector<player> players;    // 加入游戏的玩家集
    std::vector<int> mustReqCard;   // 判断是否必须要牌
    int turnsNum = 0;               // 回合数计数
    // void nextStep(char flag);       // 还没写完 (发现这个没用🌿)
    void showCardsLib();  // debug下查看牌库

   public:
    roundManager();  // 回合管理员初始化，但其实是事件循环初始化时添加53张牌
    ~roundManager();   // 析构函数，还没写完
    void randCards();  // 随机牌库
    void debug();      // debug
    void pvp();        // pvp
    // void pve();        // pve，没写完
    void play(std::vector<player>
                  _players);  // 主加载进程，添加第一次要牌任务和要牌尾调用函数
    void play();  // 要牌尾调用函数
    void resCard(
        std::vector<card> &playHand);  // response card 玩家得牌，牌库减牌
    void resCard();  // 遍历玩家vector实现要牌操作轮询
    int getPoint(int playerIndex);  // 计算算分函数
    void getPoint();                // 计算算分函数
    // void settlement();              // 结算，还没写完
};
