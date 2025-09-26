#include "personagens.h"

Personagem::Personagem(){

    //inventario = new Item[MAX_ITEMS];
    itemCount = 0;

}

Personagem::~Personagem(){
    
}

void Personagem::setNome(string n){

    nome = n;

}

void Personagem::setHabilidade(int num){

    habilidade = num;

}

void Personagem::setEnergia(int num){

    energia = num;

}

void Personagem::setSorte(int num){

    sorte = num;

}

void Personagem::setTesouro(int num){

    tesouro = num;

}

void Personagem::setProvisoes(int num){

    provisoes = num;

}

string Personagem::getNome(){

    return nome;

}

int Personagem::getHabilidade(){

    return habilidade;

}

int Personagem::getEnergia(){

    return energia;

}

int Personagem::getSorte(){

    return sorte;

}

int Personagem::getTesouro(){

    return tesouro;

}

int Personagem::getProvisoes(){

    return provisoes;

}

void Personagem::recebeDano(){

    energia -=2;

}

bool Personagem::testaSorte(){

    srand(time(NULL));
    int random = (rand() % 6) + 1;
    
    sorte--;

    if (sorte >= random) {

        return true;

    }

    return false;

}

int Personagem::calcFA(){

    srand(time(NULL));
    int random = (rand() % 10) + 1;

    return habilidade + random;

}

bool Personagem::addItem(Item newItem){

    if (itemCount >= MAX_ITEMS) {
            std::cout << "Inventario cheio!" << std::endl;
            return false;
        }
        //inventario[itemCount] = newItem;
        itemCount++;
        return true;

}

void Personagem::mostrarInventario() {
        std::cout << "Inventário:" << std::endl;
        if (itemCount == 0) {
            std::cout << "  (vazio)" << std::endl;
        }
        for (int i = 0; i < itemCount; i++) {
            std::cout << "  " << (i + 1) << ". Nome: " 
                      //<< inventario[i].getName()
                      //<< ", Tipo: " << inventario[i].getType()
                      //<< ", Combate: " << inventario[i].getCombat()
                      //<< ", FA: " << inventario[i].getFaBonus()
                      //<< ", Dano: " << inventario[i].getDamageBonus()
                      << std::endl;
        }
    }

void Personagem::setInventario(Item* inventarioUsuario){
    this->inventarioUsuario = inventarioUsuario;
}