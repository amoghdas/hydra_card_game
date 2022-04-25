#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include "cardpile.h"

class Player {
	CardPile drawPile;
	CardPile discardPile;
	string reserve;
	
	public:
	bool reserveExists = false;

	void initDrawPile(const vector<string> &pile); // initializes drawPile using pile	
	string getTopOfDrawPile();
	void removeTopOfDrawPile();
	int getNumCardsInDrawPile();
	int getNumCardsInDiscardPile();
	void shuffleDiscardIntoDraw();
	void placeOnTopOfDrawPile(const string &card);
	void placeOnTopOfDiscardPile(const string &card);
	string getReserve();
	void setReserve(const string &card);
};

#endif
