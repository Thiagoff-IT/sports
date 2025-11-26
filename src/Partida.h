#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>

using namespace std;

struct Resultado {
    int placar1;
    int placar2;
};

class Partida {
private:
    string participante1;
    string participante2;
    Resultado resultado;

public:
    Partida(string p1, string p2);

    void simularResultado();
    void exibir();
};

#endif // PARTIDA_H
