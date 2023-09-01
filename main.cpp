#include "view/consoleInterface.cpp"

int main(int argc, char const *argv[]) {
  view::ConsoleInterface consoleInterface{};
  if (argc == 1 + 6) {
    int S = atoi(argv[1]);
    int I = atoi(argv[2]);
    int R = atoi(argv[3]);
    double beta = std::stod(argv[4]);
    double gamma = std::stod(argv[5]);
    int t = atoi(argv[6]);
    consoleInterface.start(S, I, R, beta, gamma, t);
  } else {
    consoleInterface.setupAndStart();
  }
  return 0;
}
