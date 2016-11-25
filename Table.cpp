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


void Table::addBoardCard(Card* card) {
	for (int i=0; i<this->nPlayers; i++){
		this->playerHands[i]->accept(card);
	}
}

void Table::removeLast() {
	for (int i=0; i<this->nPlayers; i++){
		this->playerHands[i]->removeLast();
	}
}

void Table::evaluateHandsWithBoard(){
	int v;
	for (int i=0; i<this->nPlayers; i++){
		v = this->playerHands[i]->evaluate();
		count[i][v] += 1;
	}
}

void Table::evaluate(){
	Card* cards[52];
	for (int i=0; i<52; i++)
		cards[i] = new Card(i);

	bzero(count, sizeof(count));

	int nc = 52;

	int nHands = 0;

	for (int i=0; i< nc; i++){
		if (cardsInPlay[i]) continue;
		addBoardCard(cards[i]);
		for (int j=i+1; j< nc; j++){
			if (cardsInPlay[j]) continue;
			addBoardCard(cards[j]);
			for (int k=j+1; k< nc; k++){
				if (cardsInPlay[k]) continue;
				addBoardCard(cards[k]);
				for (int l=k+1; l< nc; l++){
					if (cardsInPlay[l]) continue;
					addBoardCard(cards[l]);
					for (int m=l+1; m< nc; m++){
						if (cardsInPlay[m]) continue;
						addBoardCard(cards[m]);
						evaluateHandsWithBoard();
						nHands += 1;
						removeLast();
					}
					removeLast();
				}
				removeLast();
			}
			removeLast();
		}
		removeLast();
	}

	printf("Number of hands:%d\n", nHands);
	for (int i = 0; i<10; i++) {
		printf("...count[%d] = %d\n", i, count[0][i]);
	}
}

int Table::getCount(int player, int countId){
	return count[player][countId];
}
