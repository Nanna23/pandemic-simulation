/**
 * Per compilare
 * g++ -std=c++2a -Wall -Wextra -fsanitize=address,undefined main.cpp
 * model/*.cpp view/*.cpp controller/*.cpp -o app Per eseguire
 * ./app
 * 
 * per compilare con CMake:
 * cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
 * cmake --build build
 * per farlo partire:
 * ./build/app
 */

#include "View/consoleInterface.cpp"

int main(int argc, char const *argv[]) {
  // array di puntatori a caratteri
  // int arcgc mi indica quanti puntatori ho
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
  // argc contiene quante parole/numeri sono stati scritti
  // dopo ./app quando il programma è stato fatto partire
  // se argc non è 0 quindi ci stanno degli argomenti passati a linea di
  // comando quindi va fatta partire la interface con i dati passati
  // dentro
  return 0;
}
