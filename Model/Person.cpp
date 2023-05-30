#include "person.hpp"

namespace model {
// new Position(-1, -1) è un puntatore alla position (-1, -1)
// inizializzo position
model::Person::Person() : position(-1, -1), state{SUSCETIBLE} {}
// per impostare la posizione di un oggetto di tipo Person (istanza)
void model::Person::setPosition(Position position) {
  this->position = position;
}
void model::Person::evolveState() {
  if (state == SUSCETIBLE) {
    state = INFECTED;
  } else if (state == INFECTED) {
    state = REMOVED;
  }
}
PersonState model::Person::getState() {
  return this->state;
}
}  // namespace model