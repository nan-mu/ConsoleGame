#pragma once
#include "global.h"

class card {
   private:
    std::string name;
    long cardID;
    int value;

   public:
    card(int _value);       // 牌对象的构造函数
    void newID();           // 为牌新建唯一标识，且只能随机
    long getID();           // 访问牌标识
    int getValue();         // 访问牌面值
    std::string getName();  // 访问牌面值
};