#ifndef PANDEMIC_HPP
#define PANDEMIC_HPP
#include "population.hpp"

namespace model {
class Pandemic {
  const double beta;
  const double gamma;

 public:
  Pandemic(double beta, double gamma);
  bool calculateNextStage(Population& population);
};
}  // namespace model
#endif
