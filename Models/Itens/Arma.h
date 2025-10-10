#pragma once

#include "Item.h"

class Arma : public Item {

public:
    Arma(string name, int faBonus, int damageBonus);
    ~Arma();

};