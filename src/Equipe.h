#ifndef EQUIPE_H
#define EQUIPE_H

#include <string>
#include <vector>
#include "Jogador.h"

using namespace std;

class Equipe {
private:
    string nome;
    vector<Jogador> jogadores;

public:
    explicit Equipe(string n);

    void adicionarJogador(Jogador j);
    void removerJogador(string nomeJogador);
    void alterarNome(string novoNome);
    bool temJogador(string nomeJogador) const;
    string getNome() const;
    vector<Jogador> getJogadores() const;
    int getTamanho() const;
    void listarJogadores() const;
};

#endif // EQUIPE_H
