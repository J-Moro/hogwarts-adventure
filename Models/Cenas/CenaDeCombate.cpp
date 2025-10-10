#include <fstream>
#include <sstream>
#include <string>
#include <limits>

#include "CenaDeCombate.h"
#include "../Personagens/Monstro.h"
#include "../Itens/Item.h"
#include "../Itens/ItemComum.h"

using namespace std;

CenaDeCombate::CenaDeCombate(string nomeArquivo) : Cena(nomeArquivo) {}
CenaDeCombate::~CenaDeCombate(){}

string CenaDeCombate::exibirCena(Personagem& jogador) {
    stringstream ss;
    cout << "\n\n\n" << getTexto() << endl;

    string proximaCena= this->iniciaCombate(jogador);
    
    if(proximaCena == "Inventario") {
        return proximaCena;
    }
    
    proximaCena += ".txt";
    return proximaCena;
}

void CenaDeCombate::setMonstro(Monstro* monstro) {
    this->monstro = monstro;
}

Monstro* CenaDeCombate::getMonstro() {
    return this->monstro;
}

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
        //no-op
    }
    
    string linhaAux;
    int habilidade, sorte, energia, tesouro, provisao;
    string itemNome;
    string nomeMonstro;
    stringstream ss;

    ss.str(linha);
    ss.clear();
    ss >> linhaAux;
    getline(ss, nomeMonstro);
    
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux; // M:
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux >> habilidade; // H:
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux >> sorte; // S:
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux >> energia; // E:
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux >> tesouro; // T:
    getline(arquivo, linha); ss.str(linha); ss.clear(); ss >> linhaAux >> provisao; // P:
   
    //I
    getline(arquivo, linha);
    ss.str(linha);
    ss.clear();
    ss >> linhaAux;
    std::getline(ss, itemNome, ';');
    Item* itemDoMonstro = new ItemComum(itemNome); 

    this->monstro = new Monstro(nomeMonstro, habilidade, sorte, energia, tesouro, provisao, itemDoMonstro);
    
    do {
        if (!getline(arquivo, linha)) {
            break;
        }
    } while (linha.find_first_not_of(" \t\n\r") == string::npos);

    stringstream ssDestino(linha);
    char hashTag;
    ssDestino >> hashTag;

    getline(ssDestino, this->proximaCenaSucesso, ':');

    ssDestino >> this->proximaCenaDerrota;
    ssDestino >> this->proximaCenaDerrota;
}

string CenaDeCombate::iniciaCombate(Personagem& jogador) {
    cout << "----- BATALHA INICIADA -----" << endl;

    while (jogador.getEnergia() > 0 && monstro->getEnergia() > 0) {
    
        exibirStatusCombate(jogador);

        char acao;
        cout << "\nAbrir Inventario = I" << endl;
        cout << "\n" << "O que voce vai fazer? (A)tacar, (M)agia, (T)estar Sorte, (F)ugir: ";
        cin >> acao;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (acao) {
            case 'A':
            case 'a':
                executarAtaque(jogador);
                break;
            case 'T':
            case 't':
            {
                if (jogador.getSorte() <= 0) {
                    cout << "\n" << "Voce nao tem mais sorte para testar!" << endl;
                    continue;
                }

                bool sucesso = jogador.testaSorte();
                if (sucesso) {
                    cout << "\n" << " SUCESSO! A sorte esta do seu lado. Voce conseguiu um bonus de sorte para a proxima rodada." << endl;
                    jogador.setBonusSorte(true);
                } else {
                cout << "\n" << "FALHA! A sorte nao esta do seu lado." << endl;
                }
                break;
            }
            case 'F':
            case 'f':
                if (tentarFuga(jogador)) {
                    return getProximaCena(false);
                }
                break;
            case 'M':
            case 'm':
                if (jogador.possuiItem("Grimorio das Chamas")) {        
                    if (monstro->getNome() == "Aranha Gigante") {
                        monstro->setEnergia(0);
                        cout << "\n" << "Seu feitico de fogo acerta em cheio a " << monstro->getNome() << " queimando-a" << endl;
                        return getProximaCena(true);
                    } else {
                        cout << "\n" << "Voce nao pode usar magia agora!" << endl;
                    }
                }
                break;
            case 'I':
            case 'i':
                return "Inventario";
            default:
                cout << "\n" << "Ação inválida. Digite A, M, T ou F." << endl;
                break;
        }
    }

    if (jogador.getEnergia() > 0) {
        cout << "\n\n--- VITORIA ---" << endl;
        cout << "\n" << "Proxima cena eh " << getProximaCena(true) << endl; 
        cout << "\n-------------\n" << endl;

        monstro->transferirItens(jogador);
        return getProximaCena(true);
    } else {
        cout << "\n\n--- DERROTA ---" << endl;
        cout << "\n" << "Proxima cena eh " << getProximaCena(false) << endl;
        cout << "\n-------------\n" << endl;
    
        return getProximaCena(false);
    }
}

void CenaDeCombate::exibirStatusCombate(Personagem& jogador) {
    cout << "\n--- STATUS DA BATALHA ---" << std::endl;

    cout << jogador.getNome() <<" - ENERGIA: " << jogador.getEnergia()
        << " | SORTE: " << jogador.getSorte() << std::endl;

    cout << monstro->getNome() << " - ENERGIA: " << monstro->getEnergia() << endl;
    cout << "Item do monstro: " << monstro->getInventario()->getName() << endl;

    cout << "-------------------------" << std::endl;
}

void CenaDeCombate::executarAtaque(Personagem& jogador) {
    int faJogador = jogador.calcFA();
    int faMonstro = monstro->calcFA();
    
    if (faJogador > faMonstro) {
        if (jogador.getBonusSorte() == true) {
            monstro->recebeDano();
            monstro->recebeDano();
            
            jogador.setBonusSorte(false);
            
            cout << "\n" << jogador.getNome() << " venceu o turno! O " << monstro->getNome() << " perdeu 4 de energia com seu bonus de sorte ativado" << endl;
        }
        else {
            monstro->recebeDano();
            cout << "\n" << jogador.getNome() << " venceu o turno! O " << monstro->getNome() << " perdeu 2 de energia" << endl;
        }
    }
    else if (faJogador < faMonstro) {
        jogador.recebeDano();
        cout << "\n" << monstro->getNome() << " venceu o turno! O " << jogador.getNome() << " perdeu 2 de energia" << endl;
    }
    else {
        jogador.recebeDano();
        monstro->recebeDano();

        cout << "\n" << "Empate! Ambos perdem 2 de energia!" << endl;
    }
}

bool CenaDeCombate::tentarFuga(Personagem& jogador) {
    cout << "\n" << "Tentando fugir. Testando sorte..." << endl;

    if (jogador.testaSorte()) {
        cout << "\n" << "Voce conseguiu fugir com sucesso!" << endl;
        cout << "\n" << "Proxima cena eh " << getProximaCena(true) << endl; 
        cout << "\n-------------\n" << endl;

        return true;
    }
    else {
        cout << "\n" << "A fuga falhou! Voce perdeu 2 de Energia e o combate continua." << endl;

        jogador.recebeDano();
        return false;
    }
}