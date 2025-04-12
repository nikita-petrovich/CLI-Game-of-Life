#ifndef GAME_HPP
#define GAME_HPP

#include <cstdlib>
#include <vector>

class Window {
public:
  Window(){};
  Window(std::size_t width, std::size_t height);
  std::size_t getWidth() const { return m_width / 2; }
  std::size_t getHeigth() const { return m_height - 1; }

private:
  std::size_t m_width{80};
  std::size_t m_height{24};
};

class Game {
public:
  Game() : Game{{}} {};
  Game(Window window);
  void mainLoop();

private:
  void printFrame(bool frame) const;
  void updateFrame(int currentFrame);
  void compareFrames(std::vector<std::string> &currentFrame,
                     std::vector<std::string> &nextFrame);
  int countNeighbours(const std::size_t x, const std::size_t y,
                      std::vector<std::string> &currentFrame);

  Window m_window{};
  std::vector<std::string> m_frameA;
  std::vector<std::string> m_frameB;
  int generationsCount{0};
};

#endif // GAME_HPP
