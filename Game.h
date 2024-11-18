#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "Card.h"
#include "Player.h"

class Game {
 private:
  std::vector<Player*> players;
  std::vector<std::string> suits;
  std::vector<std::string> ranks;
  std::vector<Card*> deck;
  std::vector<Card*> drawPile;
  std::vector<Card*> discardPile;

 public:
  Game();
  void loadDeckFromFile(std::string filename);
  bool doesContain(const std::vector<std::string>& list, const std::string& item);
  void addPlayer(bool isAI);
  void drawCard(Player* p);
  Card* deal(int numCards);
  std::string mostPlayedSuit();
  int runGame();
  ~Game();
};

#endif
