#ifndef POPULATION_HPP
#define POPULATION_HPP
namespace Model {
class Population {
  int S;
  int I;
  int R;

 public:
  // costrutture setta i valori iniziali di S I R
  Population(int S, int I, int R);
  int getS();
  int getI();
  int getR();
  int getN();
  void update(int S, int I, int R);
};
}  // namespace Model
#endif