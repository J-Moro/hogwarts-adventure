#pragma once
#include <map>
#include "Cena.h"

using namespace std;

class CenaDeTexto : public Cena {
    public:
        CenaDeTexto(string nomeArquivo);
        ~CenaDeTexto();

        void exibirCena(Personagem& jogador) override;

        void setOpcoes(int opcao);
        void setItemNecessario(string item);
        void carregaCena(string nomeArquivo) override;
        string getProximaCena(int escolha);

    private:
        map<int, bool> opcoes;
        string itemNecessario;
};