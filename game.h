#ifndef _GAME_H_
#define _GAME_H_
#include <iostream>
#include <vector>
#include <map>
#include "player.h"
#include "cardpile.h"
#include <algorithm>
#include <random>
#include <utility>

class Game {
 	vector<Player> players;
  	vector<pair<CardPile, bool>> heads;
	// Note: heads[i].second represents whether or not the
	//   (i+1)th head is in the game
	bool testingMode = false;

	int playerWhoWon = -1; // set to -1 as default to indicate there is no winner

	public:
	// setInitState(numPlayers) shuffles numPlayers number of decks and 
	//   distributes them equally among all players. Also sets the first head.
	void setInitState(int numPlayers);
	bool isWon();
	void printWinningMessage();
	int numActiveHeads(); // returns the number of heads currently in the game
	void setTestingMode(bool b);
	// printCurState() prints the current state of the game, i.e., prints
	//   all the heads and all the player information
	void printCurState();

	// printPlayerState(curPlayer, remaining, reserveExists) prints the current state 
	//   of the game and the information about the current player's turn
	void printPlayerState(int curPlayer, int remaining);

	// cardInHand(curPlayer) returns the card that the current player would draw
	//   and removes it from the drawPile (which may involve shuffling the
	//    discardPile into the new drawPile)
	string cardInHand(int curPlayer);
	void cutOffTheHead(int curPlayer, const string &inHand);
	int oldestActiveHead();

	// noOtherValidMove(inHand) determins if actions 1-3 are not valid for any heads
	bool noOtherValidMove(const string &inHand);
	
	// testingPrompt() prints "Card value?" and then receives input. If input is not
	//   "Joker", prints "Suit?" and receives input. Returns the string representing
	//   the input card.
	string testingPrompt();
	void play(int curPlayer); // implements an entire turn of the game
};

#endif
