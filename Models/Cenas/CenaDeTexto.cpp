#include <fstream>
#include <sstream>
#include <string>
#include <limits>

#include "CenaDeTexto.h"
#include "../Personagens/Monstro.h"
#include "../Itens/Item.h"
#include "../Itens/ItemComum.h"
#include "../Itens/ItemMagico.h"

CenaDeTexto::CenaDeTexto(string nomeArquivo) : Cena(nomeArquivo) {
    this->setOpcoes(-1);
}

CenaDeTexto::~CenaDeTexto(){}

string CenaDeTexto::exibirCena(Personagem& jogador) {
    int escolha;
    
    cout << "\n" << getTexto() << endl;

    while (true) {

        /*add new item from scene*/
         if (!this->itemGanho.empty()) {
            if (this->itemGanhoCombat) {
                ItemMagico novoItemGanho(itemGanho);
                jogador.addItem(novoItemGanho);
            } else {
                ItemComum novoItemGanho(itemGanho);
                jogador.addItem(novoItemGanho);
            }
            itemGanho = "";
         }

        cout << "\nAbrir Inventario = -1" << endl;
        cout << "\nQual o numero da sua escolha para a proxima cena: ";

        /*handling of player's choice*/
        if (cin >> escolha) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (opcoes.find(escolha) == opcoes.end()) {
                cout << "\n[OPCAO INVALIDA] O numero digitado (" << escolha << ") nao corresponde a uma escolha valida nesta cena. Tente novamente." << endl;
                continue;
            }
            break;    
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[ENTRADA INVALIDA] - Por favor digite um numero valido." << endl;
            continue;
        }

    }
    cout << "\n-------------" << endl;

    if (escolha == -1) {
        return "Inventario";
    }
    
    handlingCenasEspeciais(static_cast<Jogador&>(jogador), escolha);

    string proximaCenaFilename = to_string(escolha) + ".txt";
    return proximaCenaFilename;
}

void CenaDeTexto::setOpcoes(int opcao) {
    opcoes[opcao] = true;
}

void CenaDeTexto::setItemNecessario(std::string item) {
    this->itemNecessario = item;
}

void CenaDeTexto::setItemGanho(string& linha) {
    size_t start_pos = linha.find("P:") + 2; 
    size_t end_name = linha.find(';', start_pos); 

    string nome_bruto = linha.substr(start_pos, end_name - start_pos);
    size_t trim_start = nome_bruto.find_first_not_of(" \t");
    
    if (trim_start != string::npos) {
        this->itemGanho = nome_bruto.substr(trim_start); 
    } else {
        this->itemGanho = "";
    }

    string resto_da_linha = linha.substr(start_pos);

    stringstream ss(resto_da_linha);
    string campo;

    getline(ss, campo, ';'); 
    getline(ss, campo, ';'); 
    getline(ss, campo, ';'); 
    
    this->itemGanhoCombat = (campo == "1");
}

void CenaDeTexto::setItemNecessarioDaCena(string& linha) {
    stringstream ssItem(linha);
    
    string tag;
    ssItem >> tag;
    
    getline(ssItem, this->itemNecessario, ';');

    size_t start = this->itemNecessario.find_first_not_of(" \t");
    
    if (start != string::npos) {
        this->itemNecessario = this->itemNecessario.substr(start);
    } else {
        this->itemNecessario = "";
    }
}

string CenaDeTexto::getProximaCena(int escolha) {
    stringstream ss;

    auto it = this->opcoes.find(escolha);
    if (it != this->opcoes.end()) {
        ss << escolha;
        return ss.str() + ".txt";
    }
    
    return "";
}

void CenaDeTexto::processarOpcoes(string& linha) {
    stringstream ssOpcao(linha);

    string tagDestino;
    ssOpcao >> tagDestino;

    string descricaoLixo;
    getline(ssOpcao, descricaoLixo);

    string destinosString = tagDestino;
    if (destinosString.length() > 1 && destinosString[0] == '#') {
        destinosString = destinosString.substr(1);
    }

    if (!destinosString.empty() && destinosString.string::back() == ':') {
        destinosString.pop_back();
    }

    stringstream ssDestinos(destinosString);
    string idString;

    while (getline(ssDestinos, idString, '/')) {
        try {
            int id = stoi(idString);
            this->setOpcoes(id);
        } catch (...) {
            //no-op
        }
    }
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
        if (linha.find('#') != string::npos || linha.find("I:") != string::npos || linha.find("P:") != string::npos) {
            encontrouOpcoesOuItens = true;
            break;
        }
    }

    if (encontrouOpcoesOuItens) {
        do {
            if (linha.find_first_not_of(" \t\n\r") == string::npos) {
                continue;
            }

            if (linha.find("P:") != string::npos) {
                setItemGanho(linha);
                continue;
            }

            if (linha.find("I:") != string::npos) {
                setItemNecessarioDaCena(linha);
                continue;
            }

            if (linha.find('#') != string::npos) {
                processarOpcoes(linha);
            }

        } while (getline(arquivo, linha));
    }

    arquivo.close();
}

void CenaDeTexto::handlingCenasEspeciais(Jogador& jogador, int& escolha) {

    if (this->getNomeArquivo() == CENA_1 && escolha == 2) {
        if(jogador.getHabilidade() < 8 || !jogador.possuiItem("Accio")) {
            cout << "\nVoce nao possui o habilidade ou magia necessaria. Voce sera redirecionado para a cena 3." << endl;
            escolha = 3;
            return;
        }
    } else if (this->getNomeArquivo() == CENA_2 && escolha == 7) {
        if (jogador.testaSorte()) {
            cout << "Teste de sorte bem sucedido! Voce avanca para a cena 7." << endl;
        } else {
            cout << "Teste de sorte falhou! Voce avanca para a cena 8." << endl;
            escolha = 8;
        }
        return;

    } else if (this->getNomeArquivo() == CENA_4 && escolha == 2) {
        if(jogador.getHabilidade() < 7 || !jogador.possuiItem("Accio")) {
            cout << "\nVoce nao possui o habilidade ou magia necessaria. Voce sera redirecionado para a cena 11." << endl;
            escolha = 11;
            return;
        }
    } else if (this->getNomeArquivo() == CENA_6 && escolha == 12) {
        if(jogador.getHabilidade() < 8 || !jogador.possuiItem("Feitico Bombarda")) {
            cout << "\nVoce nao possui o habilidade ou magia necessaria. Vamos testar sua sorte. Voce sera redirecionado para a cena 13" << endl;
            escolha = 13;
            return;
        }
    }
    return;
}