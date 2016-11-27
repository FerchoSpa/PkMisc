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
	for (int i=0; i<nPlayers; i++){
		v = playerHands[i]->evaluate();
		count[i][v] += 1;
		handResults[i] = v;
	}
	// Evaluate only player 0 and 1
	if (handResults[0]<handResults[1]){
		count[0][TER_WIN]  += 1;
		count[1][TER_LOSE] += 1;
	} else if (handResults[1]<handResults[0]){
		count[1][TER_WIN]  += 1;
		count[0][TER_LOSE] += 1;
	} else {
		if (handResults[0] == HER_STRAIGHT_FLUSH){
			int v1 = playerHands[0]->getHighCardOnStraightFlush();
			int v2 = playerHands[1]->getHighCardOnStraightFlush();
			if (v1 == v2) {
				count[0][TER_TIE] += 1;
				count[1][TER_TIE] += 1;
			} else if (v1>v2) {
				count[0][TER_WIN]  += 1;
				count[1][TER_LOSE] += 1;
			} else {
				count[1][TER_WIN]  += 1;
				count[0][TER_LOSE] += 1;
			}
		} else if(handResults[0] == HER_FOUR_OF_A_KIND) {
			int c1 = playerHands[0]->getMostRepeatedCard();
			int c2 = playerHands[1]->getMostRepeatedCard();
			Card* hc1 = playerHands[0]->getHighCardInReverseOrder(0);
			Card* hc2 = playerHands[1]->getHighCardInReverseOrder(0);
			if (c1>c2 || (c1==c2 && hc1->getNumericRank()>hc2->getNumericRank())) {
				count[0][TER_WIN]  += 1;
				count[1][TER_LOSE] += 1;
			} else if (c2>c1 || (c1==c2 && hc2->getNumericRank()>hc1->getNumericRank())) {
				count[1][TER_WIN]  += 1;
				count[0][TER_LOSE] += 1;
			} else {
				count[0][TER_TIE] += 1;
				count[1][TER_TIE] += 1;
			}
		} else if(handResults[0] == HER_FULL_HOUSE) {
			int c1 = playerHands[0]->getMostRepeatedCard();
			int c2 = playerHands[1]->getMostRepeatedCard();
			int d1 = playerHands[0]->get2ndMostRepeatedCard();
			int d2 = playerHands[1]->get2ndMostRepeatedCard();
			if (c1>c2 || (c1==c2 && d1>d2)) {
				count[0][TER_WIN]  += 1;
				count[1][TER_LOSE] += 1;
			} else if (c2>c1 || (c1==c2 && d2>d1)) {
				count[1][TER_WIN]  += 1;
				count[0][TER_LOSE] += 1;
			} else {
				count[0][TER_TIE] += 1;
				count[1][TER_TIE] += 1;
			}
		} else {
			count[0][TER_UNDECIDED]  += 1;
			count[1][TER_UNDECIDED]  += 1;
		}
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
}

int Table::getCount(int player, int countId){
	return count[player][countId];
}
