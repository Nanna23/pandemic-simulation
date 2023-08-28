#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../model/population.hpp"

#include "doctest.h"

TEST_CASE("Testing the class handling a population") {
  model::Population population{500, 100, 50};
  SUBCASE("Testing update of population with wrong data") {
    population.update(1000, 1000, 1000);
    CHECK(population.getS() == 500);
    CHECK(population.getI() == 100);
    CHECK(population.getR() == 50);
    CHECK(population.getN() == 650);
  }
  SUBCASE("Testing update of population with correct data") {
    population.update(400, 200, 50);
    CHECK(population.getS() == 400);
    CHECK(population.getI() == 200);
    CHECK(population.getR() == 50);
    CHECK(population.getN() == 650);
  }
}
