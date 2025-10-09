#pragma once
#include "Item.h"

class Armadura : public Item {
    
    public:
        Armadura(string name, int faBonus, int damageBonus);
        ~Armadura() {};
};