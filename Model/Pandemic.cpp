#include <iostream>
#include "Pandemic.hpp"
#include "Population.hpp"

namespace Model {
Model::Pandemic::Pandemic(double beta, double gamma)
    : beta{beta}, gamma{gamma} {}
//per usare stesso population ma cambiare i valori dentro uso i puntatori
void Model::Pandemic::calculateNextStage(Population* populationPointer) {
  Population population = *populationPointer;
  int S = population.getS();
  int I = population.getI();
  int R = population.getR();
  int N = population.getN();
  int newS = S - beta * (S * I) / N;
  int newI = I + beta * (S * I) / N - gamma * I;
  int newR = R + gamma * I;
  //dall'indirizzo di casa ottengo la casa presente lì
  //e la sostituisco con una nuova casa con i dati aggiornati
  //sostitusco la population a quel indirizzo con una aggiornata prendendo
  //da un altro indirizzo la population nuova
  //new model::Population mi da il pointer
  (*populationPointer) = *(new Model::Population(newS, newI, newR));
}
}  // namespace Model
