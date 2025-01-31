#include "Fabrica/FabricaEntidadesCaverna.h"

#include <iostream>

#include "Entidades/Obstaculos/Plataforma.h"
#include "Fabrica/FabricaEntidades.h"
#include "IDs.h"

using namespace Entidades;

namespace Fabricas {

FabEntCaverna *FabEntCaverna::instancia = nullptr;

FabEntCaverna::FabEntCaverna() : FabricaEntidades() {
  std::clog << "Criando FabEntPlanicie\n";
}

FabEntCaverna::~FabEntCaverna() { std::clog << "Destruindo FabEntCaverna\n"; }

FabEntCaverna *FabEntCaverna::getInstancia() {
  if (!instancia) {
    instancia = new FabEntCaverna();
  }
  return instancia;
}

Obstaculos::Plataforma *FabEntCaverna::criarMadeira(const sf::Vector2f &pos) {
  Obstaculos::Plataforma *novaPlat =
      new Obstaculos::Plataforma(ID::IDmadeira1, pos);
  return novaPlat;
}

Obstaculos::Plataforma *FabEntCaverna::criarChao(const sf::Vector2f &pos) {
  Obstaculos::Plataforma *novaPlat =
      new Obstaculos::Plataforma(ID::IDpedra, pos);
  return novaPlat;
}

Entidade *FabEntCaverna::criarEntidade(char tipoEntidade,
                                       const sf::Vector2f &pos) {
  switch (tipoEntidade) {
    case 'E':
      return criarEsqueleto(pos);
    case 'S':
      return criarSlime(pos);
    case 'P':
      return criarChao(pos);
    case 'M':
      return criarMadeira(pos);
    case 'G':
      return criarGosma(pos);
    case 'J':
      return criarJogador(pos);
    default:
      return nullptr;
  }
}

}  // namespace Fabricas
