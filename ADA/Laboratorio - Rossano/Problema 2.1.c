/*
 ============================================================================
 Name        : 1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Scrivere un programma che calcoli la media delle calorie assunte
 	 	 	   in una settimana. Requisiti: utilizzare un array

 ============================================================================
 */

#include "stdio.h"
	#define GIORNI_SETTIMANA 7 // costanti simboliche

int main(void) {
	int calorie[GIORNI_SETTIMANA]; // vettore delle calorie
	int somma_calorie = 0; // variabili locali
	float media_calorie = 0.0;

	// ciclo di inizializzazione
	for(int i=0; i<GIORNI_SETTIMANA; i++) {
		calorie[i] = 0;
	}
	// ciclo di acquisizione ed elaborazione
	for(int i=0; i<GIORNI_SETTIMANA; i++) {

		// programmazione difensiva - controlla valori di input non corretti
		while(calorie[i] <= 0) {
			printf("\nInserire calorie assunte il giorno %d: ", i+1);
			scanf("%d",&calorie[i]);

			if(calorie[i] <= 0) // mostra un messaggio d'errore
				printf("\nInserire un valore valido\n");
			else  // altrimenti registra il valore
				somma_calorie = somma_calorie + calorie[i];
		}
	}

	media_calorie = (float) somma_calorie / GIORNI_SETTIMANA;
	printf("\n Media calorie assunte: %.2f", media_calorie);
}
