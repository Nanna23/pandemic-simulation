#include "Pandemic.hpp"

#include <iostream>

#include "Population.hpp"

namespace Model {
Model::Pandemic::Pandemic(double beta, double gamma)
    : beta{beta}, gamma{gamma} {}
void Model::Pandemic::calculateNextStage(Population population) {
  int S = population.getS();
  int I = population.getI();
  int R = population.getR();
  int N = population.getN();
  int newS = S - beta * (S * I) / N;
  int newI = I + beta * (S * I) / N - gamma * I;
  int newR = R + gamma * I;
  population.update(newS, newI, newR);
  // dall'indirizzo di casa ottengo la casa presente lì
  // e la sostituisco con una nuova casa con i dati aggiornati
  // sostitusco la population a quel indirizzo con una aggiornata prendendo
  // da un altro indirizzo la population nuova
  // new model::Population mi da il pointer
  //(*populationPointer) = *(new Model::Population(newS, newI, newR));
}
}  // namespace Model
