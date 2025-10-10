#include "Item.h"

Item::Item(void){}
Item::~Item(void){}

string Item::getName() {
    return name;
}

void Item::setName(string n) {
    name = n;
}

type Item::getType() {
    return typeOfItem;
}

void Item::setType(type t) {
    typeOfItem = t;
}

bool Item::getCombat() {
    return combat;
}

void Item::setCombat(bool c) {
    combat = c;
}

int Item::getFaBonus() {
    return faBonus;
}

void Item::setFaBonus(int v) {
    faBonus = v;
}

int Item::getDamageBonus() {
    return damageBonus;
}

void Item::setDamageBonus(int v) {
    damageBonus = v;
}