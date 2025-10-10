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

        string getProximaCena(int escolha);

        void setOpcoes(int opcao);
        void setItemNecessario(string item);

        string exibirCena(Personagem& jogador) override;
        void carregaCena(string nomeArquivo) override;
        bool temItemNecessario() { return !itemNecessario.empty(); }
        void handlingCenasEspeciais(Jogador& jogador, int &escolha);

    private:
        void setItemGanho(string& linha);
        void setItemNecessarioDaCena(string& linha);
        void processarOpcoes(string& linha);

        map<int, bool> opcoes;        
        string itemNecessario;
        string itemGanho;
        bool itemGanhoCombat;

        const string CENA_1 = "Arquivos Cena/1.txt";
        const string CENA_2 = "Arquivos Cena/2.txt";
        const string CENA_4 = "Arquivos Cena/4.txt";
        const string CENA_6 = "Arquivos Cena/6.txt";

};