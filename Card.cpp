#include "Card.h"

#include <stdio.h>

Card::Card(int numericValue) {
	printf("Creating card\n");
    this->numericValue = numericValue;
    int n = numericValue % 13;
    this->numericRank = n+1;
    this->suit = nvalToSuit[numericValue];
    this->symbolicRank = strSymbolicRanks[n+1];

}
