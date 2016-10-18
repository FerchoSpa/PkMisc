#ifndef _CARD_H
#define _CARD_H

enum Suits {
	HEARTS = 0, DIAMONDS = 1, SPADES = 2, CLUBS = 3, N_SUITS
};

class Card {

	// Short visual representation of Suits:
	//  - Heart, Diamond, Spade and Clubs
	const static char strSuits[4];

	// Numeric value (0 - 51) to Suits(Heart, Diamond, Spade, Club)
	const static int nvalToSuit[52];

	const static int strSymbolicRanks[14];

public:
	int suit;
	int ordinalRank;  // 0-12 (A, 2, ..., J, Q, K)

private:
	int numericValue;  // 0-51
	int numericRank;   // 1-13 (A, 2, ..., J, Q, K)
	char symbolicRank;

	char cardHumanReadable[3];

public:
	Card(int numericValue);

	char* toString();
};

#endif
