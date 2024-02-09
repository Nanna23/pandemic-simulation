#include <string>

#include "../model/pandemic.hpp"
#include "../model/population.hpp"

namespace controller {
class Simulation {
  model::Population population;
  model::Pandemic pandemic;
  int stageCount;

 public:
  Simulation(int firstS, int firstI, int firstR, double beta, double gamma)
      : population(firstS, firstI, firstR),
        pandemic(beta, gamma),
        stageCount{0} {}
  void advanceStage() {
    stageCount += 1;
    pandemic.calculateNextStage(population);
  }
  std::string getCurrentStateInfo() {
    return "At stage " + std::to_string(stageCount) + " susceptibles are " +
        std::to_string(population.getS()) + ", infected are " +
        std::to_string(population.getI()) + ", removed are " +
        std::to_string(population.getR());
  }
  model::Population getPopulation() { return this->population; }
  int getStageCount() { return this->stageCount; }
};
}  // namespace controller
