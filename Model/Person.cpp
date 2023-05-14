#include "Person.hpp"

namespace Model {
// new Position(-1, -1) è un puntatore alla position (-1, -1)
// inizializzo position
Model::Person::Person() : position(-1, -1), state{SUSCETIBLE} {}
// per impostare la posizione di un oggetto di tipo Person (istanza)
void Model::Person::setPosition(Position position) {
  this->position = position;
}
void Model::Person::evolveState() {
  if (state == SUSCETIBLE) {
    state = INFECTED;
  } else if (state == INFECTED) {
    state = REMOVED;
  }
}
}  // namespace Model