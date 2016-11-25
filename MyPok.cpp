#include <stdio.h>
#include <assert.h>
// 0 1 2 3 4 5 6 7 8 9 0 1 2 (A-K H)
#include "Card.h"
#include "Hand.h"
#include "Table.h"

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
	Hand* h = createHandWithFullBoard(C9H, C3H, CTH, CKD, C5D, C9C, C7C);
	int v = h->evaluate();
	assert(v==HER_PAIR);

	h->removeLast();
	h->accept(new Card(C3S));
	v = h->evaluate();
	assert(v==HER_TWO_PAIRS);
}

void pythonStraight() {
	Hand* h = createHandWithFullBoard(C1H, C2H, CQH, CKH, C1D, CTD, CJD);
	int v = h->evaluate();
	assert(v==HER_STRAIGHT);
}

void pythonFlush() {
	//2 3 5 13 26
	//Hand* h = createHandWithFullBoard(C1H, C2H, C3H, C4H, C6H, C1D, C1S);
	Hand* h = new Hand();
	h->accept(new Card(0));
	h->accept(new Card(1));
	h->accept(new Card(2));
	h->accept(new Card(3));
	h->accept(new Card(5));
	h->accept(new Card(13));
	h->accept(new Card(25));
	int v = h->evaluate();
	assert(v==HER_FLUSH);
	h->removeLast();
	h->accept(new Card(26));
	v = h->evaluate();
	assert(v==HER_FLUSH);
}

void pythonFlush27() {
	//2 3 5 14 27
	Hand* h = createHandWithFullBoard(C1H, C2H, C3H, C4H, C6H, C2D, C2S);
	int v = h->evaluate();
	assert(v==HER_FLUSH);
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

void checkLoopsOfRemoveLast() {
	int count[10];
	int v;
	Hand* h = new Hand();
	Card* cards[52];
	for (int i=0; i<52; i++)
		cards[i] = new Card(i);

	bzero(count, sizeof(count));

	int nc = 52;
	int c1 = 0;
	int c2 = 1;
	int nHands = 0;
	h->accept(cards[c1]);
	h->accept(cards[c2]);
	for (int i=0; i< nc; i++){
		if (i==c1 || i==c2) continue;
		h->accept(cards[i]);
		for (int j=i+1; j< nc; j++){
			if (j==c1 || j==c2) continue;
			h->accept(cards[j]);
			for (int k=j+1; k< nc; k++){
				if (k==c1 || k==c2) continue;
				h->accept(cards[k]);
				for (int l=k+1; l< nc; l++){
					if (l==c1 || l==c2) continue;
					h->accept(cards[l]);
					for (int m=l+1; m< nc; m++){
						if (m==c1 || m==c2) continue;
						h->accept(cards[m]);
						v = h->evaluate();
						count[v] += 1;
						nHands += 1;
						h->removeLast();
					}
					h->removeLast();
				}
				h->removeLast();
			}
			h->removeLast();
		}
		h->removeLast();
	}

	printf("Number of hands:%d\n", nHands);
	for (int i = 0; i<10; i++) {
		printf("...count[%d] = %d\n", i, count[i]);
	}
	assert(count[HER_ROYAL_FLUSH]     ==     49);
	assert(count[HER_STRAIGHT_FLUSH]  ==   1113);
	assert(count[HER_FOUR_OF_A_KIND]  ==   2668);
	assert(count[HER_FULL_HOUSE]      ==  47124);
	assert(count[HER_FLUSH]           == 138296);
	assert(count[HER_STRAIGHT]        ==  65508);
	assert(count[HER_THREE_OF_A_KIND] ==  92004);
	assert(count[HER_TWO_PAIRS]       == 469092);
	assert(count[HER_PAIR]            == 916776);
	assert(count[HER_HIGH_CARD]       == 386130);
}

void checkTable1Player(){
	Table* table = new Table();
	table->addWholeCards(C1H, CKH);

	table->evaluate();

}

int main() {
//	pythonFlush27();
//	pythonFlush();
//	pythonStraight();
//	someInitialHand();
//	checkRoyalFlush_Spades();
//	checkRoyalFlush_Clubs();
//	checkStraightFlush_5Diamonds();
//	checkStraightFlush_6Clubs();
//	checkStraightFlush_7Spades();
//	checkFourOfAKind();
//	checkFullHouse();
//	checkFlush();
//	checkStraight();
//	checkStraight_river();
//	checkThreeOfAKind();
//	checkTwoPairs();
//	checkPair();
//	checkPair_TwoPair();
//	checkOneLoopOfRemoveLast();
//	checkLoopsOfRemoveLast();
	checkTable1Player();

	printf("Done\n");


	return 0;
}
