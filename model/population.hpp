#ifndef POPULATION_HPP
#define POPULATION_HPP
#include <vector>

#include "person.hpp"

namespace model {
class Population {
  std::vector<Person> people;
  int S;
  int I;
  int R;

 public:
  Population(int S, int I, int R);
  int getS();
  int getI();
  int getR();
  int getN();
  void update(int S, int I, int R);
};
}  // namespace model
#endif
