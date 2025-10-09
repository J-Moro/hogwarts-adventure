#pragma once
#include <map>
#include "Cena.h"
#include "../Personagens/Jogador.h"
#include "../../GerenciadorDeCenas.h"

using namespace std;

class CenaDeTexto : public Cena {
    public:
        CenaDeTexto(string nomeArquivo);
        ~CenaDeTexto();

        string exibirCena(Personagem& jogador) override;

        void setOpcoes(int opcao);
        void setItemNecessario(string item);
        void carregaCena(string nomeArquivo) override;
        string getProximaCena(int escolha);
        bool temItemNecessario() { return !itemNecessario.empty(); }
        bool handlingCenasEspeciais(Jogador& jogador, int &escolha);

    private:
        map<int, bool> opcoes;
        string itemNecessario;
};