#ifndef POPULATION_HPP
#define POPULATION_HPP

namespace model {
class Population {
  int S;
  int I;
  int R;
  int N;

 public:
  Population(int S, int I, int R);
  int getS();
  int getI();
  int getR();
  int getN();
  bool update(int S, int I, int R);
};
}  // namespace model
#endif
