#include <string>
#include "../model/pandemic.hpp"
#include "../model/population.hpp"

namespace controller {
class Simulation {
  model::Population population;  // variabili puntatori a una popolazione
  model::Pandemic pandemic;      // variabili puntatori a una pandemia
  int stageCount;                // time
 public:
  // creo una popolazione e mi restituisce il puntatore (sennò posso mettere
  // dopo ):population(..), pandemic(..) {) this->population = new
  // model::Population(firstS, firstI, firstR); creo una pandemia e mi
  // restituisce il puntatore this->pandemic = new model::Pandemic(beta,
  // gamma);
  Simulation(int firstS, int firstI, int firstR, double beta, double gamma)
      : population(firstS, firstI, firstR),
        pandemic(beta, gamma),
        stageCount{0} {}
  void advanceStage() {
    stageCount += 1;
    // &population indica il pointer di una variabile population
    // Population* indica il tipo di variabile che è il pointer
    // di qualsiasi oggetto creato dalla classe Population
    pandemic.calculateNextStage(&population);
  }
  std::string getCurrentStateInfo() {
    // voglio che mi restituisce una stringa con i valori S, I, R, t
    std::string currentState =
        "At stage " + std::to_string(stageCount) + " susceptibles are " +
        std::to_string(population.getS()) + ", infected are " +
        std::to_string(population.getI()) + ", removed are " +
        std::to_string(population.getR());
    return currentState;
  }
  model::Population getPopulation() {
    return this->population;
  }
  int getStageCount() {
    return this->stageCount;
  }
};
}  // namespace Controller