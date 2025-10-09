#pragma once
#include <string>
#include <iostream>
#include <set>
#include <memory>
#include "models/Personagens/personagens.h"
#include "models/Personagens/Jogador.h"
#include "Models/Cenas/Cena.h"

using namespace std;

enum TipoCena {
    CENA_TEXTO,
    CENA_COMBATE
};

enum ResultadoLeitura{
    Poxa,
    Uau
};

class GerenciadorDeCena{
    public:

    GerenciadorDeCena();
    ~GerenciadorDeCena();

    void carregaCena(string nomeArquivo);
    Cena* getCenaAtual();
    void setCenaAtual(unique_ptr<Cena> novaCena);
    void addCenaVisualizada(string nomeArquivo);
    set<string> getCenasVisualizadas(); 
    void salvarJogo(Jogador* personagem, int slot, string pathArquivoAtual);
    string carregarJogo(Personagem& personagem, int slot);

    private:
        unique_ptr<Cena> cenaAtual;        //ponteiro para objeto cena que o jogador está
        Personagem* personagem; //referencia ao objeto personage do jogador - saber estado do jogado ao salvar o jogo 
        set<string> cenasVisualizadas;
        const string CENA_1 = "Arquivo Cena/1.txt";

};