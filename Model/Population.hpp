#ifndef POPULATION_HPP
#define POPULATION_HPP
namespace Model {
class Population {
  int S;
  int I;
  int R;

 public:
  Population(int S, int I, int R);
  int getS();
  int getI();
  int getR();
  int getN();
};
}  // namespace Model
#endif