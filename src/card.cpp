#include "card.h"

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