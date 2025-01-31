#include "Gerenciadores/GerenciadorGrafico.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>

#include "Ente.h"

namespace Gerenciadores {

GerenciadorGrafico *GerenciadorGrafico::instancia = nullptr;

GerenciadorGrafico::GerenciadorGrafico() : deltaTempo(0.f) {
  pJanela = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()),
                                 "Skjolder e Helga", sf::Style::Fullscreen);
  pJanela->setVerticalSyncEnabled(true);
  pJanela->setFramerateLimit(30);
  pJanela->requestFocus();

  larguraJanela = pJanela->getSize().x;
  alturaJanela = pJanela->getSize().y;

  relogio.restart();

  std::clog << "GerenciadorGrafico criado\n";
}

GerenciadorGrafico::~GerenciadorGrafico() {
  std::clog << "Destruindo GerenciadorGrafico\n";

  pJanela = nullptr;
  delete instancia;
}

GerenciadorGrafico *GerenciadorGrafico::getInstancia() {
  if (!instancia) {
    instancia = new GerenciadorGrafico();
  }
  return instancia;
}

bool GerenciadorGrafico::janelaAberta() { return pJanela->isOpen(); }

void GerenciadorGrafico::display() { pJanela->display(); }

void GerenciadorGrafico::clear() { pJanela->clear(); }

void GerenciadorGrafico::desenharEnte(Ente *pE) {
  if (pJanela && pE) {
    pJanela->draw(pE->getSprite());
  } else {
    std::cerr
        << "erro: parametro invalido: Gerenciador_Grafico::desenharEnte()\n";
    exit(EXIT_FAILURE);
  }
}

void GerenciadorGrafico::fecharJanela() {
  pJanela->close();
  pJanela = nullptr;
}

sf::Texture GerenciadorGrafico::carregarTex(const std::string &path) {
  sf::Texture textura;
  std::string filePath = ROOT;
  filePath += path;
  if (!textura.loadFromFile(path)) {
    std::cerr << "Erro em loadFromFile\n";
    exit(EXIT_FAILURE);
  }
  return textura;
}

sf::RenderWindow *GerenciadorGrafico::getJanela() const { return pJanela; }

void GerenciadorGrafico::atualizaDeltaTempo() {
  deltaTempo = relogio.restart().asMilliseconds();
}

const float GerenciadorGrafico::getDeltaTempo() const { return deltaTempo; }

const float GerenciadorGrafico::getLarguraJanela() const {
  return larguraJanela;
}
const float GerenciadorGrafico::getAlturaJanela() const { return alturaJanela; }

}  // namespace Gerenciadores
