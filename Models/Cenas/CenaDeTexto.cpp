#include "CenaDeTexto.h"
#include "../Personagens/Monstro.h"
#include "../Itens/Item.h"
#include "../Itens/ItemComum.h"
#include <fstream>
#include <sstream>
#include <string>

CenaDeTexto::CenaDeTexto(string nomeArquivo) : Cena(nomeArquivo) {
}

CenaDeTexto::~CenaDeTexto(){}

void CenaDeTexto::exibirCena(Personagem& jogador) {
    cout << getTexto() << endl;
    if (!opcoes.empty()) {
        cout << "\nOpcoes:" << endl;
        for (const auto& par : opcoes) {
            cout << par.first << endl;
        }
    }
}

void CenaDeTexto::setOpcoes(int opcao) {
    opcoes[opcao] = true;
}

void CenaDeTexto::setItemNecessario(std::string item) {
    this->itemNecessario = item;
}

string CenaDeTexto::getProximaCena(int escolha) {
    stringstream ss;
    auto it = this->opcoes.find(escolha);
    if (it != this->opcoes.end()) {
        ss << escolha;
        return ss.str() + ".txt";
    }
    
    return "";  //caso o valor nao seja encontrado
}

void CenaDeTexto::carregaCena(string nomeArquivo) {
    string linha;
    bool encontrouOpcoesOuItens;
    bool fimDoJogo;
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir arquivo de cena: " << nomeArquivo << endl;
        return;
    }

    while (getline(arquivo, linha)) {
        if (linha.find('#') != string::npos || linha.find("I:") != string::npos) {
            encontrouOpcoesOuItens = true;
            break;
        }
    }

    if (encontrouOpcoesOuItens) {
        do {
            if (linha.find_first_not_of(" \t\n\r") == string::npos) {
                continue;
            }

            if (linha.find("I:") != string::npos) {
                stringstream ssItem(linha);
                string tag;

                ssItem >> tag;
                getline(ssItem, this->itemNecessario, ';');

                size_t start = this->itemNecessario.find_first_not_of(" \t");
                if (start != string::npos) {
                    this->itemNecessario = this->itemNecessario.substr(start);
                }
                else {
                    this->itemNecessario = "";
                }

                continue; // item foi processaodo - proximo item
            }

            // b) TENTA LER UMA OPÇÃO (#)
            if (linha.find('#') != string::npos) {

                stringstream ssOpcao(linha);
                string tagDestino;

                ssOpcao >> tagDestino; // le a tag

                string descricaoLixo;
                getline(ssOpcao, descricaoLixo);


                //isolamento dos destinos

                string destinosString = tagDestino;

                if (destinosString.length() > 1 && destinosString[0] == '#') {          //remove o #
                    destinosString = destinosString.substr(1);
                }

                //remove o :
                if (!destinosString.empty() && destinosString.string::back() == ':') {
                    destinosString.pop_back();
                }

                stringstream ssDestinos(destinosString);
                string idString;

                //extrai cada destino separado por / 
                while (getline(ssDestinos, idString, '/')) {
                    try {
                        int id = stoi(idString);
                        this->setOpcoes(id);
                    }
                    catch (...) {
                        //no-op
                    }
                }
            }

        } while (getline(arquivo, linha));
    }

    arquivo.close();
}