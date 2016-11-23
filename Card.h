#ifndef _CARD_H
#define _CARD_H

#define C1H  0 /* Ace of Heart */
#define C2H  1 /*   2 of Heart */
#define C3H  2 /*   3 of Heart */
#define C4H  3 /*   4 of Heart */
#define C5H  4 /*   5 of Heart */
#define C6H  5 /*   6 of Heart */
#define C7H  6 /*   7 of Heart */
#define C8H  7 /*   8 of Heart */
#define C9H  8 /*   9 of Heart */
#define CTH  9 /*  10 of Heart */
#define CJH 10 /*   J of Heart */
#define CQH 11 /*   Q of Heart */
#define CKH 12 /*   K of Heart */

#define C1D 13 /* Ace of Diamonds */
#define C2D 14 /*   2 of Diamonds */
#define C3D 15 /*   3 of Diamonds */
#define C4D 16 /*   4 of Diamonds */
#define C5D 17 /*   5 of Diamonds */
#define C6D 18 /*   6 of Diamonds */
#define C7D 19 /*   7 of Diamonds */
#define C8D 20 /*   8 of Diamonds */
#define C9D 21 /*   9 of Diamonds */
#define CTD 22 /*  10 of Diamonds */
#define CJD 23 /*   J of Diamonds */
#define CQD 24 /*   Q of Diamonds */
#define CKD 25 /*   K of Diamonds */

#define C1S 26 /* Ace of Spades */
#define C2S 27 /*   2 of Spades */
#define C3S 28 /*   3 of Spades */
#define C4S 29 /*   4 of Spades */
#define C5S 30 /*   5 of Spades */
#define C6S 31 /*   6 of Spades */
#define C7S 32 /*   7 of Spades */
#define C8S 33 /*   8 of Spades */
#define C9S 34 /*   9 of Spades */
#define CTS 35 /*  10 of Spades */
#define CJS 36 /*   J of Spades */
#define CQS 37 /*   Q of Spades */
#define CKS 38 /*   K of Spades */

#define C1C 39 /* Ace of Clubs */
#define C2C 40 /*   2 of Clubs */
#define C3C 41 /*   3 of Clubs */
#define C4C 42 /*   4 of Clubs */
#define C5C 43 /*   5 of Clubs */
#define C6C 44 /*   6 of Clubs */
#define C7C 45 /*   7 of Clubs */
#define C8C 46 /*   8 of Clubs */
#define C9C 47 /*   9 of Clubs */
#define CTC 48 /*  10 of Clubs */
#define CJC 49 /*   J of Clubs */
#define CQC 50 /*   Q of Clubs */
#define CKC 51 /*   K of Clubs */

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
	int numericValue;  // 0-51

private:
	int numericRank;   // 1-13 (A, 2, ..., J, Q, K)
	char symbolicRank;

	char cardHumanReadable[3];

public:
	Card(int numericValue);

	char* toString();
	int   getNumericRank();
};

#endif
