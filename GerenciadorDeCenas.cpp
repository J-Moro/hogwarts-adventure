#include <iostream>
#include <fstream>
#include <stdexcept>
#include "GerenciadorDeCenas.h"


GerenciadorDeCena::GerenciadorDeCena(){}
GerenciadorDeCena::~GerenciadorDeCena(){}

void GerenciadorDeCena::carregaCena(string nomeArquivo){
    try {    
        ifstream arquivo(nomeArquivo);

        if (!arquivo.is_open()) {
            throw runtime_error("Erro ao abrir arquivo: " + nomeArquivo);
        }

        string primeiraPalavra;
        arquivo >> primeiraPalavra;
        arquivo.close();

        if (primeiraPalavra == "Uau" || primeiraPalavra == "Poxa") {

        } else {
            
        }
    }
}
