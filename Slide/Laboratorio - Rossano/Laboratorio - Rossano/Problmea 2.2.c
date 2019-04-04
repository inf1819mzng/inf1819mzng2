/*
 ============================================================================
 Name        : Problema 2.2.c
 Author      : Cataldo Musto (con qualche variazione)
 Version     :
 Copyright   : Your copyright notice
 Description : Definire una variabile “archivio” come un array di cinque film.
               Ciascun film deve essere rappresentato come una struct composta dai seguenti campi: nome del film, genere, data di uscita, durata
			   Nome e genere sono array di caratteri, la durata è un valore intero. La data deve essere a sua volta una struct composta da mese e anno

				Scrivere un programma che acquisisca i dati in input per ciascuno dei cinque film e li mostri sullo schermo.

				N.B. Il programma non esegue controlli sull'input.
 ============================================================================
 */

#include "stdio.h"
#define NUM_FILMS 5 // numero dei film
#define MAX_LUNGHEZZA_TITOLO 10 // lunghezza titolo massima
#define MAX_LUNGHEZZA_GENERE 10 // lunghezza genere massima
typedef struct { // struct DATA
	unsigned int mese;
	unsigned int anno;
} data;

typedef struct { // struct PERSONA
	char titolo[MAX_LUNGHEZZA_TITOLO];
	char genere[MAX_LUNGHEZZA_GENERE];
	data uscita; // NOTA: struct come membro di una struct
	unsigned int durata;
} film;


int main() {
	film archivio[NUM_FILMS]= {{"","", {0,0}, 0}}; // variabile archivio
	// Acquisizione input
	for(unsigned int i=0; i<NUM_FILMS; i++) {
		printf("Film n.%d Inserisci titolo:", i+1);
	//	fgets(archivio[i].titolo,sizeof(archivio[i].titolo),stdin); // per accettare spazi
		scanf("%15s", archivio[i].titolo); //NOTA: non accetta spazi
		printf("Film n.%d Inserisci genere:", i+1);
		scanf("%10s", archivio[i].genere); //NOTA: non accetta spazi
		printf("Film n.%d Inserisci mese di pubblicazione:", i+1);
		scanf("%u", &archivio[i].uscita.mese);
		printf("Film n.%d Inserisci anno di pubblicazione:", i+1);
		scanf("%u", &archivio[i].uscita.anno);
		printf("Film n.%d Inserisci durata:", i+1);
		scanf("%u", &archivio[i].durata);
	}
	// Ciclo di Stampa
	for(unsigned int j=0; j<NUM_FILMS; j++) {
		printf("\n%s\t%s\t%u/%u\t%u\n", archivio[j].titolo, archivio[j].genere, archivio[j].uscita.mese, archivio[j].uscita.anno, archivio[j].durata);
	}
}
