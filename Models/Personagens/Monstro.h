#include "personagens.h"

class Monstro: public Personagem{
public:

    Monstro();
    ~Monstro();

    void setBoo(bool value);
    bool getBoo();

private:

    bool boo;

};