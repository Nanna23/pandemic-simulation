#ifndef PERSON_HPP
#define PERSON_HPP
#include "position.hpp"

namespace model {
enum PersonState { SUSCETIBLE, INFECTED, REMOVED };
class Person {
  Position position;
  PersonState state;

 public:
  Person();
  void setPosition(Position position);
  void evolveState();
};
}  // namespace model
#endif