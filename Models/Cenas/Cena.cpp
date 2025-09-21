#include "Cena.h"

Cena::Cena(string nomeArquivo) : nomeArquivo(nomeArquivo) {
}

Cena::~Cena(){}

string Cena::getNomeArquivo(){
    return nomeArquivo;
}

string Cena::getTexto(){
    return texto;
}