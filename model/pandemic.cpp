#include "pandemic.hpp"

#include <iostream>
#include <numeric>
#include <vector>

#include "population.hpp"

namespace model {
model::Pandemic::Pandemic(double beta, double gamma)
    : beta{beta}, gamma{gamma} {}
void model::Pandemic::calculateNextStage(Population* populationPtr) {
  int S = (*populationPtr).getS();
  // parentesi per precedenza del puntatore
  int I = (*populationPtr).getI();
  int R = (*populationPtr).getR();
  int N = (*populationPtr).getN();
  if (N == 0) {
    return;
  }

  int newS = S - beta * (S * I) / N;
  double dS = S - beta * (S * I) / N;
  double diffS = dS - newS;
  int newI = I + beta * (S * I) / N - gamma * I;
  double dI = I + beta * (S * I) / N - gamma * I;
  double diffI = dI - newI;
  int newR = R + gamma * I;
  double dR = R + gamma * I;
  double diffR = dR - newR;
  std::vector<double> diffs{diffS, diffI, diffR};
  std::vector<int*> values{&newS, &newI, &newR};
  for (int i = 0; i < 3 - 1; i++) {
    for (int j = 0; j < 3 - i - 1; j++) {
      if (diffs[j] < diffs[j + 1]) {
        std::swap(diffs[j], diffs[j + 1]);
        std::swap(values[j], values[j + 1]);
      }
    }
  }

  double diffSum = diffS + diffI + diffR;
  while (diffSum > 0) {
    (*values[0]) += 1;
    diffSum -= 1;
    diffs.erase(diffs.begin());
    values.erase(values.begin());
  }
  (*populationPtr).update(newS, newI, newR);

  // dall'indirizzo di casa ottengo la casa presente lì
  // e la sostituisco con una nuova casa con i dati aggiornati
  // sostitusco la population a quel indirizzo con una aggiornata prendendo
  // da un altro indirizzo la population nuova
  // new model::Population mi da il pointer
  // (*populationPointer) = *(new model::Population(newS, newI, newR));
}
}  // namespace model
