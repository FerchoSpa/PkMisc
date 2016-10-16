#ifndef _CARD_H
#define _CARD_H

class Card {
	enum Suits {
		HEARTS   = 0,
		DIAMONDS = 1,
		SPADES   = 2,
		CLUBS    = 3
	};

	// Short visual representation of Suits:
	//  - Heart, Diamond, Spade and Clubs
	char strSuits[4] = {'H', 'D', 'S', 'C'};

	// Numeric value (0 - 51) to Suits(Heart, Diamond, Spade, Club)
	int nvalToSuit[] = {HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, \
	                HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, \
	                DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, \
	                DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, \
	                SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, \
	                SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, \
	                CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, \
	                CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS};

	int strSymbolicRanks = {'Nada', '0', 'A', '2', '3', '4', '5', '6', '7',
			'8', '9', 'T', 'J', 'Q', 'K'
	};

	int numericValue;
	int numericRank;
	int suit;
	char symbolicRank;


public:
	Card(int numericValue);
};

#endif
