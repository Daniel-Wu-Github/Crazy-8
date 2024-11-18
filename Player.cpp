#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>


#include "Player.h"

using std::vector, std::string, std::size_t, std::cin, std::cout, std::endl;

Player::Player(bool isAI) /* TODO: initialize */ : isAI(isAI), hand({}) {
  this->isAI = isAI;
  this->hand = {};
}

void Player::addToHand(Card* c) {
  // TODO: Add the card c to the player's hand
  hand.push_back(c);
}

size_t Player::getHandSize() {
  // TODO: Implement getter
  return hand.size();
}

std::string Player::getHandString() {
  // TODO: Implement getter
  std::string handString;
  for (int i = 0; i < hand.size(); i++){
    handString += hand[i]->getRank() + " " + hand[i]->getSuit();
    if(i != hand.size() - 1){
      handString += ", ";
    }
  }
  return handString;
}


Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit) {
  // TODO: Choose a card to play and return the chosen card
  if(!isAI){
  cout << "Your hand contains: " << getHandString() << endl;
  cout << "The next card played must be a " << currentRank << " or " << currentSuit << endl;
  cout << "What would you like to play? (enter \"draw card\" to draw a card)" << endl;
  string inputRank;
  string inputSuit;
  while (true) {
    bool skip = false;
    cin >> inputRank;
    cin >> inputSuit;
    
    if (inputRank == "draw" && inputSuit == "card") {
      return nullptr;
    }
    for (int i = 0; i < hand.size(); i++) {
      if ((hand[i]->getRank() == inputRank && hand[i]->getSuit() == inputSuit)) {
        Card* selectedCard = hand[i];
        if (!selectedCard->canBePlayed(currentRank, currentSuit)) {
          cout << "You can't play that card. Try again." << endl;
          skip = true;
          break;
        }
        hand.erase(hand.begin() + i);
        selectedCard->play();
        
        if (selectedCard->getRank() == "8") {
          cout << "What suit would you like to declare?" << endl;
          string declaredSuit;
          while (true) {
            cin >> declaredSuit;
            bool isValidSuit = false;
            for (const auto& suit : suits) {
              if (suit == declaredSuit) {
                isValidSuit = true;
                break;
              }
            }
            if (isValidSuit) {
              currentSuit = declaredSuit;
              currentRank = selectedCard->getRank();
              return selectedCard;
            } 
            else{
              cout << "That's not a suit in this deck. Try again." << endl;
            }
          }
        }
        else{
          currentRank = selectedCard->getRank();
          currentSuit = selectedCard->getSuit();
        }
        return selectedCard;
      }
    }
    if(!skip){
    cout << "That's not a card you have. Try again." << endl;
    }
  }
  }
  //AI
  else{
    for(int i = 0; i < hand.size(); i++){
      if(hand[i]->canBePlayed(currentRank, currentSuit)){
        Card* selectedCard = hand[i];
        hand.erase(hand.begin()+i);
        selectedCard->play();
        currentRank = selectedCard->getRank();
        currentSuit = selectedCard->getSuit();
        return selectedCard;
      }
    }
    return nullptr;
  }
}