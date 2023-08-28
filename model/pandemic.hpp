#ifndef PANDEMIC_HPP
#define PANDEMIC_HPP
#include "population.hpp"

namespace model {
class Pandemic {
  double beta;
  double gamma;

 public:
  Pandemic(double beta, double gamma);
  void calculateNextStage(Population* population);
};
}  // namespace model
#endif
