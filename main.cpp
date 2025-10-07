#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "GerenciadorDeCenas.h"
#include "Models/Cenas/CenaDeCombate.h"
#include "Models/Personagens/Monstro.h"
#include "Models/Personagens/personagens.h"
#include "Models/Personagens/Jogador.h"
#include "Models/Cenas/CenaDeTexto.h"
#include "Models/Itens/Item.h"
#include "Models/Cenas/Cena.h"

using namespace std;

void MenuInicial() {
    cout << "\n===============================" << endl;
    cout << " | HOGWARTS ADVENTURE |" << endl;
    cout << "===============================" << endl;
    cout << " 1. Novo Jogo" << endl;
    cout << " 2. Carregar Jogo Salvo" << endl;
    cout << " 3. Exibir Creditos" << endl;
    cout << " 4. Sair" << endl;
    cout << " Sua escolha: ";
}

void MenuCreditos() {
     cout << "\n===============================" << endl;
    cout << " | HOGWARTS ADVENTURE |" << endl;
    cout << "===============================" << endl;
    cout << "\n\n Desenvolvedoras: Grasieli Wiedthauger e Julia Moro\n\n" << endl;
    cout << " 1. Voltar ao menu anterior" << endl;
    cout << " 2. Sair" << endl;
    cout << " Sua escolha: ";
}

bool exibirMenuCreditos() {
    int escolha;

    while (true) {
        MenuCreditos();
        cin >> escolha;

        if (escolha == 1) {
            return true;
        } else if (escolha == 2) {
            return false;
        } else {
            cout << "\n Opcao Invalida" << endl;
        }
    }
}

void criacaoPersonagem(Jogador& jogador) {
    string nome;
    int pontosRestantes = 12, pontosHabilidade = 0, pontosEnergia = 0;

    cout << "\n--- CRIACAO DO PERSONAGEM ---" << std::endl;
    cout << "Digite o nome do seu mago para iniciar essa aventura em Hogwarts: ";

    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, nome);
    jogador.setNome(nome);

    
    cout << "Voce tem " << pontosRestantes << " pontos de habilidades para distribuir entre Habilidade, Energia e Sorte." << endl;
    while (true) {
        cout << "Atributos iniciais" << endl;
        cout << "Habilidade: " << jogador.getHabilidade() << " | Energia: " << jogador.getEnergia() << " | Sorte: " << jogador.getSorte() << endl;
        std::cout << "\nPontos restantes: " << pontosRestantes << endl;
        std::cout << "Voce ja tem "<< jogador.getHabilidade() << " pontos em HABILIDADE. Selecione quantos pontos para adicionar: (Minimo: 0 - Maximo: 6): ";
        
        if (!(cin >> pontosHabilidade) || pontosHabilidade < 0 || pontosHabilidade > 6) {
            cout << "Valor invalido! Habilidade total deve ser um numero entre 6 e 12." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (pontosHabilidade > pontosRestantes) {
            cout << "Pontos insuficientes! Voce tem apenas " << pontosRestantes << " pontos restantes." << endl;
        } else {
            // Se a entrada for válida, defina e saia do loop
            jogador.setHabilidade(pontosHabilidade + jogador.getHabilidade());
            pontosRestantes -= pontosHabilidade;
            break; 
        }
    }

    while (true) {
        cout << "\nPontos restantes: " << pontosRestantes << endl;
        std::cout << "Voce ja tem "<< jogador.getEnergia() << " pontos em ENERGIA. Selecione quantos pontos para adicionar: (Minimo: 0 - Maximo: 12): ";

        
        if (!(cin >> pontosEnergia) || pontosEnergia < 0 || pontosEnergia > 12) {
             cout << "Valor invalido! Energia total deve ser um numero entre 12 e 24." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (pontosEnergia > pontosRestantes) {
             cout << "Pontos insuficientes! Voce tem apenas " << pontosRestantes << " pontos restantes." << endl;
        } else {
            jogador.setEnergia(pontosEnergia + jogador.getEnergia());
            pontosRestantes -= pontosEnergia;
            break;
        }
    }

    if (pontosRestantes >= 0) { 
        
        if (pontosRestantes + jogador.getSorte()> 12) {
            jogador.setSorte(12);
        } else {
            jogador.setSorte(pontosRestantes + jogador.getSorte());
        }
        

        cout << "\nOs pontos restantes foram atribuidos a SORTE." << endl;
        cout << "\nSorte final: " << jogador.getSorte() << endl;
        pontosRestantes = 0;
    } 
    
    cout << "\n--- PERSONAGEM CRIADO ---" << endl;
    cout << "\nAtributos finais:";
    cout << "\nHabilidade: " << jogador.getHabilidade() << " | Energia: " << jogador.getEnergia() << " | Sorte: " << jogador.getSorte() << endl;
}

int main() {
    
    srand(time(NULL));

    Jogador jogador;
    GerenciadorDeCena gerenciador;
    int escolha;

    while (true) {
        MenuInicial();
        cin >> escolha;

        if (escolha == 1) {
            //criar personagem e inventario
            criacaoPersonagem(jogador);
            cout << "\n\n\n --- INICIO DE JOGO ---" << endl;

            try
            {
                gerenciador.carregaCena("Arquivos Cena/1.txt");

                //LOOP DO JOGO
                while (jogador.getEnergia() > 0) {
                    //TODO: implementar perda do jogo quando o map de opcoes tiver a opcao 0 (morte)
                    Cena* cenaAtual = gerenciador.getCenaAtual();

                    if (!cenaAtual) {
                        cout << "[ERRO] - nao conseguiu abrir a cena atual" << endl;
                        break;
                    }

                    string proximaCenaFileName = cenaAtual->exibirCena(jogador);
                    string caminhoCompleto = "Arquivos Cena/" + proximaCenaFileName;

                    if(proximaCenaFileName.empty()){
                        continue;
                    }

                    gerenciador.carregaCena(caminhoCompleto);
                }

                // FIM DE JOGO (Tela 4)
                cout << "\n=======================================" << endl;
                if (jogador.getEnergia() <= 0) {
                    cout << " | GAME OVER: VOCE FOI DERROTADO(A)! |" << endl;
                } else {
                    cout << " | FIM DA AVENTURA: VOCE VENCEU! |" << endl;
                }
                cout << "=======================================" << endl;
                
                // Volta para o Menu Inicial
                continue;
                
            }
            catch(const std::exception& e)
            {
                cout << "\n[ERRO] - " << e.what() << endl;
                break; // Sai do loop principal
            }
            



        } else if (escolha == 2) {
            //chamar funcao que carrega o jogo salvo
            cout << "\nFuncionalidade de Carregar Jogo ainda nao implementada." << endl;
        }else if (escolha == 3) {
            bool creditos = exibirMenuCreditos();
            if (creditos == false) {
                return 0;
            } else {
                continue;
            }
        } else if (escolha == 4) {
            return 0;
        } else {
            cout << "\nOpcao invalida!" << endl;
        }
    }

    

    return 0;
}