#pragma once

#include "Obstaculo.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

namespace Entidades::Obstaculos {

class Plataforma : public Obstaculo {
private:
  float altura;
  sf::Vector2f empuxo;
  bool ehFlutuante;

public:
  Plataforma(int id, const bool ehFlut = false);
  sf::RectangleShape debug;
  ~Plataforma();
  void executar();
  void obstacular(Entidades::Entidade *pEnt);
  void colidir(Entidades::Entidade *outraEnt,
               sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
};

} // namespace Entidades::Obstaculos
