#pragma once
#include "card.h"
#include "global.h"

/// @brief 玩家对象，对局开始时将被放入STL容器中
class player {
   private:
    /// @brief
    /// 玩家名字，在roundManager::pvp和roundManager::pvp设置cusNam为true时会请求玩家自定义，否则系统自动填充
    std::string name = "defined";

   public:
    /// @brief 标记是否为机器人
    bool isBot = false;
    /// @brief 玩家手上的牌库
    std::vector<card> hand;
    /// @brief
    /// 当isBot为false时roundManager会调用该函数，该函数将通过控制台询问玩家是否要牌。
    bool mayIReqCard();
    /// @brief
    /// 当isBot为true时roundManager会调用该函数，该函数将通过point的值判断是否需要要牌。
    bool mayEReqCard(int point);
    /// @brief 访问玩家的名字
    std::string getName();
    /// @brief 向控制台和日志打印玩家牌库，打印牌的name
    std::string showCard();
    /// @brief 生成真人玩家对象
    /// @param _name 名字
    player(std::string _name);
    /// @brief 生成电脑玩家对象
    player();
};