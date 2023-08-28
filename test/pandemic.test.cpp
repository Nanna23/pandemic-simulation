#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../model/pandemic.hpp"

#include "doctest.h"

TEST_CASE("Testing the class handling a pandemic") {
  model::Pandemic pandemic{0.5, 0.7};
  SUBCASE("Testing population with no people inside") {
    model::Population emptyPopulation{0, 0, 0};
    pandemic.calculateNextStage(&emptyPopulation);
    CHECK(emptyPopulation.getS() == 0);
    CHECK(emptyPopulation.getI() == 0);
    CHECK(emptyPopulation.getR() == 0);
    CHECK(emptyPopulation.getN() == 0);
  }
  SUBCASE("Testing a random population") {
    model::Population population{1200, 6, 0};
    pandemic.calculateNextStage(&population);
    CHECK(population.getS() == 1197);
    CHECK(population.getI() == 5);
    CHECK(population.getR() == 4);
    CHECK(population.getN() == 1206);
  }
}
