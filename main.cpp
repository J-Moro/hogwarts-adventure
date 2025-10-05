#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdlib>
#include <ctime>

#include "GerenciadorDeCenas.h"
#include "Models/Cenas/CenaDeCombate.h"
#include "Models/Personagens/Monstro.h"
#include "Models/Personagens/personagens.h"
#include "Models/Personagens/Jogador.h"
#include "Models/Cenas/CenaDeTexto.h"
#include "Models/Itens/Item.h"
#include "Models/Cenas/Cena.h"

using namespace std;

int main() {
    
    srand(time(NULL));

    // 1. Configuração do Jogador
    Jogador jogador;
    jogador.setNome("Harry Potter");
    jogador.setEnergia(20);
    jogador.setHabilidade(10);
    jogador.setProvisoes(3);
    jogador.setSorte(10);
    jogador.setTesouro(10);

    // 2. Criação da Cena de Combate e Carregamento de Dados (Simulando o Gerenciador)

    // O Gerenciador detecta que o arquivo "15.txt" (Aranha Gigante) é de Combate:
    string nomeArquivoTeste = "Arquivos Cena/8.txt"; 

    // Instancia a Cena
    // O seu construtor de CenaDeCombate aceita apenas o nome do arquivo.
    CenaDeCombate cenaBatalha(nomeArquivoTeste);

    // A função de carregamento é chamada diretamente na instância, como faria o Gerenciador:
    // (Atenção: É vital que o método carregaCena funcione corretamente lendo o arquivo!)
    cenaBatalha.carregaCena(nomeArquivoTeste);

    // O monstro está agora instanciado DENTRO do objeto cenaBatalha.

    cout << "--- TESTE ISOLADO DE COMBATE INICIADO ---" << endl;

    // 3. Inicia o Combate através do método exibirCena
    // Seu exibirCena() chama iniciaCombate() internamente.
    cenaBatalha.exibirCena(jogador);

    // 4. Verifica o resultado final do teste
    cout << "\n--- FIM DO TESTE ---" << endl;

    // Precisamos de um ponteiro temporário para acessar o Monstro para a checagem
    Monstro* monstroFinal = cenaBatalha.getMonstro();

    cout << "Energia Final do Jogador: " << jogador.getEnergia() << endl;
    cout << "Energia Final do Monstro (" << monstroFinal->getNome() << "): " << monstroFinal->getEnergia() << endl;

    if (jogador.getEnergia() > 0 && monstroFinal->getEnergia() <= 0) {
        cout << "RESULTADO: VITORIA DO JOGADOR!" << endl;
        // O transferirItens() já deve ter sido chamado dentro do iniciaCombate().
    }
    else if (jogador.getEnergia() <= 0) {
        cout << "RESULTADO: DERROTA DO JOGADOR!" << endl;
    }
    else {
        cout << "RESULTADO: COMBATE INTERROMPIDO (Fuga/Bug)." << endl;
    }

    return 0;
}