#include <stdexcept>

#include "population.hpp"

namespace model {
// S dentro graffa è quella fornita nella creazione, quella fuori è attributo
model::Population::Population(int S, int I, int R) : S{S}, I{I}, R{R}, N{S+I+R} {
  if (S < 0 || I < 0 || R < 0) {
    throw std::invalid_argument("The provided S, I or R value is a negative number.");
  }
  if (N <= 0) {
    throw std::invalid_argument("The total number of people is less than 1.");
  }
}
int model::Population::getS() { return this->S; }
int model::Population::getI() { return this->I; }
int model::Population::getR() { return this->R; }
int model::Population::getN() { return this->N; }
bool model::Population::update(int S, int I, int R) {
  if (S < 0 || I < 0 || R < 0 || N <= 0 || S + I + R != this->getN()) {
    return false;
  }

  this->S = S;
  this->I = I;
  this->R = R;
  return true;
}
}  // namespace model
