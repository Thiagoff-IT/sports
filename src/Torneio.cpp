#include "Torneio.h"
#include <iostream>

using namespace std;

Torneio::Torneio(string n, ModalidadeTorneio m) : nome(n), modalidade(m) {}

void Torneio::adicionarParticipante(string p) {
    participantes.push_back(p);
}

void Torneio::gerarRodadas() {
    for (size_t i = 0; i < participantes.size(); i += 2) {
        if (i + 1 < participantes.size()) {
            partidas.emplace_back(participantes[i], participantes[i + 1]);
        }
    }
    cout << "[OK] " << partidas.size() << " partida(s) programada(s) para o torneio!" << endl;
}

void Torneio::simularPartidas() {
    for (auto &p : partidas) {
        p.simularResultado();
        p.exibir();
    }
}
