#include <vector>

#include "pandemic.hpp"
#include "population.hpp"

namespace model {
model::Pandemic::Pandemic(double beta, double gamma)
    : beta{beta}, gamma{gamma} {}
void model::Pandemic::calculateNextStage(Population& population) {
  const int S = population.getS();
  const int I = population.getI();
  const int R = population.getR();
  const int N = population.getN();
  if (N == 0) {
    return;
  }

  int newS = S - beta * (S * I) / N;
  const double dS = S - beta * (S * I) / N;
  const double diffS = dS - newS;
  int newI = I + beta * (S * I) / N - gamma * I;
  const double dI = I + beta * (S * I) / N - gamma * I;
  const double diffI = dI - newI;
  int newR = R + gamma * I;
  const double dR = R + gamma * I;
  const double diffR = dR - newR;
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
  // per evitare bug dovuti alla somma di numeri double
  while (diffSum > 0.1) {
    (*values[0]) += 1;
    diffSum -= 1;
    diffs.erase(diffs.begin());
    values.erase(values.begin());
  }
  population.update(newS, newI, newR);
}
}  // namespace model
