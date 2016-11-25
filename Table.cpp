#include "Table.h"

#include <stdio.h>

Table::Table() {
	nPlayers = 0;
	bzero(cardsInPlay, sizeof(cardsInPlay));
}


void Table::addWholeCards(int c0, int c1) {
	Hand* h;
	h = new Hand();
	h->accept(new Card(c0));
	h->accept(new Card(c1));
	h->showCards();
	playerHands[nPlayers] = h;
	nPlayers += 1;
	cardsInPlay[c0] = 1;
	cardsInPlay[c1] = 1;
}

int* Table::evaluate(){

	int v;
	Card* cards[52];
	for (int i=0; i<52; i++)
		cards[i] = new Card(i);

	bzero(count, sizeof(count));

	int nc = 52;

	int nHands = 0;

	Hand* h = playerHands[0];
	for (int i=0; i< nc; i++){
		if (cardsInPlay[i]) continue;
		h->accept(cards[i]);
		for (int j=i+1; j< nc; j++){
			if (cardsInPlay[j]) continue;
			h->accept(cards[j]);
			for (int k=j+1; k< nc; k++){
				if (cardsInPlay[k]) continue;
				h->accept(cards[k]);
				for (int l=k+1; l< nc; l++){
					if (cardsInPlay[l]) continue;
					h->accept(cards[l]);
					for (int m=l+1; m< nc; m++){
						if (cardsInPlay[m]) continue;
						h->accept(cards[m]);
						v = h->evaluate();
						count[0][v] += 1;
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
		printf("...count[%d] = %d\n", i, count[0][i]);
	}

	return count[0];

}
