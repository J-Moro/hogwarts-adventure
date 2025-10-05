#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "GerenciadorDeCenas.h"
#include "Models/Cenas/Cena.h"
#include "Models/Cenas/CenaDeCombate.h"
#include "Models/Cenas/CenaDeTexto.h"
#include "Models/Itens/ItemComum.h"

using namespace std;

GerenciadorDeCena::GerenciadorDeCena() {}
GerenciadorDeCena::~GerenciadorDeCena() {}

void GerenciadorDeCena::carregaCena(string nomeArquivo)
{

    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir arquivo: " + nomeArquivo);
    }

    string primeiraPalavra;
    arquivo >> primeiraPalavra;
    arquivo.close();

    // Limpa a cena anterior para evitar vazamento de memória
    if (cenaAtual != nullptr) {
        delete cenaAtual;
        cenaAtual = nullptr;
    }

    // Instancia a cena correta
    if (primeiraPalavra == "Uau" || primeiraPalavra == "Poxa") {
        cenaAtual = new CenaDeCombate(nomeArquivo);
    }
    else {
        cenaAtual = new CenaDeTexto(nomeArquivo);
    }

    cenaAtual->lerConteudoBruto(nomeArquivo);

    cenaAtual->carregaCena(nomeArquivo);
}

Cena* GerenciadorDeCena::getCenaAtual() {
    return this->cenaAtual;
}
