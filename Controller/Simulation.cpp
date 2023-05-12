#include "../Model/Pandemic.hpp"
#include "../Model/Population.hpp"
namespace Controller {
class Simulation {
  Model::Population population;  // variabili puntatori a una popolazione
  Model::Pandemic pandemic;      // variabili puntatori a una pandemia
  int stageCount;                // time
 public:
  Simulation(int firstS, int firstI, int firstR, double beta, double gamma)
      : population(firstS, firstI, firstR), pandemic(beta, gamma) {
    // creo una popolazione e mi restituisce il puntatore (sennò posso mettere
    // dopo ):populatio(..), pandemic(..) {) this->population = new
    // Model::Population(firstS, firstI, firstR); creo una pandemia e mi
    // restituisce il puntatore this->pandemic = new Model::Pandemic(beta,
    // gamma);
    this->stageCount = 0;
  }
  void advanceStage() {
    stageCount += 1;
    pandemic.calculateNextStage(&population);
  }
};
}  // namespace Controller