#include <cmath>
#include <stdexcept>

#include "pandemic.hpp"
#include "population.hpp"

namespace model {
model::Pandemic::Pandemic(double beta, double gamma)
    : beta{beta}, gamma{gamma} {
  if (beta < 0 || gamma < 0) {
    throw std::invalid_argument("The provided beta or gamma value is a negative number.");
  }
  if (beta > 1 || gamma > 1) {
    throw std::invalid_argument("The provided beta or gamma value is greater than 1.");
  }
}
bool model::Pandemic::calculateNextStage(Population& population) {
  const int S = population.getS();
  const int I = population.getI();
  const int R = population.getR();
  const int N = population.getN();

  const double dS = S - beta * (S * I) / N;
  int newS = std::round(dS);
  const double dI = I + beta * (S * I) / N - gamma * I;
  int newI = std::round(dI);
  const double dR = R + gamma * I;
  int newR = std::round(dR);

  // per garantire S+I+R = N
  double roundingError = N - (newS + newI + newR);
  if (roundingError > 0) {
    // aggiunge l'unità in più al valore più grande
    if (newS >= newI && newS >= newR) {
      newS += roundingError;
    } else if (newI >= newR) {
      newI += roundingError;
    } else {
      newR += roundingError;
    }
  } else if (roundingError < 0) {
    // aggiunge l'unità in più al valore più piccolo
    if (newS <= newI && newS <= newR) {
      newS += roundingError;
    } else if (newI <= newR) {
      newI += roundingError;
    } else {
      newR += roundingError;
    }
  }

  return population.update(newS, newI, newR);
}
}  // namespace model
