#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "../model/pandemic.hpp"
#include "../model/population.hpp"

namespace controller {

class Simulation {
  model::Population population;
  model::Pandemic pandemic;
  int currentStage;
  const int t;

 public:
  Simulation(int firstS, int firstI, int firstR, double beta, double gamma,
             int t);
  bool advanceStage();
  model::Population getPopulation();
  int getStageCount();
};
}  // namespace controller
#endif