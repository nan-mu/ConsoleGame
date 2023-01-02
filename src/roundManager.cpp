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
void roundManager::pvp() {
    randCards();
    std::vector<player> as;
    for (size_t i = 0; i < 2; i++) {
        player a(std::to_string(i));
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
void roundManager::play(std::vector<player> _players) {
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