#ifndef PERSON_HPP
#define PERSON_HPP
#include "position.hpp"

namespace model {
  // codificati come 0, 1 e 2
enum PersonState { SUSCETIBLE, INFECTED, REMOVED };
class Person {
  Position position;
  PersonState state;

 public:
  Person();
  void setPosition(Position position);
  void evolveState();
  PersonState getState();

};
}  // namespace model
#endif