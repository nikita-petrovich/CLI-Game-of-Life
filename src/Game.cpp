#include "../include/Game.hpp"
#include "../include/Random.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>

Window::Window(std::size_t width, std::size_t height)
    : m_width{width}, m_height{height} {}

Game::Game(Window window)
    : m_window{window}, m_frameA(m_window.getWidth() * m_window.getHeigth()),
      m_frameB(m_frameA.size()) {
  std::generate(m_frameA.begin(), m_frameA.end(), []() {
    int i{Random::get(0, 3)};
    if (i == 0)
      return "⬜️";
    else
      return "⬛️";
  });
}

void Game::printFrame(bool frame) const {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpedantic"
  // Clean terminal window
  std::system("printf '\33c\e[3J'");
#pragma clang diagnostic pop

  for (std::size_t i{0}; i < m_window.getWidth() * m_window.getHeigth(); ++i) {
    if (i % (m_window.getWidth()) == 0 && i > 0)
      std::cout << '\n';

    frame ? std::cout << m_frameB[i] : std::cout << m_frameA[i];
  }
  std::cout << std::endl;
}

void Game::updateFrame(int currentFrame) {
  currentFrame ? compareFrames(m_frameB, m_frameA)
               : compareFrames(m_frameA, m_frameB);
}

void Game::compareFrames(std::vector<std::string> &currentFrame,
                         std::vector<std::string> &nextFrame) {
  std::size_t x{};
  std::size_t y{};

  for (y = 0; y < m_window.getHeigth(); ++y) {
    for (x = 0; x < m_window.getWidth(); ++x) {
      int neighbourPixels = countNeighbours(x, y, currentFrame);

      std::size_t index = x + y * m_window.getWidth();

      if (neighbourPixels == 3 && currentFrame[index] == "⬛️") {
        nextFrame[index] = "⬜️";
      } else if ((neighbourPixels == 3 || neighbourPixels == 2) &&
                 currentFrame[index] == "⬜️") {
        nextFrame[index] = "⬜️";
      } else {
        nextFrame[index] = "⬛️";
      }
    }
  }
}

int Game::countNeighbours(const std::size_t x, const std::size_t y,
                          std::vector<std::string> &currentFrame) {
  int count{0};
  std::size_t x_minus{};
  std::size_t y_minus{};
  std::size_t x_plus{};
  std::size_t y_plus{};

  x == 0 ? x_minus = m_window.getWidth() - 1 : x_minus = x - 1;
  y == 0 ? y_minus = m_window.getHeigth() - 1 : y_minus = y - 1;

  x == m_window.getWidth() - 1 ? x_plus = 0 : x_plus = x + 1;
  y == m_window.getHeigth() - 1 ? y_plus = 0 : y_plus = y + 1;

  std::size_t width = m_window.getWidth();
  currentFrame[x_minus + y_minus * width] == "⬜️" ? ++count : count; // [-1, -1]
  currentFrame[x + y_minus * width] == "⬜️" ? ++count : count;       // [0, -1]
  currentFrame[x_plus + y_minus * width] == "⬜️" ? ++count : count;  // [+1, -1]

  currentFrame[x_minus + y * width] == "⬜️" ? ++count : count; // [-1, 0]
  currentFrame[x_plus + y * width] == "⬜️" ? ++count : count;  // [+1, 0]

  currentFrame[x_minus + y_plus * width] == "⬜️" ? ++count : count; // [-1, +1]
  currentFrame[x + y_plus * width] == "⬜️" ? ++count : count;       // [0, +1]
  currentFrame[x_plus + y_plus * width] == "⬜️" ? ++count : count;  // [+1, +1]

  return count;
}

void Game::mainLoop() {
  bool currentFrame{0};
  do {
    printFrame(currentFrame);
    std::cout << "Generations passed: " << ++m_generationsCount << std::endl;
    updateFrame(currentFrame);
    currentFrame = !currentFrame;
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  } while (m_frameA != m_frameB);
}
