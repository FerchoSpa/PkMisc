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


void Hand::accept(Card* c){
	cardsInHand.push_back(c);
	printf("accept:List size:%ld\n", cardsInHand.size());
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
	}
	for (int i = 0; i<k-1; i++) {
		for (int j = i+1; j<k; j++) {
			Card* iCard = sortedCardsByNumericValue[i];
			Card* jCard = sortedCardsByNumericValue[j];

			if (iCard->numericValue < jCard->numericValue) {
				Card* tmp = sortedCardsByNumericValue[i];
				sortedCardsByNumericValue[i] = sortedCardsByNumericValue[j];
				sortedCardsByNumericValue[j] = sortedCardsByNumericValue[i];
			}
		}
	}
}

void Hand::evaluate() {
	assert(cardsInHand.size() == 7);

	this->sortCardsByNumericValue();

}
