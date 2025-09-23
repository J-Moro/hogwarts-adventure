#include "Monstro.h"

Monstro::Monstro(){


}

Monstro::~Monstro(){

}

void Monstro::transferirItens(Personagem &oponente) {
    
    oponente.setTesouro(oponente.getTesouro() + this->getTesouro());
    this->setTesouro(0);
    oponente.setProvisoes(oponente.getProvisoes() + this->getProvisoes());
    this->setProvisoes(0);
    for (int i = 0; i < 10; i++) {
        if (this->addItem(oponente.inventario[i])) {
            oponente.inventario[i] = Item(); // Remove o item do oponente
        } else {
            break; // Inventário cheio, para de transferir
        }
    }
}
