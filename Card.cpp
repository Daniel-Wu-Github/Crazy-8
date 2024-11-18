#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>


#include "Card.h"

using std::string, std::vector, std::size_t, std::cin, std::cout, std::endl;

Card::Card(string rank, string suit) /* TODO: initialize */ : rank(rank), suit(suit), timesPlayed(0){
  // TODO: implement constructor checks
  if(rank == "" || suit == ""){
    throw std::invalid_argument("Rank and suit must not be empty");
  }
  for (char c : rank) {
    if (!isalnum(c)) {
      throw std::invalid_argument("Rank contains non-alphanumeric characters");
    }
  }
  for (char c : suit) {
    if (!isalnum(c)) {
      throw std::invalid_argument("Suit contains non-alphanumeric characters");
    }
  }

}

string Card::getRank() {
  // TODO: implement getter
  return rank;
}

string Card::getSuit() {
  // TODO: implement getter
  return suit;
}

int Card::getTimesPlayed() {
  // TODO: implement getter
  return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit) {
  // TODO: return whether or not the card can legally be played
  if(rank == "8"){
    return true;
  }
  if(rank == currentRank || suit == currentSuit){
    return true;
  }
  else{
    return false;
  }
}

void Card::play() {
  timesPlayed++;
}
