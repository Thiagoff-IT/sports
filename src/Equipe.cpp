#include "Equipe.h"
#include <iostream>

using namespace std;

Equipe::Equipe(string n) : nome(n) {}

void Equipe::adicionarJogador(Jogador j) {
    jogadores.push_back(j);
}

void Equipe::removerJogador(string nomeJogador) {
    for(auto it = jogadores.begin(); it != jogadores.end(); ++it) {
        if(it->getNome() == nomeJogador) {
            jogadores.erase(it);
            break;
        }
    }
}

void Equipe::alterarNome(string novoNome) {
    nome = novoNome;
}

 bool Equipe::temJogador(string nomeJogador) const {
    for(const auto& jogador : jogadores) {
        if(jogador.getNome() == nomeJogador) {
            return true;
        }
    }
    return false;
}

string Equipe::getNome() const {
    return nome;
}

vector<Jogador> Equipe::getJogadores() const {
    return jogadores;
}

int Equipe::getTamanho() const {
    return jogadores.size();
}

void Equipe::listarJogadores() const {
    cout << "+-- " << nome << " " << string(30, '-') << "\n";
    cout << "|\n";
    for (auto &j : jogadores) {
        cout << "|  [Jogador] " << j.getEstatisticas() << "\n";
    }
    cout << "|\n";
    cout << "+" << string(nome.length() + 35, '-') << "\n";
}
