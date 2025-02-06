#include "Entidades/Obstaculos/Plataforma.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "Gerenciadores/GerenciadorColisoes.h"

namespace Entidades::Obstaculos {

Plataforma::Plataforma(ID id, const sf::Vector2f &pos)
    : Obstaculo(id, pos), empuxo(0.f, 0.f) {
  switch (id) {
    case (ID::IDmadeira1):
      std::clog << "Criando nova plataforma de madeira1\n";
      setTextura("/assets/Obstaculos/plataformafase1.png");
      break;

    case (ID::IDmadeira2):
      std::clog << "Criando nova plataforma de madeira2\n";
      setTextura("/assets/Obstaculos/plataformafase2.png");
      break;

    case (ID::IDpedra):
      std::clog << "Criando nova plataforma de pedra\n";
      setTextura("/assets/Obstaculos/chaofase1.png");
      break;

    case (ID::IDgrama):
      std::clog << "Criando nova plataforma de grama\n";
      setTextura("/assets/Obstaculos/chaofase2.png");
      break;

    default:
      break;
  }
}

Plataforma::~Plataforma() {}

void Plataforma::executar() { pGC->notificarColisao(this); }

void Plataforma::obstacular(Entidades::Entidade *pEnt) {}

void Plataforma::colidir(Entidades::Entidade *pEnt, sf::Vector2f ds) {
  sf::Vector2f posEntidade = pEnt->getPos();
  sf::Vector2f velEntidade = pEnt->getVel();

  if (ds.x < 0.f && ds.y < 0.f) {  // Colidiu
    if (ds.x > ds.y) {             // Colisao em X
      if (posEntidade.x < this->getPos().x)
        posEntidade.x += ds.x;
      else
        posEntidade.x -= ds.x;
      velEntidade.x = 0.0f;
    } else {                                   // Colisao em Y
      if (posEntidade.y < this->getPos().y) {  // Colidiu por cima
        posEntidade.y += ds.y;                 // ds eh negativo
        pEnt->setNoChao(true);
      } else {                  // Colidiu por baixo
        posEntidade.y -= ds.y;  // ds eh negativo
      }
      velEntidade.y = 0.0f;
    }
  }
  pEnt->setPos(posEntidade);
  pEnt->setVel(velEntidade);
}

}  // namespace Entidades::Obstaculos
