#pragma once
#include <string>
#include <iostream>

using namespace std;

enum type{c,r,w};

class Item {

public:
    Item();
    virtual ~Item();

    string getName();
    void setName(string n);
    type getType();
    void setType(type t);
    bool getCombat();
    void setCombat(bool c);
    int getFaBonus();
    void setFaBonus(int v);
    int getDamageBonus();
    void setDamageBonus(int v);

private:
    string name;
    type typeOfItem;
    bool combat;
    int faBonus;
    int damageBonus;

};