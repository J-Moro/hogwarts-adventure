#pragma once

#include "Cena.h"
#include "Monstro.h"
#include <string>

using namespace std;

class CenaDeCombate : public Cena {

public:
    
    CenaDeCombate(string nomeArquivo);
    ~CenaDeCombate();

    void exibirCena() override;

    void setMonstro(Monstro monstro);
    void setCenasPosCombate(string sucesso, string derrota);
    string getProximaCena(bool vitoria);

private:
    Monstro monstro;
    string proximaCenaSucesso;
    string proximaCenaDerrota;
};