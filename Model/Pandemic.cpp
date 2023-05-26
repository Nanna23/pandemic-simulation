#include "pandemic.hpp"

#include <iostream>

#include "population.hpp"

namespace model {
model::Pandemic::Pandemic(double beta, double gamma)
    : beta{beta}, gamma{gamma} {}
void model::Pandemic::calculateNextStage(Population* populationPtr) {
  int S = (*populationPtr).getS();
  //parentesi per precedenza del puntatore
  int I = (*populationPtr).getI();
  int R = (*populationPtr).getR();
  int N = (*populationPtr).getN();
  int newS = S - beta * (S * I) / N;
  int newI = I + beta * (S * I) / N - gamma * I;
  int newR = R + gamma * I;
  (*populationPtr).update(newS, newI, newR);

  // dall'indirizzo di casa ottengo la casa presente lì
  // e la sostituisco con una nuova casa con i dati aggiornati
  // sostitusco la population a quel indirizzo con una aggiornata prendendo
  // da un altro indirizzo la population nuova
  // new model::Population mi da il pointer
  //(*populationPointer) = *(new model::Population(newS, newI, newR));
}
}  // namespace model
