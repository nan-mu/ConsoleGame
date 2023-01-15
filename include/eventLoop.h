#pragma once
#include "global.h"

/// @brief
/// 实现javascript的事件循环，但这个没有内存保护，不检查空指针，没有多线程，但很符合我的编程习惯
class EventLoop {
   private:
    /// @brief 函数对象容器（当然我c++的函数不是一个对象，但凑合着理解吧）
    std::vector<std::function<void()>> events;
    /// @brief 函数对象对应的解释容器
    std::vector<std::string> descriptions;

   public:
    /// @brief Sleep Activity Final 运行状态标识，初始状态为Sleep
    char state = 'S';
    /// @brief 构造函数，其实只提供了一个初始化接口
    EventLoop(std::function<void()> intiEvent);
    /// @brief
    /// 析构函数，也就释放事件函数数组，但说实话我不知道到底要不要释放STL容器
    ~EventLoop();
    /// @brief 如题，运行this.events[eventId]，并返回eventId+1
    int next(int eventId);
    /// @brief 向this.events添加函数对象
    void enroll(std::function<void()> event, std::string log);
    /// @brief // 如题，开始，也就遍历运行事件函数数组
    void start();
};

// > **EventLoop**包含一个`std::vector<std::function<void()>>
// events`用于存储函数，`void enroll(std::function void()  event, std::string
// log)`用于向`events`中添加函数，而这些函数**什么时候被执行**就由`EventLoop`的`void
// enroll(std::function void()  event, std::string log)`和`void start()`控制。