#ifndef PERSON_HPP
#define PERSON_HPP
#include "PersonState.hpp"
#include "Position.hpp"

namespace Model {
class Person {
  Position position;
  PersonState state;

 public:
  Person();
  void setPosition(Position position);
  void evolveState();
};
}  // namespace Model
#endif