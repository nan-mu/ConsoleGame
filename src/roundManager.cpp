#include "roundManager.h"

#include "global.h"

roundManager::roundManager()
    : EventLoop([&]() -> void {
          // init cardLib
          for (size_t i = 0; i < 53; i++) cardLib.push_back(card(i));
      }) {}
roundManager::~roundManager() {}
void roundManager::debug() {
    randCards();
    showCardsLib();
    std::vector<player> as;
    player a;  // debug模式下加载一位玩家作测试
    as.push_back(a);
    play(as);
}
/// @brief 根据玩家人数开始对局
/// @param num 玩家人数
/// @param cusName 是否自定义玩家名字
void roundManager::pvp(int num, bool cusName) {
    randCards();
    std::vector<player> as;
    for (int i = 0; i < num; i++) {
        std::string name = "";
        if (cusName) {
            printf("请输入第%d位玩家的名字:", i + 1);
            getline(std::cin, name);
        } else {
            name = "自动编号(" + std::to_string(i + 1) + ")";
        }
        spdlog::info("玩家 {}初始化", name);
        player a(name);
        as.push_back(a);
    }
    spdlog::info("玩家初始化结束, 载入{}位玩家", num);
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
void roundManager::play(std::vector<player> _players) {
    players.swap(_players);
    printf("\n参赛玩家：");
    for (size_t i = 0; i < players.size(); i++)
        printf("%s ", players[i].getName().c_str());
    printf("\n");
    enroll(
        [&]() -> void {
            for (size_t i = 0; i < players.size(); i++)
                for (int ii = 0; ii < 3; ii++) resCard(players[i].hand);
            turnsNum = 4;
            resCard();
            play();
        },
        "1轮要牌，强制给牌");
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
            std::to_string(turnsNum + 1) + "轮要牌");
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
        printf("%s", players[i].showCard().c_str());
        if (players[i].mayIReqCard()) resCard(players[i].hand);
    }
}
int roundManager::getPoint(int playerIndex) {
    int res = 0;
    bool A = false;
    for (size_t i = 0; i < players[playerIndex].hand.size(); i++) {
        if ((players[playerIndex].hand[i].getValue() % 13) != 0) {
            spdlog::info("算牌阶段: 计算牌|{}| |{}| res|{}|",
                         players[playerIndex].hand[i].getName(),
                         players[playerIndex].hand[i].getValue(), res);
            res += (players[playerIndex].hand[i].getValue() % 13) + 1;
        } else {
            // 记录玩家是否持有A
            A = true;
            res += 1;
        }
    }
    if (A) {
        // 玩家手中有A时,判断对玩家有利的情况
        if (res <= 10) {
            res += 11;
        }
    }
    players[playerIndex].showCard();
    spdlog::info("算分阶段: 玩家|{}|的得分为|{}|",
                 players[playerIndex].getName(), res);
    return res;
}
void roundManager::getPoint() {
    std::vector<int> winner;
    int winnerPoint = 0, tempPoint = 21;
    bool winnerType = false;  // 用false表示超过21分，用true表示没超过21分
    spdlog::info("对局结束，计算分数");
    for (size_t i = 0; i < players.size(); i++) {
        tempPoint = getPoint(i);
        if (!i) winnerPoint = tempPoint;
        if (tempPoint <= 21) {
            if (winnerType) {
                if (winnerPoint < tempPoint) {
                    winnerPoint = tempPoint;
                    // 清除平局情况
                    std::vector<int>().swap(winner);
                    winner.push_back(i);
                } else if (winnerPoint == tempPoint) {
                    // 平局情况
                    winner.push_back(i);
                }
            }
            winnerType = true;
        } else {
            if (winnerType)
                continue;
            else {
                if (winnerPoint > tempPoint) {
                    winnerPoint = tempPoint;
                    // 清除平局情况
                    std::vector<int>().swap(winner);
                    winner.push_back(i);
                } else if (winnerPoint == tempPoint) {
                    // 平局情况
                    winner.push_back(i);
                }
            }
        }
    }
    printf("这一轮的赢家是：");
    for (size_t i = 0; i < winner.size(); i++) {
        printf("[%s]", players[winner[i]].getName().c_str());
        spdlog::info("算分阶段: 胜者为|{}|", players[winner[i]].getName());
    }
    printf("\n");
}