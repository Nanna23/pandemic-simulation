#include "population.hpp"

#include <iostream>

namespace model {
// S dentro graffa è quella fornita nella creazione
// S fuori è attributo
model::Population::Population(int S, int I, int R) : S{S}, I{I}, R{R} {
  for (int i = 0; i < S; i++) {
    // model::Person{} mi da direttamente la persona dunque non mi interessa
    // nominarla
    this->people.push_back(model::Person{});
  }
  for (int i = 0; i < I; i++) {
    // nomino la veriabile perché mi servono le funzioni di questa
    Person person{};
    // evolve perché nascono sane
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
  // inserirsco il -1 perché vettore parte da zero
  //  in questo modo il vettore rimane "sezionato"
  //  in zone in cui la prima è S poi I poi R
  for (int i = this->S - 1; i > this->S - difS - 1; i--) {
    this->people[i].evolveState();
  }
  for (int i = this->S + this->I - 1; i > this->S + this->I - difR - 1; i--) {
    this->people[i].evolveState();
  }
  // this->S rappresenta il valore della popolazione
  //  = S è il valore dato ad update
  this->S = S;
  this->I = I;
  this->R = R;
  // devo aggiornare le persone
  // calcolo differenza tra i valori e chi è cambiato faccio aggiornamento
}
}  // namespace model
