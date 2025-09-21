#include "CenaDeTexto.h"

CenaDeTexto::CenaDeTexto(string nomeArquivo) : Cena(nomeArquivo) {
}

CenaDeTexto::~CenaDeTexto(){}

void CenaDeTexto::exibirCena() {
    cout << getTexto() << endl;
    if (!opcoes.empty()) {
        cout << "\nOpções:" << endl;
        for (const auto& par : opcoes) {
            cout << par.first << ": " << par.second << endl;
        }
    }
}

void CenaDeTexto::setOpcoes(map<int, std::string> opcoes) {
    this->opcoes = opcoes;
}

void CenaDeTexto::setItemNecessario(std::string item) {
    this->itemNecessario = item;
}

string CenaDeTexto::getProximaCena(int escolha) {
    auto it = opcoes.find(escolha);
    if (it != opcoes.end()) {
        return it->second;
    }
    
    return "";  //caso o valor nao seja encontrado
}