#ifndef POSITION_HPP
#define POSITION_HPP

namespace Model {
class Position {
  int x;
  int y;

 public:
  Position(int x, int y);
  int getX();
  int getY();
  void setX(int x);
  void setY(int y);
};
}  // namespace Model
#endif