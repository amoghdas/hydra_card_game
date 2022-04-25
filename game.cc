#include "game.h"
using namespace std;

void print(const vector<string> &v) {
	cout << '[';
	for (int i = 0; i < v.size(); i++) {
		if (i == v.size() - 1) {
			cout << v[i];
		} else {
			cout << v[i] << ',';
		}
	}
	cout << ']' << endl;
}

void Game::setInitState(int numPlayers) {
	// Setting allDecks, which contains numPlayers number of decks worth of cards
	vector<string> allDecks;
	vector<string> completeDeck; // a complete 54-card deck
	vector<char> suits = {'H', 'D', 'S', 'C'};
	char curSuit;
	string value;
	string curCard;

	// Setting completeDeck
	for (int i = 0; i < 4; i++) {
		curSuit = suits[i];
		for (int j = 1; j <= 13; j++) {
			if (j == 1) value = "A";
			else if (j == 11) value = "J";
			else if (j == 12) value = "Q";
			else if (j == 13) value = "K";
			else value = to_string(j);
			curCard = value + curSuit;
			completeDeck.push_back(curCard);
		}
	}
	completeDeck.push_back("Joker");
	completeDeck.push_back("Joker");

	// Appending completeDeck to allDecks numPlayers number of times
	for (int i = 0; i < numPlayers; i++) {
		allDecks.insert(allDecks.end(), completeDeck.begin(), completeDeck.end());
	}

	srand(time(0));
	random_shuffle(allDecks.begin(), allDecks.end());
	vector<string> tempDrawPile;
	// Calling initDrawPile for each player
	Player tempPlayer; // Default player object
	for (int i = 0; i < numPlayers; i++) {
		tempDrawPile.clear();
		tempDrawPile.assign(allDecks.begin() + i * 54, allDecks.begin() + i * 54 + 54);
		players.push_back(tempPlayer);
		players.back().initDrawPile(tempDrawPile);
	}

	// Setting the first head
	string firstHead = players[0].getTopOfDrawPile();
	if (testingMode) firstHead = testingPrompt();
	if (firstHead == "Joker") firstHead = "2J";
	players[0].removeTopOfDrawPile();
	pair<CardPile, bool> tempHead;
	heads.push_back(tempHead);
	heads[0].first.placeOnTop(firstHead);
	heads[0].second = true;
}

bool Game::isWon() { return playerWhoWon != -1; }

void Game::printWinningMessage() {
	cout << "Player " << playerWhoWon << " wins!" << endl;
}

void Game::setTestingMode(bool b) { testingMode = b; }

void Game::printCurState() {	
	// Printing the state of all the active heads
	cout << "Heads:" << endl;
	for (int i = 0; i < heads.size(); i++) {
		if (heads[i].second) {
			cout << i + 1 << ": " << heads[i].first.getTopCard() <<
				" (" << heads[i].first.getNumCards() << ")" << endl;
		}
	}
	cout << endl;

	// Printing the state of all the players
	cout << "Players:" << endl;
	int numDraw = 0;
	int numDiscard = 0;
	int total = 0;
	for (int i = 0; i < players.size(); i++) {
		numDraw = players[i].getNumCardsInDrawPile();
		numDiscard = players[i].getNumCardsInDiscardPile();
		total = numDraw + numDiscard;
		cout << "Player " << i + 1 << ": " << total << 
			" (" << numDraw << " draw, " << numDiscard <<
			" discard)" << endl;
	}
}

int Game::numActiveHeads() {
	int count = 0;
	for (auto p : heads) {
		if (p.second) count++;
	}
	return count;
}

string Game::testingPrompt() {
	string card;
	string value;
	char suit; 
	while (true) {
		cout << "Card value?" << endl;
		cin >> value;
		
		// If input is invalid
		if (value != "A" && value != "J" &&
			value != "Q" && value != "K" &&
			value != "Joker" && value != "2" &&
			value != "3" && value != "4" &&
			value != "5" && value != "6" &&
			value != "7" && value != "8" &&
			value != "9" && value != "10") {
			continue;
		}
		break;
	}

	if (value == "Joker") return value;
	
	while (true) {
		cout << "Suit?" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> suit;

		// If input is invalid
		if (suit != 'H' && suit != 'S' &&
			suit != 'C' && suit != 'D') {
			continue;
		}
		break;
	}

	card = value + suit;
	return card;
}

void Game::printPlayerState(int curPlayer, int remaining) {
	// Printing the state of all the active heads
	cout << "Heads:" << endl;
	for (int i = 0; i < heads.size(); i++) {
		if (heads[i].second) {
			cout << i + 1 << ": " << heads[i].first.getTopCard() <<
				" (" << heads[i].first.getNumCards() << ")" << endl;
		}
	}
	cout << endl;

	// Printing the state of all the players
	cout << "Players:" << endl;
	int numDraw = 0;
	int numDiscard = 0;
	int total = 0;
	int reserve = players[curPlayer - 1].reserveExists ? 1 : 0;
	for (int i = 0; i < players.size(); i++) {
		numDraw = players[i].getNumCardsInDrawPile();
		numDiscard = players[i].getNumCardsInDiscardPile();
		total = numDraw + numDiscard;
		cout << "Player " << i + 1 << ": " << total << 
			" (" << numDraw << " draw, " << numDiscard <<
			" discard)";
	
		if (i == curPlayer - 1) {
			cout << " + 1 in hand, " << remaining << " remaining, " <<
				reserve << " in reserve";
		}
		cout << endl;
	}	
}

string Game::cardInHand(int curPlayer) {
	string retval;
	string reserve;
	if (players[curPlayer - 1].getNumCardsInDrawPile() > 0) {
		retval = players[curPlayer - 1].getTopOfDrawPile();
		players[curPlayer - 1].removeTopOfDrawPile();
		return retval;
	} else if (players[curPlayer - 1].getNumCardsInDiscardPile() > 0) {
		players[curPlayer - 1].shuffleDiscardIntoDraw();
		retval = players[curPlayer - 1].getTopOfDrawPile();
		players[curPlayer - 1].removeTopOfDrawPile();
		return retval;
	} else if (players[curPlayer - 1].reserveExists) {
		reserve = players[curPlayer - 1].getReserve();
		players[curPlayer - 1].placeOnTopOfDrawPile(reserve);
		players[curPlayer - 1].reserveExists = false;
		return "END TURN";
	}
	return "WON";
}

int getCardValue(const string &card) {
	if (card.size() == 3) return 10;

	if (card[0] == 'A') return 1;
	else if (card[0] == 'J') return 11;
	else if (card[0] == 'Q') return 12;
	else if (card[0] == 'K') return 13;
	else return card[0] - '0';	
}

void Game::cutOffTheHead(int curPlayer, const string &inHand) {
	// Note: If there's a "xJ" in the oldest head, then we change that to a "Joker" when 
	//   adding the oldest head to the discard pile
	int oldestHeadIdx = 0;
	// Finding the oldest head
	for (int i = 0; i < heads.size(); i++) {
		if (heads[i].second) {
			oldestHeadIdx = i;
			break;
		}
	}
	
	// Placing the played card on the discard pile
	players[curPlayer - 1].placeOnTopOfDiscardPile(inHand);
	
	if (players[curPlayer - 1].reserveExists) {
		// place the reserve on the draw pile
		string reserve = players[curPlayer - 1].getReserve();
		players[curPlayer - 1].placeOnTopOfDrawPile(reserve);
		players[curPlayer - 1].reserveExists = false;
	}

	// Adding oldest head to the discard pile
	int numCardsInHead = heads[oldestHeadIdx].first.getNumCards();
	string curTopOfHead;
	for (int i = 0; i < numCardsInHead; i++) {
		curTopOfHead = heads[oldestHeadIdx].first.getTopCard();
		if (curTopOfHead[curTopOfHead.size() - 1] == 'J') { // If top card is a valued joker
			curTopOfHead = "Joker";
		}
		players[curPlayer - 1].placeOnTopOfDiscardPile(curTopOfHead);
		heads[oldestHeadIdx].first.removeTopCard();
	}

	// Creating the 1st new head
	string drawnCard = cardInHand(curPlayer);
	if (testingMode) drawnCard = testingPrompt();
	if (drawnCard == "Joker") drawnCard = "2J";
	pair<CardPile, bool> temp; // pair.first is a default CardPile object
	heads.push_back(temp);
	heads.back().first.placeOnTop(drawnCard);
	heads.back().second = true;

	// Creating the 2nd new head	
	drawnCard = cardInHand(curPlayer);
	if (testingMode) drawnCard = testingPrompt();
	if (drawnCard == "Joker") drawnCard = "2J";
	heads.push_back(temp);
	heads.back().first.placeOnTop(drawnCard);
	heads.back().second = true;

	// Making the oldest head inactive, i.e., removing it from 
	//   the game
	heads[oldestHeadIdx].second = false;
}

int Game::oldestActiveHead() {
	for (int i = 0; i < heads.size(); i++) {
		if (heads[i].second) return i + 1;
	}
}

bool Game::noOtherValidMove(const string &inHand) {
	int cardValue = getCardValue(inHand);
	int headCardValue;
	for (auto p : heads) {
		if (p.second) {
			headCardValue = getCardValue(p.first.getTopCard());
			if (cardValue <= headCardValue || // Action 1, 2 are valid
				headCardValue == 1) { // Action 3 is valid
				return false;
			}
		}
	}
	return true;
}

void Game::play(int curPlayer) {
	cout << "Player " << curPlayer << ", it is your turn." << endl;
	int input;

	// Inputting a character (which will typically be a new line)
	cin.clear();
	cin.ignore(100, '\n');
	cin.get(); // This input is redundant and will typically be a blank line
	cout << endl;
	int numDraws = numActiveHeads();
	string inHand;
	int drawsRemaining;
	string temp;
	int headTopCardValue;
	string jokerValue;
	bool swapped = false;
	int cardValue;
	string reserve;

	for (int i = 0; i < numDraws; i++) {
		inHand = cardInHand(curPlayer);
		if (inHand == "WON") {
			playerWhoWon = curPlayer;
			return;
		} else if (inHand == "END TURN") {
			return;
		}

		drawsRemaining = numDraws - 1 - i;
		printPlayerState(curPlayer, drawsRemaining); 
		cout << endl;

		// This while loop implements one entire draw and play	
		while (true) {
			// Prompting the current player and receiving input

			if (testingMode && !swapped) {
				inHand = testingPrompt();
			}
			cout << "Player " << curPlayer << ", you are holding a " << inHand <<
				". Your move?" << endl;
			cin >> input;
			cout << endl;

			// Checking if input is out of bounds if the head is inactive
			if (input < 0 || input > heads.size() || 
				(input > 0 && !heads[input - 1].second)) {
				continue;
			} else { // input head is active	
				if (input == 0) {
					if (inHand[inHand.size() - 1] == 'J') inHand = "Joker";
					if (players[curPlayer - 1].reserveExists) { // ACTION 5
						temp = players[curPlayer - 1].getReserve();
						players[curPlayer - 1].setReserve(inHand);
						if (testingMode) temp = testingPrompt();
						inHand = temp;
						swapped = true;
						continue;
					} else if (numActiveHeads() > 1) { // ACTION 4
						players[curPlayer - 1].reserveExists = true;
						players[curPlayer - 1].setReserve(inHand);
						break;
					}
				} else if (input != 0 || swapped) {
					headTopCardValue = heads[input - 1].first.getTopCardValue();
					if (inHand == "Joker") {
						cout << "Joker Value?" << endl;
						cin >> jokerValue;
						cout << endl;
						inHand = jokerValue + 'J';
					}
					cardValue = getCardValue(inHand);
					if (cardValue < headTopCardValue) { // ACTION 1
						heads[input - 1].first.placeOnTop(inHand);
						break;
					} else if (cardValue == headTopCardValue) { // ACTION 2
						heads[input - 1].first.placeOnTop(inHand);
						return;
					} else if (headTopCardValue == 1) { // ACTION 3
						heads[input - 1].first.placeOnTop(inHand);
						break;
					} else if (input == oldestActiveHead() &&
							   (players[curPlayer - 1].reserveExists || numActiveHeads() == 1) &&
							   noOtherValidMove(inHand)) {
						cutOffTheHead(curPlayer, inHand); 
						break;
						// Note that inHand cannot be a Joker and the head that is cut off
						//   is the oldest head, i.e., the closest "active" head to the 
						//   start of the vector, heads.
					} else { // Invalid input
						continue;
					}
				}
			}
		}	
		swapped = false;
	}
	if (players[curPlayer - 1].reserveExists) {
		// Returning the reserve to the top of the draw pile
		reserve = players[curPlayer - 1].getReserve();
		players[curPlayer - 1].placeOnTopOfDrawPile(reserve);
		players[curPlayer - 1].reserveExists = false;
	}
}































