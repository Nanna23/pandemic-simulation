#include "person.hpp"

namespace model {
// new Position(-1, -1) è un puntatore alla position (-1, -1)
// inizializzo position
model::Person::Person() : position(-1, -1), state{SUSCEPTIBLE} {}
// per impostare la posizione di un oggetto di tipo Person (istanza)
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
PersonState model::Person::getState() {
  return this->state;
}
}  // namespace model