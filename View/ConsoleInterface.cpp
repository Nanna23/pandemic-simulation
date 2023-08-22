#include <SFML/Graphics.hpp>
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
    int window_height{1000};
    int window_width{800};
    int padding{50};
    sf::RenderWindow window(sf::VideoMode(window_height, window_width), "Simulation");

    std::vector<sf::Vertex> border {
      sf::Vertex(sf::Vector2f(padding, padding), sf::Color::Black),
      sf::Vertex(sf::Vector2f(padding, window_width - padding), sf::Color::Black),
      sf::Vertex(sf::Vector2f(window_height - padding, window_width - padding), sf::Color::Black)
    };

    std::vector<sf::Vertex> line_graph_s;
    std::vector<sf::Vertex> line_graph_i;
    std::vector<sf::Vertex> line_graph_r;

    std::vector<int> s_values{};
    std::vector<int> i_values{};
    std::vector<int> r_values{};

    std::cout << SEPARATOR << "\n";
    std::cout << "| " << "Stage count" << " | " <<
        std::setw(4) << "S" << std::setw(5) << " | " <<
        std::setw(4) << "I" << std::setw(5) << " | " <<
        std::setw(4) << "R" << std::setw(5) << " |\n";
    std::cout << SEPARATOR << "\n";
    for (int i = 0; i < t; i++) {
      simulation.advanceStage();
      std::cout << "| " << std::setw(6) << simulation.getStageCount() << std::setw(8) << " | " <<
        std::setw(4) << simulation.getPopulation().getS() << std::setw(5) << " | " <<
        std::setw(4) << simulation.getPopulation().getI() << std::setw(5) << " | " <<
        std::setw(4) << simulation.getPopulation().getR() << std::setw(5) << " |\n";
      s_values.push_back(simulation.getPopulation().getS());
      i_values.push_back(simulation.getPopulation().getI());
      r_values.push_back(simulation.getPopulation().getR());
      std::cout << SEPARATOR << "\n";
    }

    if (answer == "y" || answer == "yes" || answer == "Y" || answer == "Yes") {
      std::vector<int> max_values {
        *std::max_element(s_values.begin(), s_values.end()),
        *std::max_element(i_values.begin(), i_values.end()),
        *std::max_element(r_values.begin(), r_values.end())
      };
      int max_value = *std::max_element(max_values.begin(), max_values.end());
  
      int xpadding = (window_width - 2 * padding) / t;
      
      for (int i = 0; i < t; i++)
      {
        line_graph_s.emplace_back(sf::Vector2f(padding + i * xpadding, window_height - padding - (s_values[i] * 1.f / max_value) * (window_height - 2 * padding)), sf::Color::Green);
        line_graph_i.emplace_back(sf::Vector2f(padding + i * xpadding, window_height - padding - (i_values[i] * 1.f / max_value) * (window_height - 2 * padding)), sf::Color::Red);
        line_graph_r.emplace_back(sf::Vector2f(padding + i * xpadding, window_height - padding - (r_values[i] * 1.f / max_value) * (window_height - 2 * padding)), sf::Color::Black);
      }
    
      window.clear(sf::Color::White);
      window.draw(line_graph_s.data(), line_graph_s.size(), sf::PrimitiveType::LineStrip);
      window.draw(line_graph_i.data(), line_graph_i.size(), sf::PrimitiveType::LineStrip);
      window.draw(line_graph_r.data(), line_graph_r.size(), sf::PrimitiveType::LineStrip);
      window.draw(border.data(), border.size(), sf::PrimitiveType::LineStrip);
      window.display();

      while (window.isOpen())
      {
        sf::Event event;
        while (window.pollEvent(event))
        {
          if(event.type == sf::Event::Closed) {
            window.close();
          }
        }
      }
    }
  }
};
}  // namespace View