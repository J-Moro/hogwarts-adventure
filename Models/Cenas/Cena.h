#pragma once
#include <string>
#include <iostream>

using namespace std;

class Cena {
    public:
        Cena(string nomeArquivo);
        ~Cena();

        string getNomeArquivo();
        string getTexto();
        virtual void exibirCena() = 0;
    
    private:
        string nomeArquivo;
        string texto; 

};