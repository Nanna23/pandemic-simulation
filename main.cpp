/**
 * Per compilare
 * g++ -std=c++2a -Wall -Wextra -fsanitize=address,undefined main.cpp
Model/*.cpp View/*.cpp Controller/*.cpp -o app Per eseguire
 * ./app
 */

#include "View/ConsoleInterface.cpp"

int main(int argc, char const *argv[]) {
  View::ConsoleInterface consoleInterface{};
  consoleInterface.start();
  // argc contiene quante parole/numeri sono stati scritti
  // dopo ./app quando il programma è stato fatto partire
  // se argc non è 0 quindi ci stanno degli argomenti passati a linea di comando
  // quindi va fatta partire la interface con i dati passati dentro
  return 0;
}
