#include <iostream>
#include <cstring>
#include "game.h"
using namespace std;

int main(int argc, char** argv) {	
	Game g;
	
	if (argc == 2 && strcmp(argv[1], "-testing") == 0) {
		g.setTestingMode(true);
	}

	int numPlayers;
	int curPlayer = 2; // Player 2 is always the first to be prompted
	cout << "How many players?" << endl;
	cin >> numPlayers; // numPlayers is always > 1
	cout << endl;
	g.setInitState(numPlayers);

	while (true) {
		g.printCurState();
		cout << endl;
		g.play(curPlayer);
		if (g.isWon()) {
			g.printWinningMessage();
			break;
		}
		curPlayer = (curPlayer == numPlayers) ? 1 : curPlayer + 1;
	}
}
