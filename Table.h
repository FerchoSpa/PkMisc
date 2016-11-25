#ifndef _TABLE_H
#define _TABLE_H

#include <list>

#include "Hand.h"

class Table {
	int nPlayers;
	Hand* playerHands[10];
	int cardsInPlay[52];

	int count[10][10];

public:
	Table();
	void addWholeCards(int c0, int c1);
	void evaluate();
	int  getCount(int player, int countId);

private:
	void addBoardCard(Card* card);
	void removeLast();
	void evaluateHandsWithBoard();
};

#endif
