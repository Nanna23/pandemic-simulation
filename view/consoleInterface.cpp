#include <SFML/Graphics.hpp>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "../controller/simulation.cpp"

#define LINE_SEPARATOR " ------------------------------------------"
#define SEPARATOR " | "

namespace view {
class ConsoleInterface {
 public:
  ConsoleInterface() {}
  void setupAndStart() {
    int S, I, R, t;
    float beta, gamma;

    FILE *file = std::fopen("simulation.conf", "r");
    if (file != NULL) {
      std::string answer;
      std::cout << "A configuration file was found in the root directory of "
                   "the program, do you want to use it? [y/n] ";
      std::cin >> answer;
      if (answer == "y" || answer == "yes" || answer == "Y" ||
          answer == "Yes") {
        if (6 == std::fscanf(file, "%d %d %d %f %f %d", &S, &I, &R, &beta,
                             &gamma, &t)) {
          std::fclose(file);
          start(S, I, R, beta, gamma, t);
          return;
        } else {
          std::cout << "The configuration file is wrongly formatted!" << std::endl;
        }
      }
      std::fclose(file);
    }

    std::cout << "Insert initial susceptibles: ";
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
    controller::Simulation* simulation;
    try {
      simulation = new controller::Simulation(S, I, R, beta, gamma, t);
    } catch (const std::invalid_argument& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      exit(1);
    }
    std::cout << "Simulation successfully created!" << std::endl;
    std::string answer;
    std::cout
        << "Do you want a graphic representation of the simulation? [y/n] ";
    std::cin >> answer;

    std::vector<int> s_values{};
    std::vector<int> i_values{};
    std::vector<int> r_values{};

    std::cout << LINE_SEPARATOR << std::endl;
    std::cout << SEPARATOR << "Stage count"
              << SEPARATOR << std::setw(4) << "S" << std::setw(5)
              << SEPARATOR << std::setw(4) << "I" << std::setw(5) 
              << SEPARATOR << std::setw(4) << "R" << std::setw(5)
              << SEPARATOR << std::endl;
    std::cout << LINE_SEPARATOR << std::endl;
    do {
      s_values.push_back(simulation->getPopulation().getS());
      i_values.push_back(simulation->getPopulation().getI());
      r_values.push_back(simulation->getPopulation().getR());
      std::cout << SEPARATOR << std::setw(6) << simulation->getStageCount() << std::setw(8)
                << SEPARATOR << std::setw(4) << s_values.back() << std::setw(5)
                << SEPARATOR << std::setw(4) << i_values.back() << std::setw(5)
                << SEPARATOR << std::setw(4) << r_values.back() << std::setw(5)
                << SEPARATOR << std::endl;
      std::cout << LINE_SEPARATOR << std::endl;
    } while (simulation->advanceStage());

    if (answer == "y" || answer == "yes" || answer == "Y" || answer == "Yes") {
      unsigned int window_width{1000};
      unsigned int window_height{800};
      unsigned int padding{50};
      sf::RenderWindow window(sf::VideoMode(window_width, window_height),
                              "Pandemic Simulation");

      std::vector<sf::Vertex> axis{
          sf::Vertex(sf::Vector2f(padding, padding), sf::Color::Black),
          sf::Vertex(sf::Vector2f(padding, window_height - padding),
                     sf::Color::Black),
          sf::Vertex(
              sf::Vector2f(window_width - padding, window_height - padding),
              sf::Color::Black)};

      std::vector<int> max_values{
          *std::max_element(s_values.begin(), s_values.end()),
          *std::max_element(i_values.begin(), i_values.end()),
          *std::max_element(r_values.begin(), r_values.end())};
      const int max_value = *std::max_element(max_values.begin(), max_values.end());

      const float xpadding = (window_width - 2 * padding) * 1.f / t;

      std::vector<sf::Vertex> line_graph_s;
      std::vector<sf::Vertex> line_graph_i;
      std::vector<sf::Vertex> line_graph_r;
      for (int i = 0; i <= t; i++) {
        line_graph_s.emplace_back(
            sf::Vector2f(padding + i * xpadding,
                         window_height - padding -
                             (s_values[i] * 1.f / max_value) *
                                 (window_height - 2 * padding)),
            sf::Color::Green);
        line_graph_i.emplace_back(
            sf::Vector2f(padding + i * xpadding,
                         window_height - padding -
                             (i_values[i] * 1.f / max_value) *
                                 (window_height - 2 * padding)),
            sf::Color{220, 140, 0, 255});
        line_graph_r.emplace_back(
            sf::Vector2f(padding + i * xpadding,
                         window_height - padding -
                             (r_values[i] * 1.f / max_value) *
                                 (window_height - 2 * padding)),
            sf::Color::Red);
      }

      window.clear(sf::Color::White);
      window.draw(line_graph_s.data(), line_graph_s.size(),
                  sf::PrimitiveType::LineStrip);
      window.draw(line_graph_i.data(), line_graph_i.size(),
                  sf::PrimitiveType::LineStrip);
      window.draw(line_graph_r.data(), line_graph_r.size(),
                  sf::PrimitiveType::LineStrip);
      window.draw(axis.data(), axis.size(), sf::PrimitiveType::LineStrip);
      // label con nome degli assi
      sf::Text xlabel;
      sf::Text ylabel;
      sf::Font font;
      font.loadFromFile("arial.ttf");
      xlabel.setString("Time [days]");
      xlabel.setFont(font);
      xlabel.setCharacterSize(padding / 2);
      xlabel.setFillColor(sf::Color::Black);
      xlabel.setPosition(window_width / 2.f, window_height - padding);
      window.draw(xlabel);
      ylabel.setString("People");
      ylabel.setFont(font);
      ylabel.setCharacterSize(padding / 2);
      ylabel.setFillColor(sf::Color::Black);
      ylabel.setPosition(padding / 4.f, window_height / 2.f);
      ylabel.rotate(270.f);
      window.draw(ylabel);
      // legenda
      sf::RectangleShape square(sf::Vector2f(155.0f, 95.0f));
      square.setFillColor(sf::Color::Transparent);
      square.setOutlineColor(sf::Color::Black);
      square.setOutlineThickness(1);
      square.setPosition(800, padding);
      window.draw(square);
      sf::Text removedLine;
      removedLine.setString("Removed");
      removedLine.setFont(font);
      removedLine.setCharacterSize(padding / 2);
      removedLine.setFillColor(sf::Color::Red);
      removedLine.setPosition(805, padding + 5);
      window.draw(removedLine);
      sf::Text susceptiblesLine;
      susceptiblesLine.setString("Susceptibles");
      susceptiblesLine.setFont(font);
      susceptiblesLine.setCharacterSize(padding / 2);
      susceptiblesLine.setFillColor(sf::Color::Green);
      susceptiblesLine.setPosition(805, padding + 30);
      window.draw(susceptiblesLine);
      sf::Text infectedLine;
      infectedLine.setString("Infected");
      infectedLine.setFont(font);
      infectedLine.setCharacterSize(padding / 2);
      infectedLine.setFillColor(sf::Color{220, 140, 0, 255});
      infectedLine.setPosition(805, padding + 60);
      window.draw(infectedLine);
      window.display();

      while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed) {
            window.close();
          }
        }
      }
    }
  }
};
}  // namespace view
