#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <filesystem>

#include "GerenciadorDeCenas.h"
#include "Models/Cenas/Cena.h"
#include "Models/Cenas/CenaDeCombate.h"
#include "Models/Cenas/CenaDeTexto.h"
#include "Models/Itens/ItemComum.h"

using namespace std;

GerenciadorDeCena::GerenciadorDeCena() {}
GerenciadorDeCena::~GerenciadorDeCena() {}

void GerenciadorDeCena::carregaCena(string nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro ao abrir arquivo: " + nomeArquivo);
    }

    std::string primeiraPalavra;
    arquivo >> primeiraPalavra;
    arquivo.close();

    
    if (primeiraPalavra == "Uau" || primeiraPalavra == "Poxa") {
        cenaAtual = make_unique<CenaDeCombate>(nomeArquivo);
    } else {
        cenaAtual = make_unique<CenaDeTexto>(nomeArquivo);
    }

    cenaAtual->lerConteudoBruto(nomeArquivo);
    cenaAtual->carregaCena(nomeArquivo);
}


Cena* GerenciadorDeCena::getCenaAtual() {
    return this->cenaAtual.get();
}

void GerenciadorDeCena::setCenaAtual(unique_ptr<Cena> novaCena) {
    cenaAtual = move(novaCena);
}

string GerenciadorDeCena::carregarJogo(Personagem& personagem, int slot) {

    string nomeArquivo = "savegame_" + to_string(slot) + ".sav";
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir arquivo de salvamento: " << nomeArquivo << endl;
        return "";
    }

    string pathArquivoAtual;
    getline(arquivo, pathArquivoAtual);

    string nome;
    getline(arquivo, nome);

    int habilidade, energia, sorte, tesouro, provisoes, bonusSorte, quantidadeItens;
    arquivo >> habilidade;
    arquivo >> energia;
    arquivo >> sorte;
    arquivo >> tesouro;
    arquivo >> provisoes;
    arquivo >> bonusSorte;
    arquivo >> quantidadeItens;
    
    if (arquivo.fail()) {
        cerr << "Erro: Arquivo de salvamento incompleto ou corrompido: " << nomeArquivo << endl;
        arquivo.close();
        return "";
    }
    arquivo.ignore();

    personagem.setNome(nome);
    personagem.setHabilidade(habilidade);
    personagem.setEnergia(energia);
    personagem.setSorte(sorte);
    personagem.setTesouro(tesouro);
    personagem.setProvisoes(provisoes);
    personagem.setBonusSorte(bonusSorte);

    arquivo.close();
    return pathArquivoAtual;
}

int GerenciadorDeCena::salvarJogo(Jogador* personagem, int slot, string pathArquivoAtual) {
    string nomeArquivo = "savegame_" + to_string(slot) + ".sav";
    
    if(filesystem::exists(nomeArquivo)) {
        cout << "\nAviso: O arquivo de salvamento ja existe e sera sobrescrito." << endl;
        cout << "Deseja continuar? (S/N): ";
        
        char resposta;
        cin >> resposta;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        
        if (resposta == 'N' || resposta == 'n') {
            cout << "Salvamento cancelado." << endl;
            return 0; 
        }
    }

    ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        throw runtime_error("Erro: Nao foi possivel criar o arquivo de salvamento: " + nomeArquivo);
    }

    arquivo << pathArquivoAtual << "\n"; 

    arquivo << personagem->getNome() << "\n";
    arquivo << personagem->getHabilidade() << "\n";
    arquivo << personagem->getEnergia() << "\n";
    arquivo << personagem->getSorte() << "\n";

    arquivo << personagem->getTesouro() << "\n";
    arquivo << personagem->getProvisoes() << "\n";
    arquivo << personagem->getBonusSorte() << "\n";
    arquivo << personagem->getQuantidadeItens() << "\n";

    int totalItens = personagem->getQuantidadeItens();
    Item* inventario = personagem->getInventario();

    for (int i = 0; i < totalItens; ++i) {
        arquivo << inventario[i].getName() << ";";
        arquivo << (int)inventario[i].getType() << ";"; 
        arquivo << inventario[i].getCombat() << ";"; 
        arquivo << inventario[i].getFaBonus() << ";";
        arquivo << inventario[i].getDamageBonus() << "\n";
    }

    arquivo.close();
    return 1;
}