#ifndef _CARD_H
#define _CARD_H

enum Suits {
	HEARTS = 0, DIAMONDS = 1, SPADES = 2, CLUBS = 3
};

class Card {

	// Short visual representation of Suits:
	//  - Heart, Diamond, Spade and Clubs
	const static char strSuits[4];

	// Numeric value (0 - 51) to Suits(Heart, Diamond, Spade, Club)
	const static int nvalToSuit[52];

	const static int strSymbolicRanks[14];

	int numericValue;
	int numericRank;
	int suit;
	char symbolicRank;

	char cardHumanReadable[3];

public:
	Card(int numericValue);

	char* toString();
};

#endif
