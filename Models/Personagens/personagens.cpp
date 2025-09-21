#include "personagens.h"

Personagem::Personagem(){

}

Personagem::~Personagem(){
    
}

void Personagem::setNome(string n){

    nome = n;

}

void Personagem::setHabilidade(int num){

    habilidade = num;

}

void Personagem::setEnergia(int num){

    energia = num;

}

void Personagem::setSorte(int num){

    sorte = num;

}

string Personagem::getNome(){

    return nome;

}

int Personagem::getHabilidade(){

    return habilidade;

}

int Personagem::getEnergia(){

    return energia;

}

int Personagem::getSorte(){

    return sorte;

}