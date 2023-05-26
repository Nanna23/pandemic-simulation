#include "position.hpp"

namespace model {
// per inizializzare i campi privati della classe (attributi) utilizzando le
// informazioni fornite alla funzione costruttore utilizzo : x{x}, y{y}
model::Position::Position(int x, int y) : x{x}, y{y} {}
int model::Position::getX() { return x; }
int model::Position::getY() { return y; }
void model::Position::setX(int x) { this->x = x; }
void model::Position::setY(int y) { this->y = y; }
}  // namespace model