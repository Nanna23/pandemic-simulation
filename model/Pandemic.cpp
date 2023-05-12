#include "Pandemic.hpp"

#include "Population.hpp"

namespace Model {
Model::Pandemic::Pandemic(double beta, double gamma)
    : beta{beta}, gamma{gamma} {}
void Model::Pandemic::calculateNextStage(Population* populationPointer) {
  Population population = *populationPointer;
  int S = population.getS();
  int I = population.getI();
  int R = population.getR();
  int N = population.getN();
  int newS = S - beta * (S * I) / N;
  int newI = I + beta * (S * I) / N - gamma * I;
  int newR = R + gamma * I;
  populationPointer = new Model::Population(newS, newI, newR);
}
}  // namespace Model
