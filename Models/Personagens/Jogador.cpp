#include "Jogador.h"

Jogador::Jogador(){
    this->setHabilidade(6);
    this->setEnergia(12);
    this->setSorte(6);
}

Jogador::~Jogador(){}

bool Jogador::equiparArma(string itemName) {
    Item* inventario = this->getInventario();
    for (int i = 0; i < this->getQuantidadeItens(); i++) {
        if (inventario[i].getName() == itemName) {
            Arma* arma = dynamic_cast<Arma*>(&inventario[i]);
            if (arma) {
                if (armaEquipada) {
                    cout << "Voce ja tem uma arma equipada: " << armaEquipada->getName() << ". Deseja desequipa-la? (S/N)" << endl;
                    char resposta;
                    cin >> resposta;
                    if (resposta == 'S' || resposta == 's') {
                        cout << "Arma " << armaEquipada->getName() << " desequipada." << endl;
                        this->addItem(*armaEquipada); // Adiciona a arma de volta ao inventario
                        armaEquipada = nullptr;
                    } else {
                        cout << "Operacao de equipar arma cancelada." << endl;
                        return false;
                    }
                }
                armaEquipada = arma;
                cout << "Arma " << armaEquipada->getName() << " equipada." << endl;
                this->removeItem(itemName); // Remove a arma do inventario
                return true;
            } else {
                cout << "O item " << itemName << " nao e uma arma." << endl;
                return false;
            }
        }
    }
    cout << "Item " << itemName << " nao encontrado no inventario." << endl;
    return false;
}