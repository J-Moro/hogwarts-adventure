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
    void setBonusSorte(bool status);

    string getNome();
    int getHabilidade();
    int getEnergia();
    int getSorte();
    int getTesouro();
    int getProvisoes();
    int getMaxItems();
    int getQuantidadeItens();
    bool getBonusSorte();

    void recebeDano();
    bool testaSorte();
    int calcFA();
    bool addItem(Item newItem);
    bool removeItem(string itemName);
    bool possuiItem(string nomeItem);
    virtual void mostrarInventario();
    void setInventario(Item* inventario);
    Item* getInventario();
    
private:
    string nome;    
    int habilidade;
    int energia;
    int sorte;

    bool bonusSorte;
    int tesouro;
    int provisoes;
    static const int MAX_ITEMS = 10;
    int itemCount;

protected:
    Item* inventarioUsuario;

};