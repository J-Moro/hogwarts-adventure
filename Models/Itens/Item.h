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
    type getType();
    bool getCombat();
    int getFaBonus();
    int getDamageBonus();
    
    void setName(string n);
    void setType(type t);
    void setCombat(bool c);
    void setFaBonus(int v);
    void setDamageBonus(int v);

private:
    string name;
    type typeOfItem;
    bool combat;
    int faBonus;
    int damageBonus;

};