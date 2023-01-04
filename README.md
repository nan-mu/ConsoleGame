# 21点游戏

写完力～
其实还差跨平台🤥
## 思路

使用类似javascript的事件循环的思路管理游戏动作，详见eventLoop.h

生成牌管理员管理游戏，详见CBlackJack.h

# 随手记

> 这里的东西我写着写着就不管了...项目代码写完我再补，凑合着看吧

* classes
  * player:
    * args:
      * cardsInHand: vector<card>
      * point: int
      * history: vector<roundRes>
  * AIplayer:
    * base on player
    * function:
      * rule
  * roundManager:
    * args:
      * cardLib: vector<card>
      * players: vector<player>
      * rules: temples <class ruleFunction(vector<player>, vector<card>)> //在想结构的时候没料到使用模板会遇到一些问题，然后是啥问题我居然忘了！但解决方案是使用functional标准库
      * isEnd: temples <class ruleFunction(vector<player>, vector<card>)>
      * isWin: temples <class ruleFunction(vector<player>, vector<card>)>
    * function:
      * randCards
        * void
      * reqCard: player
        * args: player, cardID
      * endRound:
        * args: vector<player> as winners, vector<player> as losers
        * void
      * resCard:
        * args: player, card
      * ruleLoad:(构造)
        * args: temples <class winRule(vector<player>, vector<card>)>
        * TODO 给定何时发牌，何时结束，何时赢
* struct
  * card
    * name: string
    * cardID: string
  * roundRes
    * roundID: string
    * roundPlayer: string
    * res: bool
    * roundLabel: string