#pragma once
#include "global.h"

/// @brief 牌对象，一般被放在容器中
class card {
   private:
    /// @brief 牌名，如梅7
    std::string name;
    /// @brief 牌的唯一标识，也用于随机牌的顺序
    long cardID;
    /// @brief 牌的面值，范围在0-52，具体实现请查看构造函数
    int value;

   public:
    /// @brief 构建了this.name, this.cardID, this.value
    /// @param _value 传入值将作为this.value并用于构建this.name
    card(int _value);  // 牌对象的构造函数
    /// @brief 为牌新建唯一标识，且只能随机
    void newID();
    /// @return 返回cardID
    long getID();
    /// @return 返回value
    int getValue();
    /// @return 返回name
    std::string getName();
};