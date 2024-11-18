#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Card.h"

class Player {
 private:
  bool isAI;
  std::vector<Card*> hand;

 public:
  Player(bool isAI);
  void addToHand(Card* c);
  std::size_t getHandSize();
  std::string getHandString();
  Card* isInHand(std::string rankInput, std::string suitInput);
  Card* playCard(std::vector<std::string> const& suits, std::string& currentRank, std::string& currentSuit);
};

#endif