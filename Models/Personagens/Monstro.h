#pragma once

#include "personagens.h"

class Monstro: public Personagem{
public:

    Monstro(string nome, int habilidade, int energia, int sorte, int tesouro, int provisoes, Item* inventario);
    ~Monstro();

    void transferirItens(Personagem &oponente);

private:

};