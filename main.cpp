#include <cstdlib>
#include <string>

#include "view/consoleInterface.hpp"

int main(int argc, char const *argv[]) {
  view::ConsoleInterface consoleInterface{};
  if (argc == 1 + 6) {
    const int S = atoi(argv[1]);
    const int I = atoi(argv[2]);
    const int R = atoi(argv[3]);
    const double beta = std::stof(argv[4]);
    const double gamma = std::stof(argv[5]);
    const int t = atoi(argv[6]);
    consoleInterface.start(S, I, R, beta, gamma, t);
  } else {
    consoleInterface.setupAndStart();
  }
  return 0;
}
