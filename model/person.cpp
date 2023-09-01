#include "person.hpp"

namespace model {
// si inizializza position con coordinate (-1, -1) in quanto
// ritenute non valide visto che non è presente la parte dell'automa
model::Person::Person() : position(-1, -1), state{SUSCEPTIBLE} {}
void model::Person::setPosition(Position position) {
  this->position = position;
}
void model::Person::evolveState() {
  if (state == SUSCEPTIBLE) {
    state = INFECTED;
  } else if (state == INFECTED) {
    state = REMOVED;
  }
}
PersonState model::Person::getState() { return this->state; }
}  // namespace model
