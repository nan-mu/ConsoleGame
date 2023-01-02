#include "eventLoop.h"

EventLoop::EventLoop(std::function<void()> intiEvent) {
    events.push_back(intiEvent);
}

void EventLoop::enroll(std::function<void()> event, std::string log) {
    events.push_back(event);
    logs.push_back(log);
    printf("INT: 发现注册 %s\n", log.c_str());
    if (state == 'S') state = 'A';
}

void EventLoop::start() {
    int eventId = 0;
    while (state == 'A') {
        eventId = next(eventId);
        // LOG(INFO) << "运行id:" + eventId;
    };
}

int EventLoop::next(int eventId) {
    if (eventId < events.size()) {
        printf("INT: 正在运行 id:%d\n", eventId);
        events[eventId]();
    } else
        state = 'F';
    return eventId + 1;
}

EventLoop::~EventLoop() { std::vector<std::function<void()>>().swap(events); }