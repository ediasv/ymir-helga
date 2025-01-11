#include "Gerenciadores/GerenciadorGrafico.h"
#include <catch2/catch.hpp>
#include <cstdio>
#include <ctime>

using namespace Gerenciadores;

TEST_CASE("Gerenciador grafico") {
  Gerenciador_Grafico *pGG = Gerenciador_Grafico::getInstancia();

  SECTION("Metodo getInstancia() retorna ponteiro valido") {
    REQUIRE(pGG != nullptr);
  }
}
