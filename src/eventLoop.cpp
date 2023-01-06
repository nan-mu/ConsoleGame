#include "eventLoop.h"

EventLoop::EventLoop(std::function<void()> intiEvent) {
    events.push_back(intiEvent);
    descriptions.push_back("事件循环初始化");
}

void EventLoop::enroll(std::function<void()> event,
                       std::string description = "undefined description") {
    events.push_back(event);
    descriptions.push_back(description);
    // printf("INT: 发现注册 %s\n", description.c_str());
    spdlog::info("发现注册: |id{}| |des {}|", events.size() - 1, description);
    if (state == 'S') state = 'A';
}

void EventLoop::start() {
    int eventId = 0;
    spdlog::info("事件循环开始\n");
    while (state == 'A') {
        eventId = next(eventId);
    };
}

int EventLoop::next(int eventId) {
    if (eventId < events.size()) {
        // printf("INT: 正在运行 id:%d\n", eventId);
        spdlog::info("正在运行: |id{}| |des {}|", eventId,
                     descriptions[eventId - 1]);
        events[eventId]();
    } else {
        state = 'F';
    }
    return eventId + 1;
}

EventLoop::~EventLoop() {
    std::vector<std::function<void()>>().swap(events);
    std::vector<std::string>().swap(descriptions);
}