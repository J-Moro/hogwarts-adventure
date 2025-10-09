#include "Cena.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Cena::Cena(string nomeArquivo) : nomeArquivo(nomeArquivo) {
}

Cena::~Cena(){}


string Cena::getNomeArquivo(){
    return nomeArquivo;
}

void Cena::setNomeArquivo(string nomeArquivo) {
    this->nomeArquivo = nomeArquivo;
}

string Cena::getTexto(){
    return this->texto;
}

void Cena::setTexto(string t) {
    this->texto = t;
}

void Cena::lerConteudoBruto(string nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro ao abrir arquivo de cena: " + nomeArquivo);
    }
    
    stringstream buffer;
    
    buffer << arquivo.rdbuf();
    this->texto = buffer.str(); 
    
    arquivo.close();
}