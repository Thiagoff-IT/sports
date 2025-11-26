#include "Persistencia.h"
#include <fstream>

using namespace std;

void Persistencia::salvarJogadores(const vector<Jogador>& jogadores, string arquivo) {
    ofstream out(arquivo);
    for (auto &j : jogadores)
        j.salvar(out);
    out.close();
}
