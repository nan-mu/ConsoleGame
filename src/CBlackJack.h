#include "eventLoop.h"
#include "import.h"

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

class Player {
   private:
    bool isBot = true;             // 是否为ai
    std::string name = "defined";  // 玩家名字

   public:
    std::vector<card> hand;  // 玩家手上的牌数组
    bool mayIReqCard();  // 后期会写ai，所以单独写一个真人要牌，ai要牌就重载
    std::string getName();  // 访问玩家名字
    void showCard();        // 为玩家明牌
    Player(std::string _name);
    Player();
};

class roundManager : private EventLoop {
   private:
    std::vector<card> cardLib;      // 牌库
    std::vector<card> tempCardLib;  // 临时牌库，用于打乱牌库顺序
    std::vector<Player> players;    // 加入游戏的玩家集
    std::vector<int> mustReqCard;   // 判断是否必须要牌
    int turnsNum = 0;               // 回合数计数
    void nextStep(char flag);       // 还没写完 (发现这个没用🌿)
    void showCardsLib();            // debug下查看牌库

   public:
    roundManager();  // 回合管理员初始化，但其实是事件循环初始化时添加53张牌
    ~roundManager();   // 析构函数，还没写完
    void randCards();  // 随机牌库
    void debug();      // debug
    void pvp();        // pvp
    void pve();        // pve
    void play(std::vector<Player>
                  _players);  // 主加载进程，添加第一次要牌任务和要牌尾调用函数
    void play();  // 要牌尾调用函数
    void resCard(
        std::vector<card> &playHand);  // response card 玩家得牌，牌库减牌
    void resCard();  // 遍历玩家vector实现要牌操作轮询
    int getPoint(int playerIndex);  // 计算算分函数
    void getPoint();                // 计算算分函数
    void settlement();              // 结算，还没写完
};

roundManager::roundManager()
    : EventLoop([&]() -> void {
          // init cardLib
          for (size_t i = 0; i < 53; i++) cardLib.push_back(card(i));
      }) {}
roundManager::~roundManager() {}
void roundManager::debug() {
    randCards();
    showCardsLib();
    std::vector<Player> as;
    Player a;  // debug模式下加载一位玩家作测试
    as.push_back(a);
    play(as);
}
void roundManager::pvp() {
    randCards();
    std::vector<Player> as;
    for (size_t i = 0; i < 2; i++) {
        Player a(std::to_string(i));
        as.push_back(a);
    }
    play(as);
}
void roundManager::showCardsLib() {
    enroll(
        [=] {
            for (size_t i = 0; i < cardLib.size(); i++) {
                printf("|%5s%10ld|\n", cardLib[i].getName().c_str(),
                       cardLib[i].getID());
            }
        },
        "打印牌库");
}
void roundManager::play(std::vector<Player> _players) {
    players.swap(_players);
    printf("\n参赛玩家：");
    for (size_t i = 0; i < players.size(); i++)
        printf("%s ", players[i].getName().c_str());
    printf("\n");
    enroll(
        [&]() -> void {
            for (size_t i = 0; i < players.size(); i++)
                mustReqCard.push_back(3);
            turnsNum = 1;
            resCard();
            play();
        },
        "一轮要牌");
    start();
}
void roundManager::play() {
    if (turnsNum <= 5) {
        enroll(
            [&]() -> void {
                turnsNum++;
                resCard();
                play();
            },
            std::to_string(turnsNum) + "轮要牌");
    } else {
        enroll([&]() -> void { getPoint(); }, "计算点数");
    }
}
void roundManager::randCards() {
    enroll(
        [&]() -> void {
            std::vector<int> cardsID, seq;
            for (size_t i = 0; i < cardLib.size(); i++) {
                cardsID.push_back(cardLib[i].getID());
            }
            bubbleSortRank(cardsID, seq);
            for (size_t i = 0; i < cardLib.size(); i++) {
                tempCardLib.push_back(cardLib[seq[i]]);
                tempCardLib[i].newID();
            }
            cardLib.swap(tempCardLib);
            tempCardLib.clear();
        },
        "打乱牌库");
}
void roundManager::resCard(std::vector<card> &playerHand) {
    playerHand.push_back(*cardLib.rbegin());
    cardLib.pop_back();
}
void roundManager::resCard() {
    for (size_t i = 0; i < players.size(); i++) {
        players[i].showCard();
        bool temp = false;
        if (mustReqCard[i] != 0) {
            temp = players[i].mayIReqCard();
            // printf("\ncatch temp:%d", temp);
        }
        if (temp || (mustReqCard[i] == 0)) {
            resCard(players[i].hand);
            if (!temp && mustReqCard[i] == 0) printf("\n本回合已自动要牌");
            mustReqCard[i] = 2;
        } else
            mustReqCard[i]--;
    }
}
int roundManager::getPoint(int playerIndex) {
    int res = 0;
    bool A;
    for (size_t i = 0; i < players[playerIndex].hand.size(); i++) {
        if (!(players[playerIndex].hand[i].getValue() % 13)) {
            res += players[playerIndex].hand[i].getValue();
        } else {
            A = true;
        }
    }
    if (A == true) {
        if (res <= 10) {
            return res + 11;
        } else {
            return res + 1;
        }
    } else {
        return res;
    }
}
void roundManager::getPoint() {
    std::vector<int> winner;
    int curl = 0;
    for (size_t i = 0; i < players.size(); i++) {
        if (curl < getPoint(i)) {
            curl = getPoint(i);
            if (winner.size() != 1) std::vector<int>().swap(winner);
            winner.push_back(i);
        } else if (curl == getPoint(i)) {
            winner.push_back(i);
        }
    }
    printf("这一轮的赢家是：");
    for (size_t i = 0; i < winner.size(); i++) {
        printf("%s", players[winner[i]].getName().c_str());
    }
    printf("\n");
}
Player::Player(std::string _name) { name = _name; }
Player::Player() {}
bool Player::mayIReqCard() {
    char res = 'n';
    printf("%s想要牌吗？(y/n):", name.c_str());
    while ((res = getchar()) == 'y') {
        // printf("catch y");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return (res == 'y');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}
void Player::showCard() {
    printf("\n你现在的手牌有：");
    for (size_t i = 0; i < hand.size(); i++) {
        printf("|%s| ", hand[i].getName().c_str());
    }
    printf("\n");
}
card::card(int _value) {
    value = _value;
    if (_value >= 0 && _value <= 13)
        name += "桃";
    else if (_value >= 14 && _value <= 26)
        name += "心";
    else if (_value >= 27 && _value <= 39)
        name += "梅";
    else if (_value >= 20 && _value <= 52)
        name += "方";
    else
        throw "Unknow card value";

    switch (_value % 13) {
        case 0:
            name += "A";
            break;
        case 1:
            name += "2";
            break;
        case 2:
            name += "3";
            break;
        case 3:
            name += "4";
            break;
        case 4:
            name += "5";
            break;
        case 5:
            name += "6";
            break;
        case 6:
            name += "7";
            break;
        case 7:
            name += "8";
            break;
        case 8:
            name += "9";
            break;
        case 9:
            name += "10";
            break;
        case 10:
            name += "J";
            break;
        case 11:
            name += "Q";
            break;
        case 12:
            name += "K";
            break;
    }
    cardID = randNumber(9);
}
void card::newID() { cardID = randNumber(9); }
long card::getID() { return cardID; }
int card::getValue() { return value; }
std::string card::getName() { return name; }
std::string Player::getName() { return name; }