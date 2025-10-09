#pragma once
#include "personagens.h"
#include "../Itens/Arma.h"

class Jogador: public Personagem{
public:

    Jogador();
    ~Jogador();
    bool equiparArma(string itemName);

private:

    Arma* armaEquipada = nullptr;

};