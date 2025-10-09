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

void TelaInventario(Jogador& jogador) {
    cout << "\n===============================" << endl;
    cout << " | INVENTARIO DE " << jogador.getNome() << " |" << endl;
    cout << "===============================" << endl;
    jogador.mostrarInventario();
    cout << "\n 1. Voltar ao jogo" << endl;
    cout << "\n 2. Usar provisao" << endl;
    cout << "\n 3. Equipar arma" << endl;
    cout << "\n 4. Deletar item" << endl;
    cout << "\n 5. Salvar e sair do jogo" << endl;
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

    jogador.setProvisoes(4); //inicia com 4 provisoes
    jogador.setTesouro(10); //inicia com 10 de tesouro

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

int jogo(GerenciadorDeCena& gerenciador, Jogador& jogador) {
    
    //LOOP DO JOGO
    while (jogador.getEnergia() > 0) {
        Cena* cenaAtual = gerenciador.getCenaAtual();

        if (!cenaAtual) {
            cout << "[ERRO] - nao conseguiu abrir a cena atual" << endl;
            break;
        }

        string proximaCenaFileName = cenaAtual->exibirCena(jogador);

        // Handle cena 0 (morte) explicitamente
        if (proximaCenaFileName == "0" || proximaCenaFileName == "0.txt") {
            jogador.setEnergia(0); // Força o fim do jogo
            break;
        }

        if (proximaCenaFileName == "Inventario") {
            TelaInventario(jogador);
            int escolhaInventario;
            while (true) {
                cin >> escolhaInventario;
                if (escolhaInventario == 1) {
                    break; // Volta ao jogo
                } else if (escolhaInventario == 2) {
                    if (jogador.getProvisoes() > 0 && jogador.getEnergia() < 24) {
                        jogador.setProvisoes(jogador.getProvisoes() - 1);
                        jogador.setEnergia(jogador.getEnergia() + 4);
                        if (jogador.getEnergia() > 24) {
                            jogador.setEnergia(24); // Limita a energia máxima a 24
                        }
                        cout << "\nVoce usou uma provisao. Energia atual: " << jogador.getEnergia() << ", Provisoes restantes: " << jogador.getProvisoes() << endl;
                    } else {
                        cout << "\nVoce nao tem mais provisoes!" << endl;
                    }
                    TelaInventario(jogador); // Reexibe o menu do inventario
                } else if (escolhaInventario == 3) {
                    if (jogador.getQuantidadeItens() == 0) {
                        cout << "\nSeu inventario esta vazio! Nao ha armas para equipar." << endl;
                        TelaInventario(jogador); // Reexibe o menu do inventario
                        continue;
                    }

                    cout << "\nDigite o nome da arma que deseja equipar (ou '0' para cancelar): ";
                    string itemName;
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    getline(cin, itemName);

                    if (itemName == "0") {
                        TelaInventario(jogador); // Reexibe o menu do inventario
                        continue; // Cancela a operacao e volta ao menu do inventario
                    }

                    if (jogador.equiparArma(itemName)) {
                        cout << "\nArma '" << itemName << "' equipada com sucesso." << endl;
                    } else {
                        cout << "\nFalha ao equipar a arma. Verifique se o nome esta correto e tente novamente." << endl;
                    }
                    TelaInventario(jogador); // Reexibe o menu do inventario
                }
                
                else if (escolhaInventario == 4) {
                    if (jogador.getQuantidadeItens() == 0) {
                        cout << "\nSeu inventario esta vazio! Nao ha itens para deletar." << endl;
                        TelaInventario(jogador); // Reexibe o menu do inventario
                        continue;
                    }

                    jogador.mostrarInventario();
                    cout << "\nDigite o numero do item que deseja deletar (0 para cancelar): ";
                    int itemIndex;
                    cin >> itemIndex;

                    if (itemIndex == 0) {
                        TelaInventario(jogador); // Reexibe o menu do inventario
                        continue; // Cancela a delecao e volta ao menu do inventario
                    }

                    if (itemIndex < 1 || itemIndex > jogador.getQuantidadeItens()) {
                        cout << "\nIndice invalido! Tente novamente." << endl;
                        TelaInventario(jogador); // Reexibe o menu do inventario
                        continue;
                    }

                    string itemName = jogador.getInventario()[itemIndex - 1].getName();
                    if (jogador.removeItem(itemName)) {
                        cout << "\nItem '" << itemName << "' removido do inventario." << endl;
                    } else {
                        cout << "\nFalha ao remover o item. Tente novamente." << endl;
                    }
                    TelaInventario(jogador); // Reexibe o menu do inventario
                }
                
                else if (escolhaInventario == 5) {
                    
                    cout << "\nEm qual slot deseja salvar? (0, 1 ou 2): ";
                    int slot;
                    cin >> slot;

                    while (slot < 0 || slot > 2) {
                        
                        cout << "\nSlot invalido! Escolha 0, 1 ou 2." << endl;
                        cin >> slot;
                    }

                    if(gerenciador.salvarJogo(&jogador, slot, cenaAtual->getNomeArquivo())){
                        cout << "\nJogo salvo com sucesso no slot " << slot << "!" << endl;
                        return 0; // Sai do jogo apos salvar
                    } else {
                        cout << "\nFalha ao salvar o jogo." << endl;
                        TelaInventario(jogador);
                    }
                    

                } else {
                    cout << "\nOpcao invalida! Tente novamente." << endl;
                    TelaInventario(jogador); // Reexibe o menu do inventario
                }
            }
        }
        else {
            string caminhoCompleto = "Arquivos Cena/" + proximaCenaFileName;

            if(proximaCenaFileName.empty()){
                continue;
            }

            gerenciador.carregaCena(caminhoCompleto);
        }
    }

    // FIM DE JOGO (Tela 4)
    cout << "\n=======================================" << endl;
    if (jogador.getEnergia() <= 0) {
        cout << " | GAME OVER: VOCE FOI DERROTADO(A)! |" << endl;
    } else {
        cout << " | FIM DA AVENTURA: VOCE VENCEU! |" << endl;
    }
    cout << "=======================================" << endl;
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
            TelaInventario(jogador);
            cout << "\n\n\n --- INICIO DE JOGO ---" << endl;

            try
            {
                gerenciador.carregaCena("Arquivos Cena/1.txt");

                jogo(gerenciador, jogador);
                
                // Volta para o Menu Inicial
                continue;
                
            }
            catch(const std::exception& e)
            {
                cout << "\n[ERRO] - " << e.what() << endl;
                //break; // Sai do loop principal
            }


        } else if (escolha == 2) {
            //chamar funcao que carrega o jogo salvo
            cout << "\nQual slot deseja carregar? (0, 1 ou 2): ";
            int slot;
            cin >> slot;
            while (slot < 0 || slot > 2) {
                
                cout << "\nSlot invalido! Escolha 0, 1 ou 2." << endl;
                cin >> slot;
            }

            string nomeArquivoCena = gerenciador.carregarJogo(jogador, slot);
            if (nomeArquivoCena.empty()) { 
                cout << "\nFalha ao carregar o jogo. O slot pode estar vazio ou corrompido." << endl;
                continue; // Volta ao menu inicial
            }


            gerenciador.carregaCena(nomeArquivoCena);

            if (gerenciador.getCenaAtual() == nullptr) {
                cout << "\nFalha ao carregar o arquivo da cena. Voltando ao menu inicial." << endl;
                continue; 
            }
            
            cout << "\nJogo carregado com sucesso! Bem-vindo de volta, " << jogador.getNome() << "!" << endl;
            jogo(gerenciador, jogador);

        } else if (escolha == 3) {
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