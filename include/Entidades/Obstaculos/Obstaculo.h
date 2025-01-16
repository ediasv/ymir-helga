#include "Entidades/Personagens/Jogador.h"
#include "Entidades/Personagens/Personagem.h"
#include <SFML/System/Vector2.hpp>
namespace Entidades {
namespace Obstaculos {
class Obstaculo : public Entidade {
protected:
  bool danoso;
  Personagens::Jogador *pJog;

public:
  Obstaculo(const bool danoso = false);
  virtual ~Obstaculo();
  virtual void executar() = 0;
  virtual void obstacular(Personagens::Jogador *pJ) = 0;
  virtual void colidir(Entidade *pEnt,
                       sf::Vector2f ds = sf::Vector2f(0.f, 0.f)) = 0;
  const bool ehDanoso() const;
};
} // namespace Obstaculos
} // namespace Entidades
