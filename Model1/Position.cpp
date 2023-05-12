#include "Position.hpp"

namespace Model {
// per inizializzare i campi privati della classe (attributi) utilizzando le
// informazioni fornite alla funzione costruttore utilizzo : x{x}, y{y}
Model::Position::Position(int x, int y) : x{x}, y{y} {}
int Model::Position::getX() { return x; }
int Model::Position::getY() { return y; }
void Model::Position::setX(int x) { this->x = x; }
void Model::Position::setY(int y) { this->y = y; }
}  // namespace Model