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
	//printf("c1:%s\n", c1->toString());

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

	//printf("Hand:%s\n", h->toString());

	int* suitCount = h->getSuitCount();
	assert(suitCount[0] == 2);
	assert(suitCount[1] == 2);
	assert(suitCount[2] == 2);
	assert(suitCount[3] == 1);

	h->evaluate();

//	Card** sortedCards = h->getSortedCardsByNumericValue();
//	for (int i=0; i<7; i++) {
//		printf("i:%d : %s\n", i, sortedCards[i]->toString());
//	}

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

void checkStraightFlush_5Diamonds() {
	Hand* h = createHandWithFullBoard(C2D, CKC, C1D, C4D, CQC, C5D, C3D);

	int v = h->evaluate();
	assert(v==HER_STRAIGHT_FLUSH);
}

void checkStraightFlush_6Clubs() {
	Hand* h = createHandWithFullBoard(C2C, C5C, C7C, C8C, C8D, C4C, C6C);

	int v = h->evaluate();
	assert(v==HER_STRAIGHT_FLUSH);
}

void checkStraightFlush_7Spades() {
	Hand* h = createHandWithFullBoard(C2S, C8S, C7S, C9S, C4S, CTS, C6S);

	int v = h->evaluate();
	assert(v==HER_STRAIGHT_FLUSH);
}

void checkFourOfAKind() {
	Hand* h = createHandWithFullBoard(C2S, C8S, C2H, C2D, C4S, CTS, C2C);

	int v = h->evaluate();
	assert(v==HER_FOUR_OF_A_KIND);
}

void checkFullHouse() {
	Hand* h = createHandWithFullBoard(C2S, C2D, C2H, C5D, C4S, C5S, C7C);

	int v = h->evaluate();
	assert(v==HER_FULL_HOUSE);
}

void checkFlush() {
	Hand* h = createHandWithFullBoard(C2S, C9S, C5S, C6D, C4S, CJS, C7C);
	int v = h->evaluate();
	assert(v==HER_FLUSH);
}

void checkStraight() {
	Hand* h = createHandWithFullBoard(C2S, C9S, C5H, C6D, C4D, C3C, C2C);
	int v = h->evaluate();
	assert(v==HER_STRAIGHT);
}

void checkStraight_river() {
	Hand* h = createHandWithFullBoard(C9S, C7S, C6H, C6D, C5D, C3C, C8C);
	int v = h->evaluate();
	assert(v==HER_STRAIGHT);
}

void checkThreeOfAKind() {
	Hand* h = createHandWithFullBoard(C9S, C9H, CTH, C6D, C9D, C3C, C7C);
	int v = h->evaluate();
	assert(v==HER_THREE_OF_A_KIND);
}

void checkTwoPairs() {
	Hand* h = createHandWithFullBoard(C9S, C9H, CTH, CTD, C5D, C3C, C7C);
	int v = h->evaluate();
	assert(v==HER_TWO_PAIRS);
}

void checkPair() {
	Hand* h = createHandWithFullBoard(C9S, C3H, CTH, CJD, C5D, C9C, C7C);
	int v = h->evaluate();
	assert(v==HER_PAIR);
}


void checkPair_TwoPair() {
	Hand* h = createHandWithFullBoard(C9H, C3H, CTH, CTD, C5D, CKC, C7C);
	int v = h->evaluate();
	assert(v==HER_PAIR);


	h->removeLast();
	h->accept(new Card(C3S));
	v=h->evaluate();
	assert(v==HER_TWO_PAIRS);
}


void checkOneLoopOfRemoveLast() {
	int count[10];
	Hand* h = createHandWithFullBoard(C1H, C2H, C3H, C4H, C5H, C6H, C7H);
	int v = h->evaluate();
	assert(v==HER_STRAIGHT_FLUSH);

	bzero(count, sizeof(count));
	h->removeLast();
	for (int i = 7; i<52; i++) {
		h->accept(new Card(i));
		v = h->evaluate();
		//printf("\tv:%d\n", v);
		count[v] += 1;
		h->removeLast();
	}
	for (int i = 0; i<10; i++) {
		printf("count[%d] = %d\n", i, count[i]);
	}

}


int main() {
	someInitialHand();
	checkRoyalFlush_Spades();
	checkRoyalFlush_Clubs();
	checkStraightFlush_5Diamonds();
	checkStraightFlush_6Clubs();
	checkStraightFlush_7Spades();
	checkFourOfAKind();
	checkFullHouse();
	checkFlush();
	checkStraight();
	checkStraight_river();
	checkThreeOfAKind();
	checkTwoPairs();
	checkPair();
	checkPair_TwoPair();
	checkOneLoopOfRemoveLast();


	printf("Done\n");


	return 0;
}
