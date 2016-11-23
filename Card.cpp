#include "Card.h"

#include <stdio.h>


const char Card::strSuits[4] = {'H', 'D', 'S', 'C'};

const int Card::strSymbolicRanks[] = { 'N', 'A', '2', '3', '4', '5', '6', '7',
		'8', '9', 'T', 'J', 'Q', 'K' };


const int Card::nvalToSuit[52] = {HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, \
                HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, \
                DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, \
                DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, \
                SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, \
                SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, \
                CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, \
                CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS};


Card::Card(int numericValue) {
    this->numericValue = numericValue;
    int n = numericValue % 13;
    this->ordinalRank = n;
    this->numericRank = n+1;
    this->suit = nvalToSuit[numericValue];
    this->symbolicRank = strSymbolicRanks[n+1];
}

int Card::getNumericRank() {
	return this->numericRank;
}

char* Card::toString() {
	this->cardHumanReadable[0] = this->symbolicRank;
	this->cardHumanReadable[1] = strSuits[this->suit];
	this->cardHumanReadable[2] = '\0';
	return this->cardHumanReadable;
}
