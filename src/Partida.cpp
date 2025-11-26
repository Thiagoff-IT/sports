#include "Partida.h"
#include <iostream>
#include <random>

using namespace std;

Partida::Partida(string p1, string p2) : participante1(p1), participante2(p2) {}

void Partida::simularResultado() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 5);
    resultado.placar1 = dis(gen);
    resultado.placar2 = dis(gen);
}

void Partida::exibir() {
    cout << "[JOGO] " << participante1 << " [" << resultado.placar1
         << "] X [" << resultado.placar2
         << "] " << participante2;

    // Adicionar indicador de vencedor
    if (resultado.placar1 > resultado.placar2) {
        cout << " -> Vitoria de " << participante1;
    } else if (resultado.placar2 > resultado.placar1) {
        cout << " -> Vitoria de " << participante2;
    } else {
        cout << " -> Empate!";
    }
    cout << endl;
}
