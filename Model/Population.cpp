#include "population.hpp"

#include <iostream>

namespace model {
// S dentro graffa è quella fornita nella creazione
// S fuori è attributo
model::Population::Population(int S, int I, int R) : S{S}, I{I}, R{R} {
  for (int i = 0; i < S; i++) {
    this->people.push_back(model::Person{});
  }
  for (int i = 0; i < I; i++) {
    Person person{};
    person.evolveState();
    this->people.push_back(person);
  }
  for (int i = 0; i < R; i++) {
    Person person{};
    person.evolveState();
    person.evolveState();
    this->people.push_back(person);
  }
}
int model::Population::getS() { return S; }
int model::Population::getI() { return I; }
int model::Population::getR() { return R; }
int model::Population::getN() { return this->people.size(); }
void model::Population::update(int S, int I, int R) {
  this->S = S;
  this->I = I;
  this->R = R;
  //devo aggiornare le persone
  //calcolo differenza tra i valori e chi è cambiato faccio aggiornamento
}
}  // namespace model