#include "Ranking.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void Ranking::adicionarPontuacao(string nome, int pontos) {
    classificacao.emplace_back(nome, pontos);
}

void Ranking::gerar() {
    sort(classificacao.begin(), classificacao.end(),
         [](auto &a, auto &b) { return a.second > b.second; });
}

void Ranking::exibir() {
    cout << "\n+" << string(15, '-') << " [*] RANKING FINAL [*] " << string(15, '-') << "+\n";
    cout << "|" << string(53, ' ') << "|\n";

    for (size_t i = 0; i < classificacao.size(); i++) {
        string medalha;
        switch(i) {
            case 0: medalha = "[1st]"; break;
            case 1: medalha = "[2nd]"; break;
            case 2: medalha = "[3rd]"; break;
            default: medalha = "[" + to_string(i+1) + "th]"; break;
        }

        cout << "|  " << medalha << " " << (i+1) << "o lugar - "
             << classificacao[i].first << " (" << classificacao[i].second << " pts)"
             << string(18 - classificacao[i].first.length(), ' ') << "|\n";
    }

    cout << "|" << string(53, ' ') << "|\n";
    cout << "+" << string(53, '-') << "+\n";
}

void Ranking::exportar(string arquivo) {
    ofstream out(arquivo);
    for (auto &r : classificacao)
        out << r.first << "," << r.second << endl;
    out.close();
    cout << "Ranking exportado para " << arquivo << endl;
}
