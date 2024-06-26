#ifndef CONSOLEINTERFACE_HPP
#define CONSOLEINTERFACE_HPP

namespace view {
class ConsoleInterface {
 public:
  ConsoleInterface() {}
  void start(int S, int I, int R, double beta, double gamma, int t);
  void setupAndStart();
};
}  // namespace view
#endif