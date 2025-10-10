#include "personagens.h"

Personagem::Personagem(){
    inventarioUsuario = new Item[MAX_ITEMS];
    itemCount = 0;
}

Personagem::~Personagem(){}

void Personagem::setNome(string n) {
    nome = n;
}

void Personagem::setHabilidade(int num) {
    habilidade = num;
}

void Personagem::setEnergia(int num) {
    energia = num;
}

void Personagem::setSorte(int num) {
    sorte = num;
}

void Personagem::setTesouro(int num) {
    tesouro = num;
}

void Personagem::setProvisoes(int num) {
    provisoes = num;
}

string Personagem::getNome() {
    return nome;
}

int Personagem::getHabilidade() {
    return habilidade;
}

int Personagem::getEnergia() {
    return energia;
}

int Personagem::getSorte() {
    return sorte;
}

int Personagem::getTesouro() {
    return tesouro;
}

int Personagem::getProvisoes() {
    return provisoes;
}

int Personagem::getMaxItems() {
    return MAX_ITEMS;
}

int Personagem::getQuantidadeItens() {
    return itemCount;
}

void Personagem::recebeDano() {
    this->energia -=2;
}

bool Personagem::testaSorte() {
    if (sorte > 0) {
        cout << "\nTeste de sorte: SORTE deve ser maior ou igual ao DADO" << endl;
        int random = (rand() % 6) + 1;
        cout << "\nJogando dado...    " << random << endl;

        sorte--;

        if ((sorte + 1) >= random) {
            return true;
        }
    }
    return false;
}

int Personagem::calcFA() {
    cout << "\nForca de ataque = HABILIDADE + DADO" << endl;
    int random = (rand() % 10) + 1;

    cout << "\nJogando dado...    " << random << endl;
    cout << "\nForca de ataque do " << nome << " : " << habilidade + random << endl;

    return habilidade + random;
}

bool Personagem::addItem(Item newItem) {
    if (itemCount >= MAX_ITEMS) {
            cout << "Inventario cheio!" << endl;
            return false;
        }
    inventarioUsuario[itemCount] = newItem;
    itemCount++;
    return true;
}

bool Personagem::removeItem(string itemName) {
    for (int i = 0; i < itemCount; i++) {
        
        if (inventarioUsuario[i].getName() == itemName) {
            inventarioUsuario[i] = inventarioUsuario[itemCount - 1];
            
            itemCount--;
            return true;
        }
    }
    return false;
}

bool Personagem::possuiItem(string nomeItem) {
    if (armaEquipada.getName() == nomeItem) {
        return true;
    }
    return false;
}

void Personagem::mostrarInventario() {
        cout << "Inventario:" << endl;
        cout << "Habilidade: " << habilidade << ", Energia: " << energia << ", Sorte: " << sorte << endl;
        cout << "Provisoes: " << provisoes << ", Tesouro: " << tesouro << endl;
        cout << "Arma equipada: " << armaEquipada.getName() << endl;
        
        if (itemCount == 0) {
            cout << "  (vazio)" << endl;
        }
        for (int i = 0; i < itemCount; i++) {
            cout << "  " << (i + 1) << ". Nome: " 
                      << inventarioUsuario[i].getName()
                      << ", Tipo: " << inventarioUsuario[i].getType()
                      << ", Combate: " << inventarioUsuario[i].getCombat()
                      << ", FA: " << inventarioUsuario[i].getFaBonus()
                      << ", Dano: " << inventarioUsuario[i].getDamageBonus()
                      << endl;
        }
}

void Personagem::setInventario(Item* inventarioUsuario) {
    this->inventarioUsuario = inventarioUsuario;
}

Item* Personagem::getInventario() {
    return inventarioUsuario;
}

void Personagem::setBonusSorte(bool status) {
    bonusSorte = status;
}

bool Personagem::getBonusSorte() {
    return bonusSorte;
}