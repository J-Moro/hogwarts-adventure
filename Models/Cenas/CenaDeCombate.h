#pragma once

#include "Cena.h"
#include "../Personagens/Monstro.h"
#include <string>

using namespace std;

class CenaDeCombate : public Cena {

public:
    
    CenaDeCombate(string nomeArquivo);
    ~CenaDeCombate();

    void exibirCena() override;
    void setMonstro(Monstro* monstro);
    void setCenasPosCombate(string sucesso, string derrota);
    void carregaCena(string nomeArquivo);
    string getProximaCena(bool vitoria);
    Monstro* getMonstro();

private:
    Monstro* monstro;
    string proximaCenaSucesso;
    string proximaCenaDerrota;
};