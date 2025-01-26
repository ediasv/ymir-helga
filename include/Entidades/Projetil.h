#pragma once

#include <SFML/System/Vector2.hpp>

#include "Entidades/Entidade.h"
#include "Entidades/Personagens/Personagem.h"

namespace Entidades {

class Projetil : public Entidade {
 private:
  Personagens::Personagem *pPersDono;
  int dano;

 public:
  Projetil(Personagens::Personagem *pPersDono);
  Projetil();
  ~Projetil();

  int getDano();
  Personagens::Personagem *getDono();
  void colidir(Entidade *pE, sf::Vector2f ds = {0, 0});
  void executar();
};

}  // namespace Entidades
