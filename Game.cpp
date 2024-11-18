#include "Game.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <string>

using std::string, std::vector, std::cin, std::cout, std::endl;

Game::Game() : players({}), suits({}), ranks({}), deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename) {
  std::ifstream currentDeck(filename);
  if(!currentDeck.is_open()){
    throw std::invalid_argument("Could not open file");
  }
  string loadSuits; 
  std::getline(currentDeck,loadSuits);
  if (currentDeck.fail()) {
    throw std::runtime_error("Failed to read line");
  }
  std::istringstream iss(loadSuits);
  string temp;
  while(iss >> temp){
    for (unsigned int i = 0; i < temp.size(); i++) {
      if (!isalnum(temp[i])) {
        throw std::runtime_error("Suit contains non-alphanumeric characters");
      }
    }
    if (iss.fail()) {
    break;
    }
    suits.push_back(temp);
  }
  string loadRanks;
  std::getline(currentDeck,loadRanks);
  if (currentDeck.fail()) {
    throw std::runtime_error("Failed to read line");
  }
  iss.str(loadRanks);
  iss.clear();
  while(iss >> temp){
    for (unsigned int i = 0; i < temp.size(); i++) {
      if (!isalnum(temp[i])) {
        throw std::runtime_error("Rank contains non-alphanumeric characters");
      }
    }
    ranks.push_back(temp);
  }
  string currentCard;
  while(std::getline(currentDeck,currentCard)){
    if (currentCard.find(" ") == string::npos) {
      throw std::runtime_error("Invalid line format");
    }
    iss.str(currentCard);
    iss.clear();
    string currentRank = currentCard.substr(0, currentCard.find(" "));
    string currentSuit = currentCard.substr(currentCard.find(" ") + 1);
    bool validRank = doesContain(ranks,currentRank);
    bool validSuit = doesContain(suits,currentSuit);
    if (!validRank || !validSuit) {
      throw std::runtime_error("Invalid rank or suit");
    }
    Card* ccptr = new Card(currentRank,currentSuit);
    deck.push_back(ccptr);
    drawPile.insert(drawPile.begin(),ccptr);
  }
  if (!currentDeck.eof()) {
    throw std::runtime_error("Failed to read file");
  }
}

bool Game::doesContain(const std::vector<std::string>& list, const std::string& item){
  for(int i = 0; i < list.size(); i++){
    if(list[i] == item){
      return true;
    }
  }
  return false;
}

void Game::addPlayer(bool isAI) {
  // TODO: add a new player to the game
  Player* newPlayer = new Player(isAI);
  players.push_back(newPlayer);
}

void Game::drawCard(Player* p) {
  if(drawPile.size() == 0){
    if(discardPile.size() == 0){
      cout << "Draw pile, empty, flipping the discard pile." << endl;
      throw std::runtime_error("No Cards Left!");
    }
    cout << "Draw pile, empty, flipping the discard pile." << endl;
    for(int i = 0; i < discardPile.size(); i++){
      drawPile.insert(drawPile.begin(),discardPile[i]);
    }
    discardPile.clear();
  }
  p->addToHand(drawPile[drawPile.size()-1]);
  drawPile.pop_back();
}

// deals numCards cards to each player
Card* Game::deal(int numCards) {
  // TODO: Flip the top card of the draw pile to be the initial discard
  // then deal numCards many cards to each player
  if(drawPile.size() == 0) {
    throw std::runtime_error("No Cards Left!");
  }
  Card* initialCard = drawPile[drawPile.size()-1];
  drawPile.pop_back();
  discardPile.push_back(initialCard);

  for(int i = 0; i < numCards; i++){
    for(int j = 0; j < players.size(); j++){
      drawCard(players[j]);
    }
  }
  return initialCard;
}

string Game::mostPlayedSuit() {
  // TODO: Return the suit which has been played the most times
  // if there is a tie, choose any of the tied suits
  vector<int> count(suits.size(),0);
  for(int i = 0; i < deck.size(); i++){
    for(int j = 0; j < suits.size(); j++){
      if(deck[i]->getSuit() == suits[j]){
        count[j] += deck[i]->getTimesPlayed();
      }
    }
  }
  int mostPlayed = 0;
  int suitIndex = 0;
  for(int i = 0; i < count.size(); i++){
    if(count[i] > mostPlayed){
      mostPlayed = count[i];
      suitIndex = i;
    }
  }
  return suits[suitIndex];
}

int Game::runGame() {
    string currentRank = deck.front()->getRank();
    string currentSuit = deck.front()->getSuit();
    while(true){
        for(int i = 0; i < players.size(); i++){
            cout << "Player " << i << "'s turn!" << endl;
            Card* selectedCard = players[i]->playCard(suits, currentRank, currentSuit);
            if(selectedCard != nullptr){
                if(selectedCard->getRank() == "8"){
                    cout << "Player " << i << " plays " << selectedCard->getRank() <<" "<< selectedCard->getSuit() << " and changes the suit to " << currentSuit << "." << endl;
                }
                else{
                    cout << "Player " << i << " plays " << selectedCard->getRank() <<" "<< selectedCard->getSuit() << "." << endl;
                }
                discardPile.push_back(selectedCard);
                if(players[i]->getHandSize() == 0){
                    return i;
                }
            }
            else{
                try{
                    drawCard(players[i]);
                    cout << "Player " << i << " draws a card." << endl;
                }
                catch (std::runtime_error& e) {
                    std::cout << "Player " << i << " cannot draw a card." << std::endl;
                    return -1;
                }
            }
            if(players[i]->getHandSize() == 0) {
              return i;
            }
        }
    }
}

// Destructor--Deallocates all the dynamic memory we allocated
Game::~Game() {
  for (unsigned int i = 0; i < deck.size(); i++) {
    delete deck.at(i);
  }
  for (unsigned int i = 0; i < players.size(); i++) {
    delete players.at(i);
  }
}