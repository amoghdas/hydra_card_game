#include "player.h"

void Player::initDrawPile(const vector<string> &pile) { drawPile.initPile(pile); }

string Player::getTopOfDrawPile() { return drawPile.getTopCard(); }

void Player::removeTopOfDrawPile() { drawPile.removeTopCard(); }

int Player::getNumCardsInDrawPile() { return drawPile.getNumCards(); }

int Player::getNumCardsInDiscardPile() { return discardPile.getNumCards(); }

void Player::shuffleDiscardIntoDraw() {
	// 1. Move contents of discard pile to draw pile
	// 2. Shuffle new draw pile
	
	// Moving contents 
	string temp;
	for (int i = 0; i < discardPile.getNumCards(); i++) {
		temp = discardPile.getTopCard();
		discardPile.removeTopCard();
		drawPile.placeOnTop(temp);
	}

	// Shuffling
	drawPile.shuffle();
}

void Player::placeOnTopOfDrawPile(const string &card) {
	drawPile.placeOnTop(card);
}

void Player::placeOnTopOfDiscardPile(const string &card) {
	discardPile.placeOnTop(card);
}

string Player::getReserve() { return reserve; }

void Player::setReserve(const string &card) { reserve = card; }

