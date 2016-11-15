#include "Hand.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

Hand::Hand() {
	printf("Creating Hand\n");
	for (int i=0; i<N_SUITS; i++){
		suitCountDict[i] = 0;
	}
	for (int i=0; i<13; i++){
		faceCountDict[i] = 0;
	}
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
	printf("removeLast:List size:%ld, card:%s\n", cardsInHand.size(), c->toString());
}

void Hand::sortCardsByNumericValue() {
	bzero(sortedCardsByNumericValue, 7*sizeof(Card*));
	std::list<Card*>::iterator it;
	int k=0;
	for (it=cardsInHand.begin(); it!=cardsInHand.end(); ++it) {
		sortedCardsByNumericValue[k] = *it;
		k += 1;
	}
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

bool Hand::isRoyalFlush(int suit){
	Card* cardsOnRoyalFlush[5];
	int nCardsOnRoyalFlush = 0;
	int n = cardsInHand.size();
	for (int i = 0; i<n; i++) {
		Card* card = sortedCardsByNumericValue[i];
		printf("isRoyalFlush:%s, suit:%d/%d, ordinalRank:%d\n", card->toString(), card->suit, suit, card->ordinalRank);
		if (card->suit == suit) {
			int ordinalRank = card->ordinalRank;
			if (ordinalRank == 0 || (ordinalRank >=9 && ordinalRank <=12)) {
				cardsOnRoyalFlush[nCardsOnRoyalFlush] = card;
				nCardsOnRoyalFlush += 1;
			}
		}
	}
	printf("nCardsOnRoyalFlush:%d\n", nCardsOnRoyalFlush);
	if (nCardsOnRoyalFlush<5)
		return false;
	return cardsOnRoyalFlush[0]->ordinalRank == 0 &&
			cardsOnRoyalFlush[1]->ordinalRank == 9 &&
			cardsOnRoyalFlush[2]->ordinalRank == 10 &&
			cardsOnRoyalFlush[3]->ordinalRank == 11 &&
			cardsOnRoyalFlush[4]->ordinalRank == 12;
}

int Hand::evaluate() {
	assert(cardsInHand.size() == 7);

	this->sortCardsByNumericValue();

	int suitMax = getSuitWithMostCards();
//	for (int i = 0; i<4; i++) {
//		printf("evaluate:%d = %d\n", i, suitCountDict[i]);
//	}
	int suitedMaxCount = suitCountDict[suitMax];
//	printf("Suit:%d, ncards:%d\n", suitMax, suitedMaxCount);

	if (suitedMaxCount>=0) {
		if (isRoyalFlush(suitMax)) {
			return HER_ROYAL_FLUSH;
		} else if (isStraightFlush(suitMax)) {
			return HER_STRAIGHT_FLUSH;
		}
	}

	return HER_NONE;
}
