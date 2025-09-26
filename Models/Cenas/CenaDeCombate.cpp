#include "CenaDeCombate.h"
#include "../Personagens/Monstro.h"
#include "../Itens/Item.h"
#include "../Itens/ItemComum.h"
#include <fstream>
#include <sstream>
#include <string>

CenaDeCombate::CenaDeCombate(string nomeArquivo) : Cena(nomeArquivo) {}
CenaDeCombate::~CenaDeCombate(){}

void CenaDeCombate::exibirCena() {
    cout << getTexto() << endl;
    //implementar texto avisando que um monstro chegou
    //chamar a lógica que inicia o combate - iniciaCombate()
}

void CenaDeCombate::setMonstro(Monstro* monstro) {
    this->monstro = monstro;
}

Monstro* CenaDeCombate::getMonstro() {
    return this->monstro;
}

//cena que o jogador vai depois do combate
void CenaDeCombate::setCenasPosCombate(string sucesso, string derrota) {
    this->proximaCenaSucesso = sucesso;
    this->proximaCenaDerrota = derrota;
}

//nome da proxima cena apos resultado
string CenaDeCombate::getProximaCena(bool vitoria) {
    if (vitoria) {
        return proximaCenaSucesso;
    } else {
        return proximaCenaDerrota;
    }
}

void CenaDeCombate::carregaCena(string nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir arquivo de cena de combate: " << nomeArquivo << endl;
        return;
    }

    string linha;
    string primeiraPalavra;
    arquivo >> primeiraPalavra;

    while (getline(arquivo, linha) && linha.find("N:") == string::npos) {
        // Ignora o texto de descrição da cena
    }
    
    // Processamento dos atributos do monstro
    string linhaAux;
    int habilidade, sorte, energia, tesouro, provisao;
    string itemNome;
    
    // Extrai o nome do arquivo, removendo a extensão ".txt"
    size_t pos = nomeArquivo.find('.');
    string nomeMonstro = "Monstro" + nomeArquivo.substr(0, pos);
    
    // Lê os atributos do monstro
    stringstream ss(linha);
    ss >> linhaAux; // Descarta a palavra "N:"
    
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux; // M:
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux >> habilidade; // H:
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux >> sorte; // S:
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux >> energia; // E:
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux >> tesouro; // T:
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux >> provisao; // P:
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux >> itemNome; // I:
    
    // Cria o objeto ItemComum
    Item* itemDoMonstro = new ItemComum(itemNome);

    // Instancia o monstro e adiciona os valores diretamente
    this->monstro = new Monstro(nomeMonstro, habilidade, sorte, energia, tesouro, provisao, itemDoMonstro);

    // Leitura das cenas de destino (sucesso e falha)
    getline(arquivo, linha); //descarta linha em branco
    getline(arquivo, linha); //linha com destinos
    stringstream ssDestino(linha);
    char delimiter;
    ssDestino >> this->proximaCenaSucesso >> delimiter >> this->proximaCenaDerrota;
}