#pragma once
#include <map>
#include "Cena.h"

using namespace std;

class CenaDeTexto : public Cena {
    public:
        CenaDeTexto(string nomeArquivo);
        ~CenaDeTexto();

        void exibirCena() override;

        void setOpcoes(map<int, std::string> opcoes);
        void setItemNecessario(string item);
        void carregaCena(string nomeArquivo);
        string getProximaCena(int escolha);

    private:
        map<int, string> opcoes;
        string itemNecessario;
};