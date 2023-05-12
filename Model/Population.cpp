#include "Population.hpp"

namespace Model {
// S dentro graffa è quella fornita nella creazione
// S fuori è attributo
Model::Population::Population(int S, int I, int R) : S{S}, I{I}, R{R} {}
int Model::Population::getS() { return S; }
int Model::Population::getI() { return I; }
int Model::Population::getR() { return R; }
int Model::Population::getN() { return S + I + R; }
}  // namespace Model