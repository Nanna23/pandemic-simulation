#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../controller/simulation.hpp"

#include "doctest.h"

TEST_CASE("Testing the class handling a simulation") {
  controller::Simulation simulation{1000, 500, 50, 0.5, 0.7, 1};
  SUBCASE("Testing creation of a simulation with negative t") {
    CHECK_THROWS_AS(new controller::Simulation(1000, 500, 50, 0.5, 0.7, -4), const std::invalid_argument&);
  }
  SUBCASE("Testing advancing stages of a simulation") {
    CHECK(simulation.getStageCount() == 0);
    CHECK(simulation.advanceStage());
    CHECK(simulation.getStageCount() == 1);

    // checking that simulation does not advance past t stages
    CHECK_FALSE(simulation.advanceStage());
    CHECK(simulation.getStageCount() == 1);
  }
}
