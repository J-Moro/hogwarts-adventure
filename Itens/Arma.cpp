#include "Arma.h"

Arma::Arma(string name, int faBonus, int damageBonus) {
    setName(name);
    setType(w);              
    setCombat(true);         
    setFaBonus(faBonus);     
    setDamageBonus(damageBonus);
}

Arma::~Arma(){}