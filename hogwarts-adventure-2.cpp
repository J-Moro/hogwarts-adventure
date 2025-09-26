#include <iostream>
#include <string>
#include <typeinfo>

#include "GerenciadorDeCenas.h"
#include "Models/Cenas/CenaDeCombate.h"
#include "Models/Personagens/Monstro.h"
#include "Models/Itens/Item.h"

using namespace std;

void exibirDadosDaCenaDeCombate(CenaDeCombate* cena) {
    if (cena == nullptr) {
        cout << "Erro: A cena não é uma CenaDeCombate." << endl;
        return;
    }

    Monstro* monstro = cena->getMonstro();

    if (monstro != nullptr) {
        cout << "--- Dados do Monstro ---" << endl;
        cout << "Nome: " << monstro->getNome() << endl;
        cout << "Habilidade: " << monstro->getHabilidade() << endl;
        cout << "Sorte: " << monstro->getSorte() << endl;
        cout << "Energia: " << monstro->getEnergia() << endl;
        cout << "Tesouro: " << monstro->getTesouro() << endl;
        cout << "Provisao: " << monstro->getProvisoes() << endl;
        monstro->mostrarInventario();
        cout << "------------------------" << endl;
    }

    cout << "--- Dados da Cena ---" << endl;
    cout << "Cena de sucesso: " << cena->getProximaCena(true) << endl;
    cout << "Cena de derrota: " << cena->getProximaCena(false) << endl;
    cout << "---------------------" << endl;
}

int main() {
    GerenciadorDeCena* gerenciador = new GerenciadorDeCena();

    cout << "Carregando a cena de combate 15.txt..." << endl;
    gerenciador->carregaCena("Arquivos Cena/15.txt");

    Cena* cenaAtual = gerenciador->getCenaAtual();
    CenaDeCombate* cenaDeCombate = dynamic_cast<CenaDeCombate*>(cenaAtual);
    
    exibirDadosDaCenaDeCombate(cenaDeCombate);

    delete gerenciador;
    return 0;
}