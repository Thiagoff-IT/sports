#include "Jogador.h"
#include <sstream>

using namespace std;

Jogador::Jogador(string n, int i, string e, TipoJogador t)
    : nome(n), idade(i), esporte(e), tipo(t) {}

string Jogador::getNome() const {
    return nome;
}

int Jogador::getIdade() const {
    return idade;
}

string Jogador::getEsporte() const {
    return esporte;
}

TipoJogador Jogador::getTipo() const {
    return tipo;
}

int Jogador::getVitorias() const {
    return vitorias;
}

void Jogador::registrarVitoria() {
    vitorias++;
}

void Jogador::registrarDerrota() {
    derrotas++;
}

void Jogador::registrarEmpate() {
    empates++;
}

string Jogador::getEstatisticas() const {
    return nome + " | V:" + to_string(vitorias) +
           " D:" + to_string(derrotas) +
           " E:" + to_string(empates);
}

void Jogador::salvar(ofstream &out) const {
    out << nome << "," << idade << "," << esporte << ","
        << tipo << "," << vitorias << "," << derrotas << "," << empates << endl;
}

Jogador Jogador::carregar(string linha) {
    stringstream ss(linha);
    string nome, esporte;
    int idade, tipo, v, d, e;
    getline(ss, nome, ',');
    ss >> idade; ss.ignore();
    getline(ss, esporte, ',');
    ss >> tipo; ss.ignore();
    ss >> v; ss.ignore();
    ss >> d; ss.ignore();
    ss >> e;
    Jogador j(nome, idade, esporte, (TipoJogador)tipo);
    while(v--) j.registrarVitoria();
    while(d--) j.registrarDerrota();
    while(e--) j.registrarEmpate();
    return j;
}
