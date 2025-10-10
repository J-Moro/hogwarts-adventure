#pragma once

#include <string>

#include "Cena.h"
#include "../Personagens/Monstro.h"

using namespace std;

class CenaDeCombate : public Cena {

public:
    CenaDeCombate(string nomeArquivo);
    ~CenaDeCombate();

    Monstro* getMonstro();

    void setMonstro(Monstro* monstro);

    string exibirCena(Personagem& jogador) override;
    void carregaCena(string nomeArquivo) override;
    string iniciaCombate(Personagem& jogador);
    string getProximaCena(bool vitoria);

private:
    void executarAtaque(Personagem& jogador);
    bool tentarFuga(Personagem& jogador);
    void exibirStatusCombate(Personagem& jogador);

    Monstro* monstro;
    string proximaCenaSucesso;
    string proximaCenaDerrota;
    
};