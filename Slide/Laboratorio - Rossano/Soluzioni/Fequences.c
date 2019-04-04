/*
 ============================================================================
 Name        : Fequences.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "stdio.h"
	#define RESPONSE_SIZE 20
    #define FREQUENCY_SIZE 5

	int main(void) {
		int rating = 0; // variabili contatore
 		int answer = 0;
		int frequency[FREQUENCY_SIZE] = {0}; // inizializziamo il vettore
		int responses[RESPONSE_SIZE] = {5, 1, 2, 4, 2, 3, 1, 1, 5, 2, 2, 2, 1, 4, 4, 2, 2, 4, 1, 4};


 	 	for (answer = 0; answer < RESPONSE_SIZE; answer++) {
 		 	frequency[ responses[answer]-1 ]++;
 	 	}

 	 	for (rating = 0; rating < FREQUENCY_SIZE; rating++) {
 		 	printf("Rating: %d \t Number: %d \n", rating+1, frequency[rating]);
 	 	}
 		return 0;
 	}
