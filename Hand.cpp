#include "Hand.h"

#include <stdio.h>



Hand::Hand() {
	printf("Creating Hand\n");
	for (int i=0; i<N_SUITS; i++){
		suitCountDict[i] = 0;
	}
}

char* Hand::toString() {
	return NULL;
}


void Hand::accept(Card* c){
	printf("List size:%ld\n", cardsInHand.size());
	cardsInHand.push_back(c);
	printf("List size:%ld\n", cardsInHand.size());
	suitCountDict[c->suit] += 1;
}

void Hand::removeLast() {
	Card* c = cardsInHand.back();
	cardsInHand.pop_back();
	printf("List size:%ld, card:%s\n", cardsInHand.size(), c->toString());
}
