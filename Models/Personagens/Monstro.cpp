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
    for (int i = 0; i < 10; i++) {
        //if (this->addItem(oponente.inventario[i])) {
          //  oponente.inventario[i] = Item(); // Remove o item do oponente
        //} else {
          //  break; // Inventário cheio, para de transferir
        //}
    }
}

void Monstro::mostrarInventario() {
    if (this->inventarioUsuario == nullptr) {
        cout << "(nenhum tesouro)" << endl;
    } else {
        cout << "Tesouro do Monstro: " << this->inventarioUsuario->getName() << endl;
    }
}
