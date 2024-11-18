#include <iostream>
#include <string>
#include <sstream>

#include "Card.h"
#include "Game.h"
#include "Player.h"

using std::string , std::cout, std::cin, std::endl;

bool loadDeck(Game& g) {
  string filename;
  std::cout << "Choose a file to load the deck from:" << std::endl;
  std::cin >> filename;
  try {
    g.loadDeckFromFile(filename);
  } catch (std::invalid_argument const&) {
    std::cout << "The file was invalid. Aborting." << std::endl;
    return false;
  }
  return true;
}

int getPlayerCount() {
  std::cout << "Enter number of players:" << std::endl;
  int numPlayers;
  while (true) {
    if ((!(std::cin >> numPlayers)) || numPlayers <= 0) {
      if (std::cin.fail()) {
        // Clear the fail flag
        std::cin.clear();
        // Remove the non-integer data from the stream
        string garbage;
        std::cin >> garbage;
      }
      std::cout << "Please enter a positive number" << std::endl;
    } else {
      // break out of the loop once we've read a valid number
      break;
    }
  }
  return numPlayers;
}

void setupPlayers(Game& g, int numPlayers) {
  // TODO: Determine whether each player is a human or an AI
  // and add them to the game
    for(int i = 0; i < numPlayers; i++){
    cout << "Is player " << i << " an AI? (y/n)" << endl;
    string input;
    while (true){
      cin >> input;
      if (input == "y" || input == "n") {
        break;
      }
      cout << "Please enter y or n" << endl;
    }
    if(input == "y"){
      g.addPlayer(true);
    }
    else{
      g.addPlayer(false);
    }
  }
}

void setupGame(Game& g) {
  // TODO: Determine how many cards to deal, deal the cards, and
  // print the initial discard
  cout << "How many cards should each player start with?" << endl;
  int numCards;

  string input;
  while (true){
    getline(cin, input);
    std::stringstream ss(input);
    if (ss >> numCards) {
        string remaining;
        if (!(ss >> remaining) && numCards > 0) {
            break;
        }
    }
    if (numCards <= 0) {
        cout << "Please enter a positive number" << endl;
    }
}

  Card* initialDiscard = g.deal(numCards);
  cout << "The initial discard is " << initialDiscard->getRank() << " " << initialDiscard->getSuit() << endl;
}

int main() {
  Game g;
  if (!loadDeck(g)) {
    return 1;
  }
  int numPlayers = getPlayerCount();
  setupPlayers(g, numPlayers);
  setupGame(g);
  int winner = g.runGame();
  if (winner != -1) {
    std::cout << "Player " << winner << " wins!" << std::endl;
  } else {
    std::cout << "The game is a draw!" << std::endl;
  }
  std::cout << "The most played suit was " << g.mostPlayedSuit() << std::endl;
  return 0;
}