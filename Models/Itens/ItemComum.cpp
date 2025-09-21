#include "ItemComum.h"

ItemComum::ItemComum(string name) {
    setName(name);
    setType(c);
    setCombat(false);
    setFaBonus(0);
    setDamageBonus(0);
}

ItemComum::~ItemComum(){}