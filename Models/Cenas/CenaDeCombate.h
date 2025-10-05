#pragma once

#include "Cena.h"
#include "../Personagens/Monstro.h"
#include <string>

using namespace std;

class CenaDeCombate : public Cena {

public:
    
    CenaDeCombate(string nomeArquivo);
    ~CenaDeCombate();

    void exibirCena(Personagem& jogador) override;
    void setMonstro(Monstro* monstro);
    void setCenasPosCombate(string sucesso, string derrota);
    void carregaCena(string nomeArquivo) override;
    string iniciaCombate(Personagem& jogador);
    string getProximaCena(bool vitoria);
    Monstro* getMonstro();

private:
    //private methods
    void executarAtaque(Personagem& jogador);
    bool tentarFuga(Personagem& jogador);
    void exibirStatusCombate(Personagem& jogador);


    Monstro* monstro;
    string proximaCenaSucesso;
    string proximaCenaDerrota;
};