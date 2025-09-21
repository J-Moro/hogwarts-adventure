#pragma once

#include <string>
#include <iostream>

using namespace std;

class Personagem {
public:

    Personagem();
    ~Personagem();

    void setNome(string n);
    void setHabilidade(int num);
    void setEnergia(int num);
    void setSorte(int num);
    string getNome();
    int getHabilidade();
    int getEnergia();
    int getSorte();


private:

    string nome;    
    int habilidade;
    int energia;
    int sorte;

};