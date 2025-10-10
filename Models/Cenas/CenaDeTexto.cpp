#include "CenaDeTexto.h"
#include "../Personagens/Monstro.h"
#include "../Itens/Item.h"
#include "../Itens/ItemComum.h"
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

CenaDeTexto::CenaDeTexto(string nomeArquivo) : Cena(nomeArquivo) {
    this->setOpcoes(-1); //mapa de opcoes sempre tem a opcao I (inventario)
}

CenaDeTexto::~CenaDeTexto(){}

string CenaDeTexto::exibirCena(Personagem& jogador) {
    //TODO: implementar testar sorte para algumas cenas
    int escolha;
    
    cout << "\n" << getTexto() << endl;

    while (true) {

         if (!this->itemGanho.empty()) {
            ItemComum novoItemGanho(itemGanho);
            jogador.addItem(novoItemGanho);
            itemGanho = "";
         }

        cout << "\nAbrir Inventario = -1" << endl;
        cout << "\nQual o numero da sua escolha para a proxima cena: ";
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

        return "Inventario"; //sinaliza para o main que deve abrir o inventario
    }
    
    handlingCenasEspeciais(static_cast<Jogador&>(jogador), escolha);

    // 6. Monta e retorna o nome do arquivo (ID.txt)
    string proximaCenaFilename = to_string(escolha) + ".txt";
   

    // 7. Retorna o nome do arquivo para o main loop efetuar a transição
    return proximaCenaFilename;
}

void CenaDeTexto::setOpcoes(int opcao) {
    opcoes[opcao] = true;
}

void CenaDeTexto::setItemNecessario(std::string item) {
    this->itemNecessario = item;
}

void CenaDeTexto::setItemGanho(string item) {
    this->itemGanho = item;
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

            // Se for P: (ITEM GANHO)
            if (linha.find("P:") != string::npos) {
    
                // 1. Encontra o início do nome (logo após "P:"). Assume que "P:" tem 2 chars.
                size_t start_pos = linha.find("P:") + 2; 

                // 2. Encontra o final do nome (o primeiro ';'). Como é garantido, não checamos npos.
                size_t end_pos = linha.find(';', start_pos);

                // 3. Extrai a substring bruta, que pode começar com espaço (Ex: " Feitiço Bombarda").
                string nome_bruto = linha.substr(start_pos, end_pos - start_pos);

                // 4. Remove espaços em branco (trim) do início.
                size_t trim_start = nome_bruto.find_first_not_of(" \t");
    
                if (trim_start != string::npos) {
                    // Armazena APENAS o nome limpo!
                    this->itemGanho = nome_bruto.substr(trim_start); 
                } else {
                    this->itemGanho = "";
                }

                continue; // Processado, vai para a próxima linha
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

                continue; // item foi processado - proximo item
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

bool CenaDeTexto::handlingCenasEspeciais(Jogador& jogador, int& escolha) {
    // Implementar aqui o tratamento de cenas especiais, se necessário
    // Retornar true se a cena especial foi tratada, false caso contrário

    if (this->getNomeArquivo() == "1.txt" && escolha == 2) {
        if(jogador.getHabilidade() < 8) 
        {
            cout << "\nSua habilidade eh insuficiente para essa escolha. Voce sera redirecionado para a cena 3." << endl;
            escolha = 3;
            return true;
        }
    } else if (this->getNomeArquivo() == "2.txt" && escolha == 7) {
        if (jogador.testaSorte()) {
            cout << "Teste de sorte bem sucedido! Voce avanca para a cena 7." << endl;
        } else {
            cout << "Teste de sorte falhou! Voce avanca para a cena 8." << endl;
            escolha = 8;
        }
        return true;

    } else if (this->getNomeArquivo() == "4.txt" && escolha == 2) {
        if(jogador.getHabilidade() < 7) 
        {
            cout << "\nSua habilidade eh insuficiente para essa escolha. Voce sera redirecionado para a cena 11." << endl;
            escolha = 11;
            return true;
        }
    } else if (this->getNomeArquivo() == "6.txt" && escolha == 12) {
        if(jogador.getHabilidade() < 8) 
        {
            cout << "\nSua habilidade eh insuficiente para essa escolha. Vamos testar sua sorte." << endl;
        } else if (jogador.testaSorte()) {
            cout << "Teste de sorte bem sucedido! Voce avanca para a cena 7." << endl;
        } else {
            cout << "Teste de sorte falhou! Voce avanca para a cena 13." << endl;
            escolha = 13;
        }
        return true;
    }

    return false;
}