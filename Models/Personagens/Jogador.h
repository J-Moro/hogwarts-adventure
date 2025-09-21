#include "personagens.h"
#include "../Itens/Item.h"

class Jogador: public Personagem{
public:

    Jogador();
    ~Jogador();

    void setTesouro(int num);
    int getTesouro();
    Item* addItem();
    Item* deleteItem();
    Item* getInventario();


private:

    int tesouro;    //qtd de dinheiro
    Item* inventario;

};