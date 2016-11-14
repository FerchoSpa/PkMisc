#include <stdio.h>
#include <assert.h>
// 0 1 2 3 4 5 6 7 8 9 0 1 2 (A-K H)
#include "Card.h"
#include "Hand.h"
//#include "BoardsBuilder.h"

Hand* createHandWithFullBoard(int a, int b, int c, int d, int e, int f, int g) {
	Card* c1 = new Card(a);
	Card* c2 = new Card(b);
	Card* c3 = new Card(c);
	Card* c4 = new Card(d);
	Card* c5 = new Card(e);
	Card* c6 = new Card(f);
	Card* c7 = new Card(g);
	printf("c1:%s\n", c1->toString());

	Hand* h = new Hand();
	h->accept(c1);
	h->accept(c2);
	h->accept(c3);
	h->accept(c4);
	h->accept(c5);
	h->accept(c6);
	h->accept(c7);

	return h;
}

// 0 -12 - A, 2, 3..., K Hearts
//13 -25 - A, 2, 3..., K Diamonds
//26 -38 - A, 2, 3..., K Spades
//39 -51 - A, 2, 3..., K Clubs
void someInitialHand() {
	Hand* h = createHandWithFullBoard(3, 23, 7, 13, 26, 39, 35);

	printf("Hand:%s\n", h->toString());

	int* suitCount = h->getSuitCount();
	assert(suitCount[0] == 2);
	assert(suitCount[1] == 2);
	assert(suitCount[2] == 2);
	assert(suitCount[3] == 1);

	h->evaluate();

	Card** sortedCards = h->getSortedCardsByNumericValue();
	for (int i=0; i<7; i++) {
		printf("i:%d : %s\n", i, sortedCards[i]->toString());
	}

	h->removeLast();
}

void checkRoyalFlush_Spades() {
	//                                KD, TD, QD, AD, AS, JD, TS
	Hand* h = createHandWithFullBoard(25, 23, 24, 13, 26, 22, 35);

	int* suitCount = h->getSuitCount();
	assert(suitCount[0] == 0);
	assert(suitCount[1] == 5);   // 5 Spades
	assert(suitCount[2] == 2);
	assert(suitCount[3] == 0);

	int v = h->evaluate();
	assert(v==HER_ROYAL_FLUSH);
}

void checkRoyalFlush_Clubs() {
	Hand* h = createHandWithFullBoard(C1H, CKC, CTC, C4D, CQC, C1C, CJC);

	int* suitCount = h->getSuitCount();
	assert(suitCount[0] == 1);
	assert(suitCount[1] == 1);
	assert(suitCount[2] == 0);
	assert(suitCount[3] == 5);

	int v = h->evaluate();
	assert(v==HER_ROYAL_FLUSH);
}


int main() {

	someInitialHand();
	checkRoyalFlush_Spades();
	checkRoyalFlush_Clubs();

	printf("Done\n");

	return 0;
}
