#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../controller/simulation.cpp"

#include "doctest.h"

TEST_CASE("Testing the class handling a simulation") {
  controller::Simulation simulation{1000, 500, 50, 0.5, 0.7};
  SUBCASE("Testing the stage count of a simulation") {
    CHECK(simulation.getStageCount() == 0);
    simulation.advanceStage();
    CHECK(simulation.getStageCount() == 1);
  }
}
