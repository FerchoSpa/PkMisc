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
	printf("someInitialHand PASSED\n");
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
	printf("checkRoyalFlush_Spades PASSED\n");
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
	printf("checkRoyalFlush_Clubs PASSED\n");
}

void checkStraightFlush_5Diamonds() {
	Hand* h = createHandWithFullBoard(C2D, CKC, C1D, C4D, CQC, C5D, C3D);

	int v = h->evaluate();
	assert(v==HER_STRAIGHT_FLUSH);
	printf("checkStraightFlush_5Diamonds PASSED\n");
}

void checkStraightFlush_6Clubs() {
	Hand* h = createHandWithFullBoard(C2C, C5C, C7C, C8C, C8D, C4C, C6C);

	int v = h->evaluate();
	assert(v==HER_STRAIGHT_FLUSH);
	printf("checkStraightFlush_6Clubs PASSED\n");
}

void checkStraightFlush_7Spades() {
	Hand* h = createHandWithFullBoard(C2S, C8S, C7S, C9S, C4S, CTS, C6S);

	int v = h->evaluate();
	assert(v==HER_STRAIGHT_FLUSH);
	printf("checkStraightFlush_7Spades PASSED\n");
}

void checkFourOfAKind() {
	Hand* h = createHandWithFullBoard(C2S, C8S, C2H, C2D, C4S, CTS, C2C);

	int v = h->evaluate();
	assert(v==HER_FOUR_OF_A_KIND);
	printf("checkFourOfAKind PASSED\n");
}

void checkFullHouse() {
	Hand* h = createHandWithFullBoard(C2S, C2D, C2H, C5D, C4S, C5S, C7C);

	int v = h->evaluate();
	assert(v==HER_FULL_HOUSE);
	printf("checkFullHouse PASSED\n");
}

void checkFlush() {
	Hand* h = createHandWithFullBoard(C2S, C9S, C5S, C6D, C4S, CJS, C7C);
	int v = h->evaluate();
	assert(v==HER_FLUSH);
	printf("checkFlush PASSED\n");
}

void checkStraight() {
	Hand* h = createHandWithFullBoard(C2S, C9S, C5H, C6D, C4D, C3C, C2C);
	int v = h->evaluate();
	assert(v==HER_STRAIGHT);
	printf("checkStraight PASSED\n");
}

void checkStraight_river() {
	Hand* h = createHandWithFullBoard(C9S, C7S, C6H, C6D, C5D, C3C, C8C);
	int v = h->evaluate();
	assert(v==HER_STRAIGHT);
	printf("checkStraight_river PASSED\n");
}

void checkThreeOfAKind() {
	Hand* h = createHandWithFullBoard(C9S, C9H, CTH, C6D, C9D, C3C, C7C);
	int v = h->evaluate();
	assert(v==HER_THREE_OF_A_KIND);
	printf("checkThreeOfAKind PASSED\n");
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
	printf("checkPair PASSED\n");
}

void checkPair_TwoPair() {
	Hand* h = createHandWithFullBoard(C9H, C3H, CTH, CKD, C5D, C9C, C7C);
	int v = h->evaluate();
	assert(v==HER_PAIR);

	h->removeLast();
	h->accept(new Card(C3S));
	v = h->evaluate();
	assert(v==HER_TWO_PAIRS);
	printf("checkPair_TwoPair PASSED\n");
}

void pythonStraight() {
	Hand* h = createHandWithFullBoard(C1H, C2H, CQH, CKH, C1D, CTD, CJD);
	int v = h->evaluate();
	assert(v==HER_STRAIGHT);
	printf("pythonStraight PASSED\n");
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
	printf("pythonFlush PASSED\n");
}

void pythonFlush27() {
	//2 3 5 14 27
	Hand* h = createHandWithFullBoard(C1H, C2H, C3H, C4H, C6H, C2D, C2S);
	int v = h->evaluate();
	assert(v==HER_FLUSH);
	printf("pythonFlush27 PASSED\n");
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
	printf("checkOneLoopOfRemoveLast PASSED\n");
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
	printf("checkLoopsOfRemoveLast PASSED\n");
}

void checkTable1Player(){
	Table* table = new Table();
	table->addWholeCards(C1H, C2H);

	table->evaluate();
	assert(table->getCount(0, HER_ROYAL_FLUSH)     ==     49);
	assert(table->getCount(0, HER_STRAIGHT_FLUSH)  ==   1113);
	assert(table->getCount(0, HER_FOUR_OF_A_KIND)  ==   2668);
	assert(table->getCount(0, HER_FULL_HOUSE)      ==  47124);
	assert(table->getCount(0, HER_FLUSH)           == 138296);
	assert(table->getCount(0, HER_STRAIGHT)        ==  65508);
	assert(table->getCount(0, HER_THREE_OF_A_KIND) ==  92004);
	assert(table->getCount(0, HER_TWO_PAIRS)       == 469092);
	assert(table->getCount(0, HER_PAIR)            == 916776);
	assert(table->getCount(0, HER_HIGH_CARD)       == 386130);
	printf("checkTable1Player PASSED\n");
}

void checkTable2Players(){
	Table* table = new Table();
	table->addWholeCards(C1H, C2H);
	table->addWholeCards(C1D, C2D);

	table->evaluate();
	for (int j=0; j<2; j++){
		for (int i=0; i<TER_UNDECIDED+1; i++){
			printf("Player%d: count[%d]:%d\n", j, j, table->getCount(j, i));
		}
		printf("\n");
	}
	for (int j=0; j<2; j++){
		assert(table->getCount(j, HER_ROYAL_FLUSH)     ==     46);
		assert(table->getCount(j, HER_STRAIGHT_FLUSH)  ==   1020);
		assert(table->getCount(j, HER_FOUR_OF_A_KIND)  ==    484);
		assert(table->getCount(j, HER_FULL_HOUSE)      ==  19052);
		assert(table->getCount(j, HER_FLUSH)           == 124532);
		assert(table->getCount(j, HER_STRAIGHT)        ==  60028);
		assert(table->getCount(j, HER_THREE_OF_A_KIND) ==  50676);
		assert(table->getCount(j, HER_TWO_PAIRS)       == 308924);
		assert(table->getCount(j, HER_PAIR)            == 761412);
		assert(table->getCount(j, HER_HIGH_CARD)       == 386130);
	}
	printf("checkTable2Players PASSED\n");
}

void checkStraightFlushCompareH1gtH2(){
	Table* t = new Table();
	t->addWholeCards(C6D, CTH);
	t->addWholeCards(C3D, C5H);

	t->addBoardCard(new Card(C7H));
	t->addBoardCard(new Card(C6H));
	t->addBoardCard(new Card(C9H));
	t->addBoardCard(new Card(C8H));
	t->addBoardCard(new Card(CQD));

	t->evaluateHandsWithBoard();
	assert(t->getCount(0, HER_STRAIGHT_FLUSH)==1);
	assert(t->getCount(1, HER_STRAIGHT_FLUSH)==1);
	assert(t->getCount(0, TER_TIE)==0);
	assert(t->getCount(1, TER_TIE)==0);
	assert(t->getCount(0, TER_WIN)==1);
	assert(t->getCount(1, TER_WIN)==0);
	assert(t->getCount(0, TER_LOSE)==0);
	assert(t->getCount(1, TER_LOSE)==1);
	assert(t->getCount(0, TER_UNDECIDED)==0);
	assert(t->getCount(1, TER_UNDECIDED)==0);
	printf("checkStraightFlushCompareH1gtH2 PASSED\n");
}

void checkStraightFlushCompareH1eqH2(){
	Table* t = new Table();
	t->addWholeCards(C6H, C9H);
	t->addWholeCards(C3D, C5D);

	t->addBoardCard(new Card(CJS));
	t->addBoardCard(new Card(C8S));
	t->addBoardCard(new Card(CTS));
	t->addBoardCard(new Card(C9S));
	t->addBoardCard(new Card(CQS));

	t->evaluateHandsWithBoard();
	assert(t->getCount(0, HER_STRAIGHT_FLUSH)==1);
	assert(t->getCount(1, HER_STRAIGHT_FLUSH)==1);
	assert(t->getCount(0, TER_TIE)==1);
	assert(t->getCount(1, TER_TIE)==1);
	assert(t->getCount(0, TER_WIN)==0);
	assert(t->getCount(1, TER_WIN)==0);
	assert(t->getCount(0, TER_LOSE)==0);
	assert(t->getCount(1, TER_LOSE)==0);
	assert(t->getCount(0, TER_UNDECIDED)==0);
	assert(t->getCount(1, TER_UNDECIDED)==0);
	printf("checkStraightFlushCompareH1eqH2 PASSED\n");
}

void check4ofAKindCompareH1gtH2_4ak(){
	Table* t = new Table();
	t->addWholeCards(C6H, C6C);
	t->addWholeCards(C2H, C2D);

	t->addBoardCard(new Card(C6S));
	t->addBoardCard(new Card(C6D));
	t->addBoardCard(new Card(C2S));
	t->addBoardCard(new Card(C2C));
	t->addBoardCard(new Card(C1S));

	t->evaluateHandsWithBoard();
	assert(t->getCount(0, HER_FOUR_OF_A_KIND)==1);
	assert(t->getCount(1, HER_FOUR_OF_A_KIND)==1);
	assert(t->getCount(0, TER_TIE)==0);
	assert(t->getCount(1, TER_TIE)==0);
	assert(t->getCount(0, TER_WIN)==1);
	assert(t->getCount(1, TER_WIN)==0);
	assert(t->getCount(0, TER_LOSE)==0);
	assert(t->getCount(1, TER_LOSE)==1);
	assert(t->getCount(0, TER_UNDECIDED)==0);
	assert(t->getCount(1, TER_UNDECIDED)==0);
	printf("check4ofAKindCompareH1gtH2_4ak PASSED\n");
}

void check4ofAKindCompareH1gtH2_hc(){
	Table* t = new Table();
	t->addWholeCards(CTH, CKC);
	t->addWholeCards(C9S, C2D);

	t->addBoardCard(new Card(C6S));
	t->addBoardCard(new Card(C6D));
	t->addBoardCard(new Card(C6C));
	t->addBoardCard(new Card(C6H));
	t->addBoardCard(new Card(C5S));

	t->evaluateHandsWithBoard();
	assert(t->getCount(0, HER_FOUR_OF_A_KIND)==1);
	assert(t->getCount(1, HER_FOUR_OF_A_KIND)==1);
	assert(t->getCount(0, TER_TIE)==0);
	assert(t->getCount(1, TER_TIE)==0);
	assert(t->getCount(0, TER_WIN)==1);
	assert(t->getCount(1, TER_WIN)==0);
	assert(t->getCount(0, TER_LOSE)==0);
	assert(t->getCount(1, TER_LOSE)==1);
	assert(t->getCount(0, TER_UNDECIDED)==0);
	assert(t->getCount(1, TER_UNDECIDED)==0);
	printf("check4ofAKindCompareH1gtH2_hc PASSED\n");
}

void check4ofAKindCompareH1etH2(){
	Table* t = new Table();
	t->addWholeCards(CTH, CKC);
	t->addWholeCards(C9S, C2D);

	t->addBoardCard(new Card(C6S));
	t->addBoardCard(new Card(C6D));
	t->addBoardCard(new Card(C6C));
	t->addBoardCard(new Card(C6H));
	t->addBoardCard(new Card(C1S));

	t->evaluateHandsWithBoard();
	assert(t->getCount(0, HER_FOUR_OF_A_KIND)==1);
	assert(t->getCount(1, HER_FOUR_OF_A_KIND)==1);
	assert(t->getCount(0, TER_TIE)==0);
	assert(t->getCount(1, TER_TIE)==0);
	assert(t->getCount(0, TER_WIN)==1);
	assert(t->getCount(1, TER_WIN)==0);
	assert(t->getCount(0, TER_LOSE)==0);
	assert(t->getCount(1, TER_LOSE)==1);
	assert(t->getCount(0, TER_UNDECIDED)==0);
	assert(t->getCount(1, TER_UNDECIDED)==0);
	printf("check4ofAKindCompareH1etH2 PASSED\n");
}

void check4ofAKindCompareH1etH2_hand(){
	Table* t = new Table();
	t->addWholeCards(CTH, C1C);
	t->addWholeCards(C9S, C1D);

	t->addBoardCard(new Card(C6S));
	t->addBoardCard(new Card(C6D));
	t->addBoardCard(new Card(C6C));
	t->addBoardCard(new Card(C6H));
	t->addBoardCard(new Card(C3S));

	t->evaluateHandsWithBoard();
	assert(t->getCount(0, HER_FOUR_OF_A_KIND)==1);
	assert(t->getCount(1, HER_FOUR_OF_A_KIND)==1);
	assert(t->getCount(0, TER_TIE)==0);
	assert(t->getCount(1, TER_TIE)==0);
	assert(t->getCount(0, TER_WIN)==1);
	assert(t->getCount(1, TER_WIN)==0);
	assert(t->getCount(0, TER_LOSE)==0);
	assert(t->getCount(1, TER_LOSE)==1);
	assert(t->getCount(0, TER_UNDECIDED)==0);
	assert(t->getCount(1, TER_UNDECIDED)==0);
	printf("check4ofAKindCompareH1etH2_hand PASSED\n");
}

void checkFullHousCompareH1etH2(){
	Table* t = new Table();
	t->addWholeCards(CKH, CKC);
	t->addWholeCards(C9S, C9D);

	t->addBoardCard(new Card(CKS));
	t->addBoardCard(new Card(C9C));
	t->addBoardCard(new Card(CTC));
	t->addBoardCard(new Card(CTH));
	t->addBoardCard(new Card(C1S));

	t->evaluateHandsWithBoard();
	assert(t->getCount(0, HER_FULL_HOUSE)==1);
	assert(t->getCount(1, HER_FULL_HOUSE)==1);
	assert(t->getCount(0, TER_TIE)==0);
	assert(t->getCount(1, TER_TIE)==0);
	assert(t->getCount(0, TER_WIN)==1);
	assert(t->getCount(1, TER_WIN)==0);
	assert(t->getCount(0, TER_LOSE)==0);
	assert(t->getCount(1, TER_LOSE)==1);
	assert(t->getCount(0, TER_UNDECIDED)==0);
	assert(t->getCount(1, TER_UNDECIDED)==0);
	printf("checkFullHousCompareH1etH2 PASSED\n");
}

void checkFullHousCompareH1etH2_2nd(){
	Table* t = new Table();
	t->addWholeCards(CJH, CQD);
	t->addWholeCards(CJS, CTC);

	t->addBoardCard(new Card(CJC));
	t->addBoardCard(new Card(CJD));
	t->addBoardCard(new Card(CTS));
	t->addBoardCard(new Card(CQH));
	t->addBoardCard(new Card(C1S));

	t->evaluateHandsWithBoard();
	assert(t->getCount(0, HER_FULL_HOUSE)==1);
	assert(t->getCount(1, HER_FULL_HOUSE)==1);
	assert(t->getCount(0, TER_TIE)==0);
	assert(t->getCount(1, TER_TIE)==0);
	assert(t->getCount(0, TER_WIN)==1);
	assert(t->getCount(1, TER_WIN)==0);
	assert(t->getCount(0, TER_LOSE)==0);
	assert(t->getCount(1, TER_LOSE)==1);
	assert(t->getCount(0, TER_UNDECIDED)==0);
	assert(t->getCount(1, TER_UNDECIDED)==0);
	printf("checkFullHousCompareH1etH2_2nd PASSED\n");
}

void checkAKvsTT(){
	Table* table = new Table();
	table->addWholeCards(C1H, CKH);
	table->addWholeCards(CTC, CTS);

	table->evaluate();
	for (int j=0; j<2; j++){
		for (int i=0; i<TER_UNDECIDED+1; i++){
			printf("Player%d: count[%d]:%d (%2.02f%%)\n", j, i, table->getCount(j, i), (100.0*table->getCount(j, i))/1712304.0);
		}
		printf("\n");
	}
//	for (int j=0; j<2; j++){
//		assert(table->getCount(j, HER_ROYAL_FLUSH)     ==     46);
//		assert(table->getCount(j, HER_STRAIGHT_FLUSH)  ==   1020);
//		assert(table->getCount(j, HER_FOUR_OF_A_KIND)  ==    484);
//		assert(table->getCount(j, HER_FULL_HOUSE)      ==  19052);
//		assert(table->getCount(j, HER_FLUSH)           == 124532);
//		assert(table->getCount(j, HER_STRAIGHT)        ==  60028);
//		assert(table->getCount(j, HER_THREE_OF_A_KIND) ==  50676);
//		assert(table->getCount(j, HER_TWO_PAIRS)       == 308924);
//		assert(table->getCount(j, HER_PAIR)            == 761412);
//		assert(table->getCount(j, HER_HIGH_CARD)       == 386130);
//	}
	printf("checkTable2Players PASSED\n");
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
//	checkTable1Player();
//	checkTable2Players();
//	checkStraightFlushCompareH1gtH2();
//	checkStraightFlushCompareH1eqH2();
//	check4ofAKindCompareH1gtH2_4ak();
//	check4ofAKindCompareH1gtH2_hc();
//	check4ofAKindCompareH1etH2();
//	check4ofAKindCompareH1etH2_hand();
//	checkFullHousCompareH1etH2();
//	checkFullHousCompareH1etH2_2nd();
	checkAKvsTT();

	printf("Done\n");


	return 0;
}
