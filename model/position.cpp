#include "position.hpp"

namespace model {
model::Position::Position(int x, int y) : x{x}, y{y} {}
int model::Position::getX() { return x; }
int model::Position::getY() { return y; }
void model::Position::setX(int x) { this->x = x; }
void model::Position::setY(int y) { this->y = y; }
}  // namespace model
