#include <iostream>

#include "../Controller/Simulation.cpp"

namespace View {
class ConsoleInterface {
 public:
  ConsoleInterface() {}
  void start() {
    int S, I, R;
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
    Controller::Simulation simulation{S, I, R, beta, gamma};
    std::cout << "Simulation successfully created!\n";
    int t;
    std::cout << "Insert number of stages to calculate: ";
    std::cin >> t;
    for (int i = 0; i < t; i++)
    {
        simulation.advanceStage();
        std::cout << simulation.getCurrentStateInfo() << ".\n";      
    }

    // prende input dall'utente per cambiare gli stage o chiudere il programma
    // gestisce anche la creazione di grafici o cose così
  }
  void stop() {}

  // DOPO
  // fare un costruttore vuoto e uno con i dati in input
  // (nel caso vengano passati da linea di comando tramite il main)
};
}  // namespace View