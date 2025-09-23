#pragma once

#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "../Itens/Item.h"

using namespace std;

class Personagem {
public:

    Personagem();
    ~Personagem();

    void setNome(string n);
    void setHabilidade(int num);
    void setEnergia(int num);
    void setSorte(int num);
    void setTesouro(int num);
    void setProvisoes(int num);
    string getNome();
    int getHabilidade();
    int getEnergia();
    int getSorte();
    int getTesouro();
    int getProvisoes();

    void recebeDano();
    bool testaSorte();
    int calcFA();
    bool addItem(Item newItem);
    void mostrarInventario();

    Item* inventario;

private:

    string nome;    
    int habilidade;
    int energia;
    int sorte;

    int tesouro;
    int provisoes;
    static const int MAX_ITEMS = 10;
    int itemCount;

};