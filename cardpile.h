#ifndef _CARDPILE_H_
#define _CARDPILE_H_
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class CardPile {
	vector<string> pile;

	public:
	void initPile(const vector<string> &tempPile); // initializes pile to be a copy of tempPile
	int getTopCardValue();
	string getTopCard(); // Returns the string representing the top card of pile
	void placeOnTop(const string &card);
	void removeTopCard(); 
	int getNumCards();
	void shuffle();
};

#endif
