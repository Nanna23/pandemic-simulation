#include <string>
#include <stdexcept>

#include "../model/pandemic.hpp"
#include "../model/population.hpp"

namespace controller {
class Simulation {
  model::Population population;
  model::Pandemic pandemic;
  int currentStage;
  const int t;

 public:
  Simulation(int firstS, int firstI, int firstR, double beta, double gamma, int t)
      : population(firstS, firstI, firstR),
        pandemic(beta, gamma),
        currentStage{0},
        t{t} {
    if (t < 0) {
     throw std::invalid_argument("The provided t value is a negative number.");
    }
  }
  bool advanceStage() {
    if (currentStage < t) {
      currentStage += 1;
      return pandemic.calculateNextStage(population);
    }

    return false;
  }
  std::string getCurrentStateInfo() {
    return "At stage " + std::to_string(currentStage) + " susceptibles are " +
        std::to_string(population.getS()) + ", infected are " +
        std::to_string(population.getI()) + ", removed are " +
        std::to_string(population.getR());
  }
  model::Population getPopulation() { return this->population; }
  int getStageCount() { return this->currentStage; }
};
}  // namespace controller
