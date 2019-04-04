/*
 ============================================================================
 Name        : Costo.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Scrivere un programma che conteggi il costo totale dei prodotti in un carrello.
               Non sappiamo quanti prodotti può contenere il carrello.

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float costo = 0; 		// variabile di tipo float
	float totale = 0;

	printf("\nInserisci il costo del prodotto (-1 per terminare): ");
	scanf("%f", &costo);

	while(costo != -1) {
		if (costo > 0)       //condizione per controllare che l'utente non abbia inserito un valore negativo diverso da -1
			totale = totale + costo;
		else
			printf ("Valore non valido, inserire il costo di un prodotto e -1 per terminare\n");

		printf("Inserisci il costo del prodotto: ");
		scanf("%f", &costo);
	}
	printf("Totale: %.2f\n", totale);
}

