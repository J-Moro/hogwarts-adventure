#include "personagens.h"

class Monstro: public Personagem{
public:

    Monstro();
    ~Monstro();

    void transferirItens(Personagem &oponente);

private:

};