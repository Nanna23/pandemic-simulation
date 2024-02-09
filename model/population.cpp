#include <stdexcept>

#include "population.hpp"

namespace model {
// S dentro graffa è quella fornita nella creazione, quella fuori è attributo
model::Population::Population(int S, int I, int R) : S{S}, I{I}, R{R} {
  if (S < 0 || I < 0 || R < 0) {
    throw std::invalid_argument("The provided S, I or R value is a negative number.");
  }
}
int model::Population::getS() { return S; }
int model::Population::getI() { return I; }
int model::Population::getR() { return R; }
int model::Population::getN() { return S + I + R; }
bool model::Population::update(int S, int I, int R) {
  if (S + I + R != this->getN()) {
    return false;
  }

  this->S = S;
  this->I = I;
  this->R = R;
  return true;
}
}  // namespace model
