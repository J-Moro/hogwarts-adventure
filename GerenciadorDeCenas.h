#pragma once

#include <string>
#include <iostream>
#include <set>
#include <memory>

#include "models/Personagens/personagens.h"
#include "models/Personagens/Jogador.h"
#include "Models/Cenas/Cena.h"

using namespace std;

enum ResultadoLeitura{
    Poxa,
    Uau
};

class GerenciadorDeCena{
    public:
    GerenciadorDeCena();
    ~GerenciadorDeCena();

    Cena* getCenaAtual();
    set<string> getCenasVisualizadas();

    void setCenaAtual(unique_ptr<Cena> novaCena);
    
    void carregaCena(string nomeArquivo);
    int salvarJogo(Jogador* personagem, int slot, string pathArquivoAtual);
    string carregarJogo(Personagem& personagem, int slot);

    private:
        unique_ptr<Cena> cenaAtual;
        Personagem* personagem;

        const string CENA_1 = "Arquivos Cena/1.txt";
};