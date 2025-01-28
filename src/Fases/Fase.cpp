#include "Fases/Fase.h"

#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "Entidades/Personagens/Esqueleto.h"
#include "Entidades/Personagens/Jogador.h"
#include "Gerenciadores/GerenciadorColisoes.h"
#include "Gerenciadores/GerenciadorInput.h"
#include "IDs.h"
#include "Listas/ListaEntidades.h"

using namespace Entidades;

namespace Fases {

Fase::Fase()
    : Ente(ID::IDfase),
      ehPrimeiroJogador(true),
      listaObstaculos(),
      listaPersonagens(),
      pFE(nullptr) {
  pGC = Gerenciadores::Gerenciador_Colisoes::getInstancia();
  pGI = Gerenciadores::Gerenciador_Input::getInstancia();

  listaObstaculos.limpar();
  listaPersonagens.limpar();
}

Fase::~Fase() {
  pGC = nullptr;
  pGI = nullptr;
  listaObstaculos.limpar();
  listaPersonagens.limpar();
}

void Fase::executar() {
  listaObstaculos.percorrer();
  listaPersonagens.percorrer();

  pGC->executar();
}

void Fase::incluirNoColisor() {
  Listas::Lista<Entidades::Entidade *>::Iterator it;

  for (it = listaObstaculos.begin(); it != listaObstaculos.end(); ++it) {
    pGC->incluirObst(dynamic_cast<Obstaculos::Obstaculo *>(*(*it)));
  }

  // Inclui personagens na lista de personagens do GC
  for (it = listaPersonagens.begin(); it != listaPersonagens.end(); ++it) {
    pGC->incluirPers(
        dynamic_cast<Entidades::Personagens::Personagem *>(*(*it)));
  }
}

void Fase::criarMapa(const std::string path) {
  std::ifstream arquivoMapa;
  std::string filePath = ROOT;
  filePath += path;

  arquivoMapa.open(filePath);
  if (!arquivoMapa.is_open()) {
    std::cout << "Erro ao abrir arquivo de mapa" << std::endl;
    exit(1);
  }

  std::string linha;
  for (int j = 0; std::getline(arquivoMapa, linha); j++) {
    for (int i = 0; i < linha.size(); i++) {
      if (linha[i] != ' ') {
        pFE->criarEntidade(linha[i], sf::Vector2f(i * 16, j * 16));
        // TODO: Adicionar entidades criadas nas listas (personagens e
        // obstaculos)
      }
    }
  }

  arquivoMapa.close();

  incluirNoColisor();
}

// WARNING: Quando tirar a criarJogador daqui, nao teremos mais acesso ao pGI
// TODO: Talvez passar parametros para a construcao do jogador?
// o att ehPrimrioJogador ja existe na classe Jogador, deixar ele estatico la
void Fase::criarJogador(const sf::Vector2f &pos) {
  Personagens::Jogador *novoJog =
      new Personagens::Jogador(pos, ehPrimeiroJogador);

  // TODO: Talvez alterar a construtora de jogador para receber ponteiro pro GI
  pGI->inscrever(novoJog->getControlador());

  listaPersonagens.incluir(novoJog);

  ehPrimeiroJogador = false;
}

// TODO: Refatorar considerando Factory
void Fase::criarEsqueleto(const sf::Vector2f &pos) {
  Personagens::Inimigos::Esqueleto *novoEsq =
      new Personagens::Inimigos::Esqueleto(pos);
  listaPersonagens.incluir(novoEsq);
}

}  // namespace Fases
