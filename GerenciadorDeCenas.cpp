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

void GerenciadorDeCena::carregaCena(string nomeArquivo)
{
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro ao abrir arquivo: " + nomeArquivo);
    }

    std::string primeiraPalavra;
    arquivo >> primeiraPalavra;
    arquivo.close();

    // Instancia a cena correta usando unique_ptr
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
    cenaAtual = move(novaCena); // transfere propriedade
}


void GerenciadorDeCena::addCenaVisualizada(string nomeArquivo) {

}

set<string> GerenciadorDeCena::getCenasVisualizadas() {

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
    // A leitura falhou antes de todos os 7 stats serem lidos!
    cerr << "Erro: Arquivo de salvamento incompleto ou corrompido: " << nomeArquivo << endl;
    arquivo.close();
    return ""; // Retorna string vazia para sinalizar falha
}
    arquivo.ignore(); // Ignora o '\n' após o último inteiro

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

void GerenciadorDeCena::salvarJogo(Jogador* personagem, int slot, string pathArquivoAtual) {
    // Monta o nome do arquivo, ex: "savegame_1.sav"
    string nomeArquivo = "savegame_" + to_string(slot) + ".sav";
    
    if(filesystem::exists(nomeArquivo)) {
        cout << "\nAviso: O arquivo de salvamento ja existe e sera sobrescrito." << endl;
        cout << "Deseja continuar? (S/N): ";
        char resposta;
        cin >> resposta;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer do cin
        if (resposta != 'N' && resposta != 'n') {
            cout << "Salvamento cancelado." << endl;
            return; // Sai da função sem salvar
        }
    }

    ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        // Lançar um erro se não conseguir criar o arquivo (o main.cpp deve capturar)
        throw runtime_error("Erro: Nao foi possivel criar o arquivo de salvamento: " + nomeArquivo);
    }

    // =======================================================
    // 1. DADOS DE POSIÇÃO (Cena Atual)
    // =======================================================
    arquivo << pathArquivoAtual << "\n"; 
    
    // =======================================================
    // 2. DADOS DO PERSONAGEM/JOGADOR
    // =======================================================
    arquivo << personagem->getNome() << "\n";
    arquivo << personagem->getHabilidade() << "\n";
    arquivo << personagem->getEnergia() << "\n";
    arquivo << personagem->getSorte() << "\n";

    // Outros atributos do Personagem
    arquivo << personagem->getTesouro() << "\n";
    arquivo << personagem->getProvisoes() << "\n";
    arquivo << personagem->getBonusSorte() << "\n"; // Salvo como 0 ou 1
    arquivo << personagem->getQuantidadeItens() << "\n"; // Quantidade para o carregamento
    
    // =======================================================
    // 3. INVENTÁRIO (Item: nome;tipo;combate;FA;dano)
    // =======================================================
    int totalItens = personagem->getQuantidadeItens();
    Item* inventario = personagem->getInventario();

    for (int i = 0; i < totalItens; ++i) {
        // Item: nome;tipo;combate;FA;dano
        arquivo << inventario[i].getName() << ";";
        
        // Converte o enum type (c, r, w -> 0, 1, 2) para um inteiro
        arquivo << (int)inventario[i].getType() << ";"; 
        
        // Converte o bool combat (true/false) para 1 ou 0
        arquivo << inventario[i].getCombat() << ";"; 
        
        arquivo << inventario[i].getFaBonus() << ";";
        arquivo << inventario[i].getDamageBonus() << "\n"; // Último campo seguido por nova linha
    }

    // =======================================================
    // 4. CENAS VISUALIZADAS
    // =======================================================
    // Salva o número total de cenas para saber quantos itens ler
    //arquivo << cenasVisualizadas.size() << "\n"; 
    //for (const auto& nome : cenasVisualizadas) {
      //  arquivo << nome << "\n";
    //}

    arquivo.close();
    // Nota: A linha cin.ignore() é desnecessária aqui, pois estamos escrevendo.
    // Ela só é necessária após a leitura (cin >>).
}