#include "Jogador.h"
#include "../Itens/ItemComum.h"
#include "../Itens/ItemMagico.h"

Jogador::Jogador(){
    this->setHabilidade(6);
    this->setEnergia(12);
    this->setSorte(6);

    ItemMagico itemAccio("Accio");
    ItemMagico itemLumus("Lumus");
    ItemComum itemPocao("Pocao do Sono");

    this->addItem(itemAccio);
    this->addItem(itemLumus);
    this->addItem(itemPocao);
}

Jogador::~Jogador(){}

bool Jogador::equiparArma(int numeroItem) {
    Item* inventario = this->getInventario();
    
    numeroItem--;

    for (int i = 0; i < this->getQuantidadeItens(); i++) {
        
        if (inventario[numeroItem].getName() == inventario[i].getName()) {
            Item arma = inventario[i];
            
            
            if (armaEquipada.getName() != "") {
                cout << "Voce ja tem uma arma equipada: " << armaEquipada.getName() << ". Deseja desequipa-la? (S/N)" << endl;
                
                char resposta;
                cin >> resposta;
                
                if (resposta == 'S' || resposta == 's') {
                    cout << "Arma " << armaEquipada.getName() << " desequipada." << endl;
                    
                    this->addItem(armaEquipada);
                    
                } else {
                    cout << "Operacao de equipar arma cancelada." << endl;
                    return false;
                }
            }

            armaEquipada = arma;
            cout << "Arma " << armaEquipada.getName() << " equipada." << endl;
            
            this->removeItem(arma.getName());
            
            return true;
            
        }
    }

    cout << "Item " << numeroItem << " nao encontrado no inventario." << endl;
    
    return false;
}
