#include "Entidades/Personagens/Slime.h"

#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "Entidades/Personagens/Inimigo.h"
#include "Entidades/Personagens/Jogador.h"
#include "Entidades/Projetil.h"
#include "IDs.h"

namespace Entidades::Personagens::Inimigos {

Slime::Slime(const sf::Vector2f &pos) : Inimigo(ID::IDslime) {
  std::clog << "Criando novo slime\n";

  setTextura("/assets/Personagens/Slime.png");
}

Slime::~Slime() {}

void Slime::colidir(Entidade *pEnt, sf::Vector2f ds) {
  if (ds.x < 0 && ds.y < 0) {
    if (pEnt->getId() == ID::IDjogador) {
      dynamic_cast<Jogador *>(pEnt)->aplicaLentidao(viscosidade);
      dynamic_cast<Jogador *>(pEnt)->tomarDano(getDano());
    } else if (pEnt->getId() == ID::IDprojetil) {
      if (dynamic_cast<Projetil *>(pEnt)->getDono()->getId() == ID::IDjogador) {
        tomarDano(dynamic_cast<Projetil *>(pEnt)->getDano());
      }
    }
  }
}
void Slime::executar() {
  // FIX: segfault no metodo perseguir
  // (O seg fault acontece por que a classe inimigo nao tem os ponteiros para
  // jogadores inicializados) perseguir();
  mover();
}

void Slime::atacar() {}

}  // namespace Entidades::Personagens::Inimigos
