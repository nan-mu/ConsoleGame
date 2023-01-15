#pragma once
#include "card.h"
#include "eventLoop.h"
#include "global.h"
#include "player.h"

/// @brief 管理p21游戏的所有活动
class roundManager : private EventLoop {
   private:
    /// @brief 牌库
    std::vector<card> cardLib;
    /// @brief 临时牌库，用于打乱牌库顺序
    std::vector<card> tempCardLib;
    /// @brief 加入游戏的玩家集
    std::vector<player> players;
    /// @brief debug下查看牌库
    void showCardsLib();
    /// @brief 回合数
    int turnsNum;

   public:
    /// @brief
    /// 回合管理员初始化，但其实只在事件循环初始化时注册了添加53张牌的函数
    roundManager();
    /// @brief 析构函数
    ~roundManager();
    /// @brief 用eventLoop.enrool注册随机牌库的函数
    void randCards();
    /// @brief debug模式下开始游戏，这时会向控制台打印牌库，并只有一个玩家参加
    void debug();
    /// @brief pvp模式下加载游戏，根据num加载玩家数量
    /// @param cusName 是否自定义玩家的名字
    void pvp(int num, bool cusName);
    /// @brief pve模式下加载游戏，一个玩家一个电脑
    /// @param cusName 是否自定义玩家的名字
    void pve(bool cusName);
    /// @brief 游戏开始时运行，添加第一次要牌任务和要牌尾调用函数
    /// @param _players 参与的玩家的数组
    void play(std::vector<player> _players);
    /// @brief 要牌尾调用函数
    void play();
    /// @brief response card 玩家得牌，牌库减牌
    /// @param playHand 对应玩家的手牌容器
    void resCard(std::vector<card> &playHand);
    /// @brief 遍历roundManager.players实现要牌操作轮询
    void resCard();
    /// @brief 计算算分函数
    /// @param playerIndex 玩家在roundManager.players中的下标
    int getPoint(int playerIndex);
    /// @brief 遍历计算分数并得出优胜者
    void getPoint();  // 计算算分函数
};
