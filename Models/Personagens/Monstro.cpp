#include "Monstro.h"

Monstro::Monstro(string nome, int habilidade, int energia, int sorte, int tesouro, int provisoes, Item* inventario){
    setNome(nome);
    setHabilidade(habilidade);
    setEnergia(energia);
    setSorte(sorte);
    setTesouro(tesouro);
    setProvisoes(provisoes);
    setInventario(inventario);
    setBonusSorte(false);
}

Monstro::~Monstro(){

}

void Monstro::transferirItens(Personagem &oponente) {
    
    oponente.setTesouro(oponente.getTesouro() + this->getTesouro());
    this->setTesouro(0);
    oponente.setProvisoes(oponente.getProvisoes() + this->getProvisoes());
    this->setProvisoes(0);
    
    if (this->getInventario() != nullptr) {
        if (oponente.addItem(*(this->getInventario()))) {
            cout << "\nVoce obteve o item: " << this->getInventario()->getName() << " do monstro!" << endl;
            delete this->getInventario(); // Libera a memória do item do monstro
            this->setInventario(nullptr); // Remove o item do monstro
        } else {
            cout << "\nSeu inventario esta cheio! Nao foi possivel obter o item: " << this->getInventario()->getName() << " do monstro." << endl;
        }
    } else {
        cout << "\nO monstro nao tinha nenhum item para transferir." << endl;
    }
}

void Monstro::mostrarInventario() {
    if (this->inventarioUsuario == nullptr) {
        cout << "(nenhum tesouro)" << endl;
    } else {
        cout << "Tesouro do Monstro: " << this->inventarioUsuario->getName() << endl;
    }
}
