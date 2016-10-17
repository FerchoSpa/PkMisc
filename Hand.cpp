#include "Hand.h"

#include <stdio.h>



Hand::Hand() {
	printf("Creating Hand\n");
}

char* Hand::toString() {
	return NULL;
}


void Hand::accept(Card* c){
	printf("List size:%ld\n", mylist.size());
	mylist.push_back(c);
	printf("List size:%ld\n", mylist.size());
}
