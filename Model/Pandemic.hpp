#ifndef PANDEMIC_HPP
#define PANDEMIC_HPP

#include "Population.hpp"

namespace Model {
class Pandemic {
  double beta;
  double gamma;

 public:
  Pandemic(double beta, double gamma);
  void calculateNextStage(Population population);
};
}  // namespace Model
#endif