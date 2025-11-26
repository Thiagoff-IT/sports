#include <iostream>
#include <vector>
#include <locale>
#include <windows.h>
#include <cstdlib>
#include <string>
#include "src/Jogador.h"
#include "src/Equipe.h"
#include "src/Torneio.h"
#include "src/Ranking.h"
#include "src/Persistencia.h"

using namespace std;

// Estado global do sistema
vector<Jogador> jogadores;
vector<Equipe> equipes;
Ranking ranking;
bool rankingGerado = false;

bool jogadorJaEstaEmEquipe(string nomeJogador) {
    for(const auto& equipe : equipes) {
        if(equipe.temJogador(nomeJogador)) {
            return true;
        }
    }
    return false;
}

string encontrarEquipeDoJogador(string nomeJogador) {
    for(const auto& equipe : equipes) {
        if(equipe.temJogador(nomeJogador)) {
            return equipe.getNome();
        }
    }
    return "";
}

void limparTela() {
    system("cls");
}

void exibirCabecalho() {
    cout << "================================================================\n";
    cout << "||                                                            ||\n";
    cout << "||         [*] SISTEMA DE GERENCIAMENTO ESPORTIVO [*]         ||\n";
    cout << "||                                                            ||\n";
    cout << "||              Organize seus torneios com estilo!            ||\n";
    cout << "||                                                            ||\n";
    cout << "================================================================\n";
    cout << "\n";
}

void exibirMenu() {
    cout << "\n+===============================================================+\n";
    cout << "|                       [>] MENU PRINCIPAL                     |\n";
    cout << "+===============================================================+\n";
    cout << "|  [1]  -> Demonstracao Completa do Sistema [PADRAO]           |\n";
    cout << "|  [2]  -> Criar Jogadores Personalizados                      |\n";
    cout << "|  [3]  -> Organizar Torneio                                   |\n";
    cout << "|  [4]  -> Ver Rankings                                        |\n";
    cout << "|  [5]  -> Gerenciar Equipes                                   |\n";
    cout << "|  [0]  -> Sair do Sistema                                     |\n";
    cout << "+===============================================================+\n";
    cout << "\n>> Digite sua opcao (pressione ENTER para opcao 1): ";
}

void pausar() {
    cout << "\n" << string(60, '-') << "\n";
    cout << "   Pressione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void criarJogadoresPersonalizados() {
    limparTela();
    cout << "\n[*] CRIAR JOGADORES PERSONALIZADOS [*]\n";
    cout << string(50, '=') << "\n\n";

    cout << "[INFO] Vamos cadastrar seus jogadores!\n";
    cout << "Quantos jogadores deseja cadastrar? (minimo 2, maximo 20): ";

    int quantidade;
    cin >> quantidade;
    cin.ignore(); // Limpar buffer

    if(quantidade < 2) {
        cout << "\n[AVISO] Eh necessario pelo menos 2 jogadores para formar equipes!\n";
        quantidade = 2;
        cout << "Ajustando para 2 jogadores...\n\n";
    } else if(quantidade > 20) {
        cout << "\n[AVISO] Maximo de 20 jogadores permitido!\n";
        quantidade = 20;
        cout << "Ajustando para 20 jogadores...\n\n";
    }

    jogadores.clear(); // Limpar jogadores existentes

    for(int i = 0; i < quantidade; i++) {
        cout << "\n[JOGADOR " << (i+1) << "/" << quantidade << "]\n";
        cout << string(25, '-') << "\n";

        string nome, esporte;
        int idade;
        int tipoNivel;

        cout << "Nome: ";
        getline(cin, nome);

        cout << "Idade: ";
        cin >> idade;
        cin.ignore();

        cout << "Esporte: ";
        getline(cin, esporte);

        cout << "Nivel (1-Amador, 2-Profissional): ";
        cin >> tipoNivel;
        cin.ignore();

        TipoJogador nivel = (tipoNivel == 2) ? PROFISSIONAL : AMADOR;

        Jogador novoJogador(nome, idade, esporte, nivel);
        jogadores.push_back(novoJogador);

        cout << "[OK] Jogador " << nome << " cadastrado!\n";
    }

    cout << "\n[SUCCESS] " << jogadores.size() << " jogadores cadastrados com sucesso!\n";
    cout << "\n[LISTA DE JOGADORES]\n";
    cout << string(30, '-') << "\n";

    for(size_t i = 0; i < jogadores.size(); i++) {
        cout << (i+1) << ". " << jogadores[i].getNome()
             << " (" << jogadores[i].getIdade() << " anos, "
             << jogadores[i].getEsporte() << ")\n";
    }

    // Salvar automaticamente
    Persistencia::salvarJogadores(jogadores, "jogadores.csv");
    cout << "\n[INFO] Dados salvos automaticamente em 'jogadores.csv'\n";

    pausar();
}

void gerenciarEquipes() {
    limparTela();
    cout << "\n[*] GERENCIAR EQUIPES [*]\n";
    cout << string(50, '=') << "\n\n";

    // Verificar se existem jogadores
    if(jogadores.empty()) {
        cout << "[AVISO] Nao ha jogadores cadastrados!\n";
        cout << "Eh necessario ter jogadores para formar equipes.\n\n";
        cout << "[DICA] Va para a opcao 2 para cadastrar jogadores primeiro.\n";
        pausar();
        return;
    }

    int opcaoEquipe;
    do {
        cout << "\n[GERENCIAR EQUIPES]\n";
        cout << "1 - Criar Nova Equipe\n";
        cout << "2 - Listar Equipes Existentes\n";
        cout << "3 - Adicionar Jogador a Equipe\n";
        cout << "4 - Remover Jogador da Equipe\n";
        cout << "5 - Editar Nome da Equipe\n";
        cout << "6 - Excluir Equipe\n";
        cout << "7 - Ver Jogadores Livres\n";
        cout << "0 - Voltar ao Menu Principal\n";
        cout << "\nEscolha: ";
        cin >> opcaoEquipe;
        cin.ignore();

        switch(opcaoEquipe) {
            case 1: {
                cout << "\nNome da nova equipe: ";
                string nomeEquipe;
                getline(cin, nomeEquipe);

                Equipe novaEquipe(nomeEquipe);
                equipes.push_back(novaEquipe);

                cout << "[OK] Equipe '" << nomeEquipe << "' criada com sucesso!\n";
                break;
            }
            case 2: {
                if(equipes.empty()) {
                    cout << "\n[INFO] Nenhuma equipe cadastrada ainda.\n";
                } else {
                    cout << "\n[EQUIPES CADASTRADAS]\n";
                    cout << string(50, '=') << "\n";
                    for(size_t i = 0; i < equipes.size(); i++) {
                        cout << (i+1) << ". ";
                        equipes[i].listarJogadores();

                        // Mostrar resumo da equipe
                        cout << "[INFO] Total de jogadores: " << equipes[i].getTamanho() << "\n";
                        cout << "\n";
                    }

                    // Mostrar estatisticas gerais
                    int totalJogadoresEmEquipes = 0;
                    for(const auto& equipe : equipes) {
                        totalJogadoresEmEquipes += equipe.getTamanho();
                    }

                    cout << string(50, '=') << "\n";
                    cout << "[ESTATISTICAS]\n";
                    cout << "Total de equipes: " << equipes.size() << "\n";
                    cout << "Jogadores em equipes: " << totalJogadoresEmEquipes << "\n";
                    cout << "Jogadores livres: " << (jogadores.size() - totalJogadoresEmEquipes) << "\n";
                }
                break;
            }
            case 3: {
                if(equipes.empty()) {
                    cout << "\n[AVISO] Nenhuma equipe existe ainda!\n";
                    cout << "Crie uma equipe primeiro (opcao 1).\n";
                    break;
                }

                cout << "\n[SELECIONAR EQUIPE]\n";
                for(size_t i = 0; i < equipes.size(); i++) {
                    cout << (i+1) << ". " << equipes[i].getNome() << "\n";
                }
                cout << "Escolha a equipe (numero): ";

                int indiceEquipe;
                cin >> indiceEquipe;
                cin.ignore();

                if(indiceEquipe < 1 || indiceEquipe > (int)equipes.size()) {
                    cout << "[ERRO] Equipe invalida!\n";
                    break;
                }

                cout << "\n[SELECIONAR JOGADOR]\n";
                cout << "[JOGADORES DISPONIVEIS]\n";
                vector<int> jogadoresDisponiveis;

                for(size_t i = 0; i < jogadores.size(); i++) {
                    if(!jogadorJaEstaEmEquipe(jogadores[i].getNome())) {
                        jogadoresDisponiveis.push_back(i);
                        cout << (jogadoresDisponiveis.size()) << ". " << jogadores[i].getNome()
                             << " (" << jogadores[i].getIdade() << " anos)\n";
                    }
                }

                if(jogadoresDisponiveis.empty()) {
                    cout << "[AVISO] Todos os jogadores ja estao em equipes!\n";
                    cout << "Para transferir um jogador, remova-o primeiro da equipe atual.\n";
                    break;
                }

                cout << "Escolha o jogador (numero): ";

                int escolha;
                cin >> escolha;
                cin.ignore();

                if(escolha < 1 || escolha > (int)jogadoresDisponiveis.size()) {
                    cout << "[ERRO] Jogador invalido!\n";
                    break;
                }

                int indiceJogador = jogadoresDisponiveis[escolha-1];
                string nomeJogador = jogadores[indiceJogador].getNome();

                // Verificacao adicional antes de adicionar
                if(jogadorJaEstaEmEquipe(nomeJogador)) {
                    string equipeAtual = encontrarEquipeDoJogador(nomeJogador);
                    cout << "[ERRO] " << nomeJogador << " ja esta na equipe '" << equipeAtual << "'!\n";
                    cout << "Para transferir, remova-o primeiro da equipe atual.\n";
                    break;
                }

                equipes[indiceEquipe-1].adicionarJogador(jogadores[indiceJogador]);
                cout << "[OK] Jogador " << nomeJogador << " adicionado a equipe '"
                     << equipes[indiceEquipe-1].getNome() << "'!\n";
                break;
            }
            case 4: { // Remover Jogador da Equipe
                if(equipes.empty()) {
                    cout << "\n[AVISO] Nenhuma equipe existe ainda!\n";
                    break;
                }

                cout << "\n[SELECIONAR EQUIPE]\n";
                for(size_t i = 0; i < equipes.size(); i++) {
                    cout << (i+1) << ". " << equipes[i].getNome()
                         << " (" << equipes[i].getTamanho() << " jogadores)\n";
                }
                cout << "Escolha a equipe (numero): ";

                int indiceEquipe;
                cin >> indiceEquipe;
                cin.ignore();

                if(indiceEquipe < 1 || indiceEquipe > (int)equipes.size()) {
                    cout << "[ERRO] Equipe invalida!\n";
                    break;
                }

                if(equipes[indiceEquipe-1].getTamanho() == 0) {
                    cout << "[AVISO] Esta equipe nao tem jogadores!\n";
                    break;
                }

                cout << "\n[JOGADORES NA EQUIPE]\n";
                vector<Jogador> jogadoresEquipe = equipes[indiceEquipe-1].getJogadores();
                for(size_t i = 0; i < jogadoresEquipe.size(); i++) {
                    cout << (i+1) << ". " << jogadoresEquipe[i].getNome() << "\n";
                }
                cout << "Escolha o jogador para remover (numero): ";

                int indiceJogador;
                cin >> indiceJogador;
                cin.ignore();

                if(indiceJogador < 1 || indiceJogador > (int)jogadoresEquipe.size()) {
                    cout << "[ERRO] Jogador invalido!\n";
                    break;
                }

                string nomeJogador = jogadoresEquipe[indiceJogador-1].getNome();
                equipes[indiceEquipe-1].removerJogador(nomeJogador);
                cout << "[OK] Jogador " << nomeJogador << " removido da equipe!\n";
                break;
            }
            case 5: { // Editar Nome da Equipe
                if(equipes.empty()) {
                    cout << "\n[AVISO] Nenhuma equipe existe ainda!\n";
                    break;
                }

                cout << "\n[SELECIONAR EQUIPE PARA EDITAR]\n";
                for(size_t i = 0; i < equipes.size(); i++) {
                    cout << (i+1) << ". " << equipes[i].getNome() << "\n";
                }
                cout << "Escolha a equipe (numero): ";

                int indiceEquipe;
                cin >> indiceEquipe;
                cin.ignore();

                if(indiceEquipe < 1 || indiceEquipe > (int)equipes.size()) {
                    cout << "[ERRO] Equipe invalida!\n";
                    break;
                }

                cout << "Nome atual: " << equipes[indiceEquipe-1].getNome() << "\n";
                cout << "Novo nome da equipe: ";
                string novoNome;
                getline(cin, novoNome);

                if(!novoNome.empty()) {
                    string nomeAntigo = equipes[indiceEquipe-1].getNome();
                    equipes[indiceEquipe-1].alterarNome(novoNome);
                    cout << "[OK] Nome alterado de '" << nomeAntigo << "' para '" << novoNome << "'!\n";
                } else {
                    cout << "[AVISO] Nome nao pode ser vazio!\n";
                }
                break;
            }
            case 6: { // Excluir Equipe
                if(equipes.empty()) {
                    cout << "\n[AVISO] Nenhuma equipe existe ainda!\n";
                    break;
                }

                cout << "\n[SELECIONAR EQUIPE PARA EXCLUIR]\n";
                for(size_t i = 0; i < equipes.size(); i++) {
                    cout << (i+1) << ". " << equipes[i].getNome()
                         << " (" << equipes[i].getTamanho() << " jogadores)\n";
                }
                cout << "Escolha a equipe (numero): ";

                int indiceEquipe;
                cin >> indiceEquipe;
                cin.ignore();

                if(indiceEquipe < 1 || indiceEquipe > (int)equipes.size()) {
                    cout << "[ERRO] Equipe invalida!\n";
                    break;
                }

                string nomeEquipe = equipes[indiceEquipe-1].getNome();
                cout << "\n[CONFIRMACAO] Deseja realmente excluir a equipe '" << nomeEquipe << "'? (s/n): ";
                char confirmacao;
                cin >> confirmacao;
                cin.ignore();

                if(confirmacao == 's' || confirmacao == 'S') {
                    equipes.erase(equipes.begin() + (indiceEquipe-1));
                    cout << "[OK] Equipe '" << nomeEquipe << "' excluida com sucesso!\n";
                } else {
                    cout << "[INFO] Operacao cancelada.\n";
                }
                break;
            }
            case 7: { // Ver Jogadores Livres
                cout << "\n[JOGADORES LIVRES]\n";
                cout << string(40, '=') << "\n";

                vector<string> jogadoresLivres;
                for(const auto& jogador : jogadores) {
                    if(!jogadorJaEstaEmEquipe(jogador.getNome())) {
                        jogadoresLivres.push_back(jogador.getNome());
                    }
                }

                if(jogadoresLivres.empty()) {
                    cout << "[INFO] Todos os jogadores estao em equipes!\n";
                } else {
                    cout << "[INFO] " << jogadoresLivres.size() << " jogador(es) disponivel(is):\n\n";
                    for(size_t i = 0; i < jogadoresLivres.size(); i++) {
                        // Encontrar o jogador completo para mostrar detalhes
                        for(const auto& jogador : jogadores) {
                            if(jogador.getNome() == jogadoresLivres[i]) {
                                cout << (i+1) << ". " << jogador.getNome()
                                     << " (" << jogador.getIdade() << " anos, "
                                     << jogador.getEsporte() << ")\n";
                                break;
                            }
                        }
                    }
                }

                cout << "\n[DICA] Use a opcao 3 para adicionar jogadores livres as equipes.\n";
                break;
            }
            default:
                cout << "\n[ERRO] Opcao invalida!\n";
                break;
        }
    } while(opcaoEquipe != 0);
}

void organizarTorneio() {
    limparTela();
    cout << "\n[*] ORGANIZAR TORNEIO [*]\n";
    cout << string(50, '=') << "\n\n";

    // Verificar se existem jogadores suficientes
    if(jogadores.size() < 2) {
        cout << "[AVISO] Nao ha jogadores suficientes para um torneio!\n";
        cout << "Eh necessario pelo menos 2 jogadores.\n\n";
        cout << "[DICA] Va para a opcao 2 para cadastrar mais jogadores.\n";
        pausar();
        return;
    }

    cout << "[INFO] Criando torneio com " << jogadores.size() << " jogadores.\n\n";

    string nomeTorneio;
    cout << "Nome do torneio: ";
    getline(cin, nomeTorneio);

    cout << "\nTipo de torneio:\n";
    cout << "1 - Pontos Corridos\n";
    cout << "2 - Eliminacao Simples\n";
    cout << "Escolha: ";

    int tipoTorneio;
    cin >> tipoTorneio;
    cin.ignore();

    ModalidadeTorneio tipo = (tipoTorneio == 2) ? MATA_MATA : PONTOS_CORRIDOS;

    Torneio torneio(nomeTorneio, tipo);

    // Adicionar todos os jogadores
    cout << "\n[INFO] Adicionando participantes...\n";
    for(const auto& jogador : jogadores) {
        torneio.adicionarParticipante(jogador.getNome());
        cout << "   -> " << jogador.getNome() << " adicionado\n";
    }

    cout << "\n[INFO] Gerando rodadas do torneio...\n";
    torneio.gerarRodadas();

    cout << "\n[INFO] Deseja simular as partidas automaticamente? (s/n): ";
    char simular;
    cin >> simular;
    cin.ignore();

    if(simular == 's' || simular == 'S') {
        cout << "\n[INFO] Simulando partidas...\n";
        torneio.simularPartidas();

        // Atualizar ranking global
        cout << "\n[INFO] Atualizando ranking...\n";
        ranking = Ranking(); // Reset ranking

        // Adicionar pontuacoes simuladas (aqui voce pode integrar com os resultados do torneio)
        for(const auto& jogador : jogadores) {
            int pontos = rand() % 10; // Pontuacao aleatoria para demo
            ranking.adicionarPontuacao(jogador.getNome(), pontos);
        }

        ranking.gerar();
        rankingGerado = true;

        cout << "[SUCCESS] Torneio concluido e ranking atualizado!\n";
    } else {
        cout << "[INFO] Torneio criado. Voce pode simular as partidas depois.\n";
    }

    pausar();
}

void verRankings() {
    limparTela();
    cout << "\n[*] VER RANKINGS [*]\n";
    cout << string(50, '=') << "\n\n";

    if(!rankingGerado) {
        cout << "[AVISO] Nenhum ranking foi gerado ainda!\n";
        cout << "Para gerar um ranking, voce precisa:\n";
        cout << "1. Ter jogadores cadastrados\n";
        cout << "2. Organizar e simular um torneio\n\n";
        cout << "[DICA] Va para as opcoes 2 e 3 para configurar e executar um torneio.\n";
        pausar();
        return;
    }

    cout << "[INFO] Exibindo ranking atual:\n\n";
    ranking.exibir();

    cout << "\n[OPCOES]\n";
    cout << "1 - Exportar ranking para CSV\n";
    cout << "2 - Voltar ao menu\n";
    cout << "Escolha: ";

    int opcao;
    cin >> opcao;
    cin.ignore();

    if(opcao == 1) {
        cout << "\nNome do arquivo (sem extensao): ";
        string nomeArquivo;
        getline(cin, nomeArquivo);
        nomeArquivo += ".csv";

        ranking.exportar(nomeArquivo);
        cout << "[SUCCESS] Ranking exportado para '" << nomeArquivo << "'!\n";
    }

    pausar();
}

void demonstracaoCompleta() {
    limparTela();
    cout << "\n[*] DEMONSTRACAO COMPLETA DO SISTEMA [*]\n";
    cout << string(50, '=') << "\n\n";

    // Cadastro de jogadores
    cout << "[INFO] CADASTRANDO JOGADORES...\n";
    cout << string(30, '-') << "\n";

    Jogador j1("Ana Silva", 22, "Futebol", PROFISSIONAL);
    Jogador j2("Carlos Santos", 25, "Futebol", AMADOR);
    Jogador j3("Maria Oliveira", 20, "Futebol", PROFISSIONAL);
    Jogador j4("Joao Costa", 28, "Futebol", AMADOR);

    // Limpar estado anterior e adicionar jogadores ao estado global
    jogadores.clear();
    jogadores = {j1, j2, j3, j4};

    cout << "[OK] Jogadores cadastrados com sucesso!\n";
    for(const auto& j : jogadores) {
        cout << "   -> " << j.getNome() << "\n";
    }

    pausar();

    // Criar equipes
    cout << "\n[INFO] FORMANDO EQUIPES...\n";
    cout << string(30, '-') << "\n";

    // Limpar equipes anteriores e criar novas
    equipes.clear();

    Equipe equipe1("Raios FC");
    equipe1.adicionarJogador(j1);
    equipe1.adicionarJogador(j2);
    equipes.push_back(equipe1);

    Equipe equipe2("Chamas United");
    equipe2.adicionarJogador(j3);
    equipe2.adicionarJogador(j4);
    equipes.push_back(equipe2);

    cout << "\n";
    equipe1.listarJogadores();
    cout << "\n";
    equipe2.listarJogadores();

    pausar();

    // Criar torneio
    cout << "\n[INFO] ORGANIZANDO TORNEIO...\n";
    cout << string(30, '-') << "\n";

    Torneio t("Copa de Verao 2024", PONTOS_CORRIDOS);
    t.adicionarParticipante("Ana Silva");
    t.adicionarParticipante("Carlos Santos");
    t.adicionarParticipante("Maria Oliveira");
    t.adicionarParticipante("Joao Costa");

    cout << "[INFO] Gerando rodadas...\n";
    t.gerarRodadas();

    cout << "\n[INFO] SIMULANDO PARTIDAS...\n";
    cout << string(30, '-') << "\n";
    t.simularPartidas();

    pausar();

    // Ranking
    cout << "\n[INFO] GERANDO RANKING FINAL...\n";
    cout << string(30, '-') << "\n";

    // Usar ranking global
    ranking = Ranking(); // Reset ranking
    ranking.adicionarPontuacao("Ana Silva", 9);
    ranking.adicionarPontuacao("Carlos Santos", 4);
    ranking.adicionarPontuacao("Maria Oliveira", 7);
    ranking.adicionarPontuacao("Joao Costa", 3);
    ranking.gerar();
    ranking.exibir();
    rankingGerado = true; // Marcar que temos um ranking

    cout << "\n[INFO] Exportando dados...\n";
    ranking.exportar("ranking.csv");

    // Persistência
    Persistencia::salvarJogadores(jogadores, "jogadores.csv");
    cout << "[OK] Dados dos jogadores salvos em 'jogadores.csv'\n";

    cout << "\n[SUCCESS] Demonstracao concluida com sucesso!\n";
    pausar();
}

void exibirCreditos() {
    cout << "\n+===============================================================+\n";
    cout << "|                         ATE LOGO!                            |\n";
    cout << "|                                                               |\n";
    cout << "|          Obrigado por usar nosso sistema esportivo!          |\n";
    cout << "|                                                               |\n";
    cout << "|                   Desenvolvido com amor                      |\n";
    cout << "|                                                               |\n";
    cout << "+===============================================================+\n";
    cout << "\n";
}

int main() {
    // Configurar console para Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Configurar locale para UTF-8
    setlocale(LC_ALL, "Portuguese");

    int opcao;

    exibirCabecalho();

    do {
        exibirMenu();

        // Pre-selecionar opcao 1 como padrao
        string input;
        getline(cin, input);

        if(input.empty()) {
            opcao = 1; // Opcao padrao: Demonstracao Completa
            cout << "1 (opcao padrao selecionada)\n";
        } else {
            try {
                opcao = stoi(input);
            } catch(const exception&) {
                opcao = -1; // Opcao invalida
            }
        }

        switch(opcao) {
            case 1:
                demonstracaoCompleta();
                break;

            case 2:
                criarJogadoresPersonalizados();
                break;

            case 3:
                organizarTorneio();
                break;

            case 4:
                verRankings();
                break;

            case 5:
                gerenciarEquipes();
                break;


            case 0:
                exibirCreditos();
                break;

            default:
                cout << "\n[ERRO] Opcao invalida! Por favor, tente novamente.\n";
                pausar();
                break;
        }

    } while(opcao != 0);

    return 0;
}