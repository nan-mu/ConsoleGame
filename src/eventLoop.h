#include "import.h"

// 实现javascript的事件循环，但这个没有内存保护，不检查空指针，没有多线程
// 但很符合我的编程习惯

class EventLoop {
   private:
    /* data */
    std::vector<std::function<void()>> events;  // 事件函数数组
    std::vector<std::string> logs;

   public:
    char state = 'S';  // Sleep Activity Final 运行状态标识
    EventLoop(std::function<void()>
                  intiEvent);  // 构造函数，其实只提供了一个初始化接口
    ~EventLoop();              // 析构函数，也就释放事件函数数组
    int next(int eventId);  // 如题，运行下一步
    void enroll(std::function<void()> event,
                std::string log);  // 向事件函数数组内注册函数
    void start();  // 如题，开始，也就遍历运行事件函数数组
};

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
        LOG(INFO) << "运行id:" + eventId;
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