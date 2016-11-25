#ifndef _TABLE_H
#define _TABLE_H

#include <list>

#include "Hand.h"

class Table {
	int nPlayers;
	Hand* playerHands[10];
	int cardsInPlay[52];

public:
	Table();
	void addWholeCards(int c0, int c1);
	void evaluate();

private:
	//void populateMostRepeatedCardCount();
};

#endif
