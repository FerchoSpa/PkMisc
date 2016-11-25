#ifndef _HAND_H
#define _HAND_H

#include <list>

#include "Card.h"

#define TO_STRING_STR_LEN 80
enum HandEvalRank {
	HER_NONE = -1,
	HER_ROYAL_FLUSH = 0,
	HER_STRAIGHT_FLUSH,
	HER_FOUR_OF_A_KIND,
	HER_FULL_HOUSE,
	HER_FLUSH,
	HER_STRAIGHT,
	HER_THREE_OF_A_KIND,
	HER_TWO_PAIRS,
	HER_PAIR,
	HER_HIGH_CARD
};

class Hand {
	int suitCountDict[4];
	int faceCountDict[13];
	std::list<Card*> cardsInHand;

	std::list<int> faceCountsNonZero;
	int countOfMostRepeatedCard; // Four of a kind, three of a kind, pair
	int numberOfMostRepeatedCards;// 1 pair, 2 pairs, 3 pairs
	int countOf2ndMostRepeatedCard; // Four of a kind, three of a kind, pair (for 2 pair)

	Card* sortedCardsByNumericValue[7];

	int   nUnrepeatedCardsByRankValue;
	int   sortedUnrepeatedCardsByRankValue[7];

	char _toStringStr[TO_STRING_STR_LEN];
public:
	Hand();
	void accept(Card* c);
	void removeLast();
	int  evaluate();

	int* getSuitCount();
	Card** getSortedCardsByNumericValue();

	char* toString();
	void showCards();

private:
	void sortCardsByNumericValue();
	int  getSuitWithMostCards();
	int  getNextSuitWithMostCards(int suit);
	bool isRoyalFlush(int suit);
	bool isStraightFlush(int suit);
	bool isFourOfAKind();
	bool isFullHouse(int suitWithMostCards);
	bool isStraight();
	bool isThreeOfAKind();
	bool isTwoPairs();
	bool isPair();
	void populateMostRepeatedCardCount();
};

#endif
