#ifndef TORNEIO_H
#define TORNEIO_H

#include <string>
#include <vector>
#include "Enums.h"
#include "Partida.h"

using namespace std;

class Torneio {
private:
    string nome;
    ModalidadeTorneio modalidade;
    vector<string> participantes;
    vector<Partida> partidas;

public:
    Torneio(string n, ModalidadeTorneio m);

    void adicionarParticipante(string p);
    void gerarRodadas();
    void simularPartidas();
};

#endif // TORNEIO_H
