#include <stdio.h>
#include <assert.h>
// 0 1 2 3 4 5 6 7 8 9 0 1 2 (A-K H)
#include "Card.h"
#include "Hand.h"
#include "BoardsBuilder.h"

int main() {
	Card* c1 = new Card(3);  // 4H
	Card* c2 = new Card(23); // JD
	Card* c3 = new Card(7);  // 8H
	Card* c4 = new Card(13); // AD
	Card* c5 = new Card(26); // AS
	Card* c6 = new Card(39); // AC
	Card* c7 = new Card(35); // TS
	printf("c1:%s\n", c1->toString());
	printf("c2:%s\n", c2->toString());
	printf("c3:%s\n", c3->toString());
	printf("c4:%s\n", c4->toString());
	printf("c5:%s\n", c5->toString());
	printf("c6:%s\n", c6->toString());
	printf("c7:%s\n", c7->toString());

	Hand* h = new Hand();
	h->accept(c1);
	h->accept(c2);
	h->accept(c3);
	h->accept(c4);
	h->accept(c5);
	h->accept(c6);
	h->accept(c7);

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

	int wholeCards[52];
	bzero(wholeCards, sizeof(wholeCards));
	wholeCards[0] = 1;
	wholeCards[1] = 1;
	BoardsBuilder bb;
	bb.buildBoards(wholeCards);


	printf("Done\n");

	return 0;
}
