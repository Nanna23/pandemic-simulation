#include "population.hpp"

#include <iostream>

namespace model {
// S dentro graffa è quella fornita nella creazione, quella fuori è attributo
model::Population::Population(int S, int I, int R) : S{S}, I{I}, R{R} {
  for (int i = 0; i < S; i++) {
    this->people.push_back(model::Person{});
  }
  for (int i = 0; i < I; i++) {
    Person person{};
    // va fatta evolvere la persona perché viene creata suscettibile
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
int model::Population::getN() { return S + I + R; }
void model::Population::update(int S, int I, int R) {
  if (S + I + R != this->getN()) {
    return;
  }

  // rappresenta le persone di cui devo fare l'update
  int difS = this->S - S;
  int difR = R - this->R;
  // è presente il -1 perché gli indici dei vettori partono
  // da zero, in questo modo il vettore rimane "sezionato"
  // in zone S, I ed R
  for (int i = this->S - 1; i > this->S - difS - 1; i--) {
    this->people[i].evolveState();
  }
  for (int i = this->S + this->I - 1; i > this->S + this->I - difR - 1; i--) {
    this->people[i].evolveState();
  }
  this->S = S;
  this->I = I;
  this->R = R;
}
}  // namespace model
