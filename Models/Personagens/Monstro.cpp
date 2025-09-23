#include "Monstro.h"

Monstro::Monstro(){

    boo = true;

}

Monstro::~Monstro(){

}

void Monstro::setBoo(bool value){

    boo = value;

}

bool Monstro::getBoo(){

    return boo;

}