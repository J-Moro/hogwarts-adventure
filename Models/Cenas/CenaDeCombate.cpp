#include "CenaDeCombate.h"

CenaDeCombate::CenaDeCombate(string nomeArquivo) : Cena(nomeArquivo) {}
CenaDeCombate::~CenaDeCombate(){}

void CenaDeCombate::exibirCena() {
    cout << getTexto() << endl;
    //implementar texto avisando que um monstro chegou
    //chamar a lógica que inicia o combate - iniciaCombate()
}

void CenaDeCombate::setMonstro(Monstro monstro) {
    this.monstro = monstro;
}

//cena que o jogador vai depois do combate
void CenaDeCombate::setCenasPosCombate(string sucesso, string derrota) {
    this->proximaCenaSucesso = sucesso;
    this->proximaCenaDerrota = derrota;
}

//nome da proxima cena apos resultado
string CenaDeCombate::getProximaCena(bool vitoria) {
    if (vitoria) {
        return proximaCenaSucesso;
    } else {
        return proximaCenaDerrota;
    }
}