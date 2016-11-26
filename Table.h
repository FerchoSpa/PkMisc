#ifndef _TABLE_H
#define _TABLE_H

#include <list>

#include "Hand.h"

enum TableEvalRank {
	TER_WIN = HER_HIGH_CARD+1,
	TER_LOSE,
	TER_TIE,
	TER_UNDECIDED
};

class Table {
	int nPlayers;
	Hand* playerHands[10];
	int handResults[10];
	int cardsInPlay[52];

	int count[10][TER_UNDECIDED+1];

public:
	Table();
	void addWholeCards(int c0, int c1);
	void evaluate();
	int  getCount(int player, int countId);

	void addBoardCard(Card* card);
	void evaluateHandsWithBoard();

private:
	void removeLast();
};

#endif
