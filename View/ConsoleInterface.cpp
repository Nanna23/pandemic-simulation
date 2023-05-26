#include <iostream>

#include "../Controller/simulation.cpp"

namespace View {
class ConsoleInterface {
 public:
  ConsoleInterface() {}
  void setupAndStart() {
    int S, I, R, t;
    float beta, gamma;
    std::cout << "Insert initial suscetibles: ";
    std::cin >> S;
    std::cout << "Insert initial infected: ";
    std::cin >> I;
    std::cout << "Insert initial removed: ";
    std::cin >> R;
    std::cout << "Insert parameter beta: ";
    std::cin >> beta;
    std::cout << "Insert parameter gamma: ";
    std::cin >> gamma;
    std::cout << "Insert number of stages to calculate: ";
    std::cin >> t;
    start(S, I, R, beta, gamma, t);
  }
  void start(int S, int I, int R, float beta, float gamma, int t) {
    Controller::Simulation simulation{S, I, R, beta, gamma};
    std::cout << "Simulation successfully created!\n";
    for (int i = 0; i < t; i++) {
      simulation.advanceStage();
      std::cout << simulation.getCurrentStateInfo() << ".\n";
    }
  }
    void stop() {}

    // DOPO
    // fare una funzione start con i dati come argomento e t
    // (nel caso vengano passati da doctest o da
    // linea di comando tramite il main (./app 10 2 0 0.5 0.5 6))
  };
}  // namespace View