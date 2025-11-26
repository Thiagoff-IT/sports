#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <string>
#include <vector>
#include "Jogador.h"

using namespace std;

class Persistencia {
public:
    static void salvarJogadores(const vector<Jogador>& jogadores, string arquivo);
};

#endif // PERSISTENCIA_H
