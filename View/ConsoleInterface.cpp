#include <iostream>
#include <iomanip>
#include <cstdio>

#include "../Controller/simulation.cpp"

#define SEPARATOR "------------------------------------------"

namespace View {
class ConsoleInterface {
 public:
  ConsoleInterface() {}
  void setupAndStart() {
    int S, I, R, t;
    float beta, gamma;

    FILE *file = std::fopen("simulation.conf", "r");
    if (file != NULL) {
      std::string answer;
      std::cout << "A configuration file was found in the root directory of the program, do you want to use it? [Y/n] ";
      std::cin >> answer;
      if (answer == "y" || answer == "yes" || answer == "Y" || answer == "Yes") {
        if (6 == std::fscanf(file, "%d %d %d %f %f %d", &S, &I, &R, &beta, &gamma, &t)) {
          std::fclose(file);
          start(S, I, R, beta, gamma, t);
          return;
        } else {
          std::cout << "The configuration file is wrongly formatted!";
        }
      }
      std::fclose(file);
    }

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
    std::string answer;
    std::cout << "Do you want a graphic representation of the simulation? [Y/n] ";
    std::cin >> answer;

    // TODO: se answer == Y or answer == YES allora grafico con SFML
    std::cout << SEPARATOR << "\n";
    std::cout << "| " << "Stage count" << " | " <<
        std::setw(4) << "S" << std::setw(5) << " | " <<
        std::setw(4) << "I" << std::setw(5) << " | " <<
        std::setw(4) << "R" << std::setw(5) << " |\n";
    std::cout << SEPARATOR << "\n";
    for (int i = 0; i < t; i++) {
      simulation.advanceStage();
      std::cout << "| " << std::setw(6) << simulation.getStageCount() << std::setw(7) << " | " <<
        std::setw(4) << simulation.getPopulation().getS() << std::setw(5) << " | " <<
        std::setw(4) << simulation.getPopulation().getI() << std::setw(5) << " | " <<
        std::setw(4) << simulation.getPopulation().getR() << std::setw(5) << " |\n";
      std::cout << SEPARATOR << "\n";
    }
  }
};
}  // namespace View