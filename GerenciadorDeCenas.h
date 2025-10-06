#pragma once
#include <string>
#include <iostream>
#include "models/Personagens/personagens.h"
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
    void salvarJogo(Cena* cenaAtual, Personagem* personagem);
    void carregaJogo(string arquivoDeSalvamento);

    private:
        Cena* cenaAtual;        //ponteiro para objeto cena que o jogador está
        Personagem* personagem; //referencia ao objeto personage do jogador - saber estado do jogado ao salvar o jogo 
        const string CENA_1 = "Arquivo Cena/1.txt";

};