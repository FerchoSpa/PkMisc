#include "BoardsBuilder.h"

#include <stdio.h>

BoardsBuilder::BoardsBuilder() {
}

void BoardsBuilder::buildBoards(int* wholeCardsBitmap) {
	int count = 0;
	for (int i=0; i<52; i++) {
		if (wholeCardsBitmap[i]) continue;
		for (int j=i+1; j<52; j++) {
			if (wholeCardsBitmap[i]) continue;
			for (int k=j+1; k<52; k++) {
				if (wholeCardsBitmap[i]) continue;
				for (int l=k+1; l<52; l++) {
					if (wholeCardsBitmap[i]) continue;
					for (int m=l+1; m<52; m++) {
						if (wholeCardsBitmap[i]) continue;
						count += 1;
					}
				}
			}
		}
	}
	printf ("BoardsBuilder::buildBoards count:%d\n", count);
}
