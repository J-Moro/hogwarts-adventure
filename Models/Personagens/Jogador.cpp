#include "Jogador.h"

Jogador::Jogador(){

    inventario = new Item[10];

}

Jogador::~Jogador(){

    delete inventario;

}

void Jogador::setTesouro(int num){

    tesouro = num;

}

int Jogador::getTesouro(){

    return tesouro;

}

Item* getInventario(){

    return inventario;

}