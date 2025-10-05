#pragma once
#include <string>
#include <iostream>
#include "../Personagens/personagens.h"

using namespace std;

class Cena {
    public:
        Cena(string nomeArquivo);
        ~Cena();

        virtual string exibirCena(Personagem& jogador) = 0;
        string getNomeArquivo();
        string getTexto();
        void setTexto(string t);
        void lerConteudoBruto(string nomeArquivo);
        virtual void carregaCena(string nomeArquivo) = 0;
    
    private:
        string nomeArquivo;
        string texto;
};