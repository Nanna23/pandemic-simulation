#include "population.hpp"

namespace model {
// S dentro graffa è quella fornita nella creazione, quella fuori è attributo
model::Population::Population(int S, int I, int R) : S{S}, I{I}, R{R} {}
int model::Population::getS() { return S; }
int model::Population::getI() { return I; }
int model::Population::getR() { return R; }
int model::Population::getN() { return S + I + R; }
void model::Population::update(int S, int I, int R) {
  if (S + I + R != this->getN()) {
    return;
  }

  this->S = S;
  this->I = I;
  this->R = R;
}
}  // namespace model
