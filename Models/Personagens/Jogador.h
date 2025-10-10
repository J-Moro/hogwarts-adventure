#pragma once

#ifndef JOGADOR_H 
#define JOGADOR_H 

#include "personagens.h"
#include "../Itens/Arma.h"

class Jogador: public Personagem{
public:

    Jogador();
    ~Jogador();
    
    bool equiparArma(int numeroItem);

private:
    

};

#endif 