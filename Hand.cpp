#include "Hand.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

Hand::Hand() {
	for (int i=0; i<N_SUITS; i++){
		suitCountDict[i] = 0;
	}
	for (int i=0; i<13; i++){
		faceCountDict[i] = 0;
	}
	nUnrepeatedCardsByRankValue=0;
	countOfMostRepeatedCard=0;
	numberOfMostRepeatedCards=0;
	countOf2ndMostRepeatedCard=0;
	nCardsOnStraightFlush=0;
	bzero(cardsOnStraightFlush, sizeof(cardsOnStraightFlush));
	mostRepeatedCard = -1;
}

char* Hand::toString() {
	snprintf(_toStringStr, TO_STRING_STR_LEN, "H:%0d,D:%0d,S:%0d,C:%0d", suitCountDict[0],
			suitCountDict[1],
			suitCountDict[2], suitCountDict[3]);
	return _toStringStr;
}

int* Hand::getSuitCount() {
	return this->suitCountDict;
}

Card** Hand::getSortedCardsByNumericValue() {
	return this->sortedCardsByNumericValue;
}

void Hand::accept(Card* c){
	cardsInHand.push_back(c);
	suitCountDict[c->suit] += 1;
	int cardOrdinalRank = c->ordinalRank;
	if (faceCountDict[cardOrdinalRank] == 0){
		faceCountsNonZero.push_back(cardOrdinalRank);
	}
	faceCountDict[cardOrdinalRank] += 1;
}

void Hand::removeLast() {
	Card* c = cardsInHand.back();
	cardsInHand.pop_back();
	suitCountDict[c->suit] -= 1;
	int cardOrdinalRank = c->ordinalRank;
	faceCountDict[cardOrdinalRank] -= 1;
	if (faceCountDict[cardOrdinalRank] == 0){
		faceCountsNonZero.remove(cardOrdinalRank);
	}
	//printf("removeLast:List size:%ld, card:%s\n", cardsInHand.size(), c->toString());
}

void Hand::sortCardsByNumericValue() {
	bzero(sortedCardsByNumericValue, 7*sizeof(Card*));
	bzero(cardsByRank, 7*sizeof(Card*));
	std::list<Card*>::iterator it;
	int k=0;
	for (it=cardsInHand.begin(); it!=cardsInHand.end(); ++it) {
		sortedCardsByNumericValue[k] = *it;
		cardsByRank[k] = *it;
		k += 1;
	}

	// Sort by Numeric Value (0-51)
	for (int i = 0; i<k-1; i++) {
		for (int j = i+1; j<k; j++) {
			Card* iCard = sortedCardsByNumericValue[i];
			Card* jCard = sortedCardsByNumericValue[j];

			if (jCard->numericValue < iCard->numericValue) {
				Card* tmp = sortedCardsByNumericValue[i];
				sortedCardsByNumericValue[i] = sortedCardsByNumericValue[j];
				sortedCardsByNumericValue[j] = tmp;
			}
		}
	}

	// Sort by Numeric Rank (1-13)
	for (int i = 0; i<k-1; i++) {
		for (int j = i+1; j<k; j++) {
			Card* iCard = cardsByRank[i];
			Card* jCard = cardsByRank[j];

			if (jCard->getNumericRank() < iCard->getNumericRank()) {
				Card* tmp = cardsByRank[i];
				cardsByRank[i] = cardsByRank[j];
				cardsByRank[j] = tmp;
			}
		}
	}

	nUnrepeatedCardsByRankValue = 1;
	sortedUnrepeatedCardsByRankValue[0] = cardsByRank[0]->getNumericRank();
	int prev = cardsByRank[0]->getNumericRank();
	for (int i = 1; i<k; i++) {
		if (cardsByRank[i]->getNumericRank() != prev) {
			prev = cardsByRank[i]->getNumericRank();
			sortedUnrepeatedCardsByRankValue[nUnrepeatedCardsByRankValue] = prev;
			nUnrepeatedCardsByRankValue += 1;
		}
	}
}

int Hand::getMostRepeatedCard() {
	return mostRepeatedCard;
}

int Hand::getSuitWithMostCards() {
	int idx = 0;
	int max = suitCountDict[0];
	for (int i = 1; i<4; i++) {
		if (suitCountDict[i]>max) {
			idx = i;
			max = suitCountDict[i];
		}
	}
	return idx;
}

int  Hand::getNextSuitWithMostCards(int suit) {
	int idx = 0;
	int max = 0;
	for (int i = 0; i<4; i++) {
		if (i != suit && suitCountDict[i]>max) {
			idx = i;
			max = suitCountDict[i];
		}
	}
	return idx;
}

bool Hand::isRoyalFlush(int suit){
	Card* cardsOnRoyalFlush[5];
	int nCardsOnRoyalFlush = 0;
	int n = cardsInHand.size();
	for (int i = 0; i<n; i++) {
		Card* card = sortedCardsByNumericValue[i];
		if (card->suit == suit) {
			int ordinalRank = card->ordinalRank;
			if (ordinalRank == 0 || (ordinalRank >=9 && ordinalRank <=12)) {
				cardsOnRoyalFlush[nCardsOnRoyalFlush] = card;
				nCardsOnRoyalFlush += 1;
			}
		}
	}
	if (nCardsOnRoyalFlush<5)
		return false;
	return cardsOnRoyalFlush[0]->ordinalRank == 0 &&
			cardsOnRoyalFlush[1]->ordinalRank == 9 &&
			cardsOnRoyalFlush[2]->ordinalRank == 10 &&
			cardsOnRoyalFlush[3]->ordinalRank == 11 &&
			cardsOnRoyalFlush[4]->ordinalRank == 12;
}

int Hand::getHighCardOnStraightFlush(){
	return cardsOnStraightFlush[nCardsOnStraightFlush-1]->ordinalRank;
}

Card* Hand::getHighCardInReverseOrder(int minusOrder){
	return cardsByRank[cardsInHand.size()-1-minusOrder];
}

bool Hand::isStraightFlush(int suit){
	nCardsOnStraightFlush = 0;
	int n = cardsInHand.size();
	for (int i = 0; i<n; i++) {
		Card* card = sortedCardsByNumericValue[i];
		if (card->suit == suit) {
			cardsOnStraightFlush[nCardsOnStraightFlush] = card;
			nCardsOnStraightFlush += 1;
		}
	}
	if (nCardsOnStraightFlush<5)
		return false;
	if (cardsOnStraightFlush[0]->ordinalRank + 4 == cardsOnStraightFlush[4]->ordinalRank)
		return true;
	if (nCardsOnStraightFlush==5)
		return false;
	if (cardsOnStraightFlush[1]->ordinalRank + 4 == cardsOnStraightFlush[5]->ordinalRank)
		return true;
	if (nCardsOnStraightFlush==6)
		return false;
	return cardsOnStraightFlush[2]->ordinalRank + 4 == cardsOnStraightFlush[6]->ordinalRank;
}

bool Hand::isFourOfAKind(){
	return countOfMostRepeatedCard == 4;
}

bool Hand::isFullHouse(int suitWithMostCards) {
	return countOfMostRepeatedCard == 3 && countOf2ndMostRepeatedCard >= 2;
}

bool Hand::isStraight() {
	if (nUnrepeatedCardsByRankValue<5)
		return false;
	if ((sortedUnrepeatedCardsByRankValue[0]+4 == sortedUnrepeatedCardsByRankValue[4]) ||
			(sortedUnrepeatedCardsByRankValue[0] == 1 && sortedUnrepeatedCardsByRankValue[1]+3 == sortedUnrepeatedCardsByRankValue[4] &&
					sortedUnrepeatedCardsByRankValue[4]==13))
		return true;
	if (nUnrepeatedCardsByRankValue==5)
		return false;
	if ((sortedUnrepeatedCardsByRankValue[1]+4 == sortedUnrepeatedCardsByRankValue[5]) ||
			(sortedUnrepeatedCardsByRankValue[0] == 1 && sortedUnrepeatedCardsByRankValue[2]+3 == sortedUnrepeatedCardsByRankValue[5] &&
					sortedUnrepeatedCardsByRankValue[5]==13))
		return true;
	if (nUnrepeatedCardsByRankValue==6)
		return false;
	return ((sortedUnrepeatedCardsByRankValue[2]+4 == sortedUnrepeatedCardsByRankValue[6]) ||
			(sortedUnrepeatedCardsByRankValue[0] == 1 && sortedUnrepeatedCardsByRankValue[3]+3 == sortedUnrepeatedCardsByRankValue[6] &&
								sortedUnrepeatedCardsByRankValue[6]==13));
}

bool Hand::isThreeOfAKind() {
	return countOfMostRepeatedCard == 3;
}

bool Hand::isTwoPairs() {
	return countOfMostRepeatedCard == 2 && numberOfMostRepeatedCards>=2;
}

bool Hand::isPair() {
	return countOfMostRepeatedCard == 2;
}

void Hand::populateMostRepeatedCardCount(){
	std::list<int>::iterator it;
	countOfMostRepeatedCard = 0;
	countOf2ndMostRepeatedCard = 0;
	numberOfMostRepeatedCards += 1;
	mostRepeatedCard = *(faceCountsNonZero.begin());
	for (it=faceCountsNonZero.begin(); it!=faceCountsNonZero.end(); ++it) {
		int ordinalRank = *it;
		if (faceCountDict[ordinalRank]>countOfMostRepeatedCard) {
			countOfMostRepeatedCard = faceCountDict[ordinalRank];
			numberOfMostRepeatedCards = 1;
			mostRepeatedCard = ordinalRank;
		} else if (faceCountDict[ordinalRank]==countOfMostRepeatedCard) {
			numberOfMostRepeatedCards += 1;
		}
	}
	for (it=faceCountsNonZero.begin(); it!=faceCountsNonZero.end(); ++it) {
		int ordinalRank = *it;
		if (mostRepeatedCard != ordinalRank && faceCountDict[ordinalRank]>countOf2ndMostRepeatedCard) {
			countOf2ndMostRepeatedCard = faceCountDict[ordinalRank];
		}
	}
}

void Hand::showCards() {
	printf("cardsInHand:%ld\n", cardsInHand.size());
	std::list<Card*>::iterator it;
	for (it=cardsInHand.begin(); it!=cardsInHand.end(); ++it) {
		Card* card = *it;
		printf("Card:%d\n", card->getNumericRank());
	}
}
int Hand::evaluate() {
	assert(cardsInHand.size() == 7);

	this->sortCardsByNumericValue();

	int suitMax = getSuitWithMostCards();
	int suitedMaxCount = suitCountDict[suitMax];

	if (suitedMaxCount>=5) {
		if (isRoyalFlush(suitMax)) {
			return HER_ROYAL_FLUSH;
		} else if (isStraightFlush(suitMax)) {
			return HER_STRAIGHT_FLUSH;
		}
	}
	populateMostRepeatedCardCount();
	if (isFourOfAKind()) {
		return HER_FOUR_OF_A_KIND;
	}
	if (isFullHouse(suitMax)) {
		return HER_FULL_HOUSE;
	}
	if (suitedMaxCount>=5) {
		return HER_FLUSH;
	}
	if (isStraight()) {
		return HER_STRAIGHT;
	}
	if (isThreeOfAKind()) {
		return HER_THREE_OF_A_KIND;
	}
	if (isTwoPairs()) {
		return HER_TWO_PAIRS;
	}
	if (isPair()) {
		return HER_PAIR;
	}

	return HER_HIGH_CARD;
}
