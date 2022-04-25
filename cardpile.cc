#include "cardpile.h"

void CardPile::initPile(const vector<string> &tempPile) { pile = tempPile; }

int CardPile::getTopCardValue() {
	if (pile.size() == 0) return -1;

	string card = pile[pile.size() - 1];
	if (card.size() == 3) return 10;

	if (card[0] == 'A') return 1;
	else if (card[0] == 'J') return 11;
	else if (card[0] == 'Q') return 12;
	else if (card[0] == 'K') return 13;
	else return card[0] - '0';	
}

string CardPile::getTopCard() { return pile[pile.size() - 1]; }

void CardPile::placeOnTop(const string &card) { pile.push_back(card); }

void CardPile::removeTopCard() { pile.pop_back(); }

int CardPile::getNumCards() {return pile.size(); }

void CardPile::shuffle() {
   srand(time(0));	
	random_shuffle(pile.begin(), pile.end()); 
}
