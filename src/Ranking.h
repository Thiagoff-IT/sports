#ifndef RANKING_H
#define RANKING_H

#include <string>
#include <vector>

using namespace std;

class Ranking {
private:
    vector<pair<string, int>> classificacao;

public:
    void adicionarPontuacao(string nome, int pontos);
    void gerar();
    void exibir();
    void exportar(string arquivo);
};

#endif // RANKING_H
