#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>
#include <fstream>
#include "Enums.h"

using namespace std;

class Jogador {
private:
    string nome;
    int idade;
    string esporte;
    TipoJogador tipo;
    int vitorias = 0;
    int derrotas = 0;
    int empates = 0;

public:
    Jogador(string n, int i, string e, TipoJogador t);

    string getNome() const;
    int getIdade() const;
    string getEsporte() const;
    TipoJogador getTipo() const;
    int getVitorias() const;

    void registrarVitoria();
    void registrarDerrota();
    void registrarEmpate();

    string getEstatisticas() const;
    void salvar(ofstream &out) const;
    static Jogador carregar(string linha);
};

#endif // JOGADOR_H
