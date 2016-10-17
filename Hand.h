#ifndef _HAND_H
#define _HAND_H

#include <list>

#include "Card.h"

enum RankValues {
	  VAL_NONE            = -1,
	  VAL_ROYAL_FLUSH     = 0,
	  VAL_STRAIGHT_FLUSH  = 1,
	  VAL_FOUR_OF_A_KIND  = 2,
	  VAL_FULL_HOUSE      = 3,
	  VAL_FLUSH           = 4,
	  VAL_STRAIGHT        = 5,
	  VAL_THREE_OF_A_KIND = 6,
	  VAL_TWO_PAIR        = 7,
	  VAL_PAIR            = 8,
	  VAL_HIGH_CARD       = 9
};

class Hand {
	 std::list<Card*> mylist;

public:
	Hand();
	void accept(Card* c);

	char* toString();
};

#endif
