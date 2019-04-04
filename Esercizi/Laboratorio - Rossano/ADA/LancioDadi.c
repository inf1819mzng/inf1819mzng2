/*
 ============================================================================
 Name        : LancioDadi.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Il programma  simula il lancio di due dadi.
 	 	 	   Restituisce la frequenza della somma dei due valori su 36000 lanci.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_LANCI 36000
#define FACCIA_MAX 6
#define NUM_FREQUENZE 11 /* Le possibili frequenze sono 11 da 2 (se per entrambi i dadi appare 1)
							a 12 (se su entrambi i dadi appare 6)*/

int myrng(int max);
void stampaFrequenze(int frequenze[]);

int main(void) {

	int frequenzeSomma [NUM_FREQUENZE]={0}; //array delle frequenze delle somme
    int i;
    int sommaDadi=0; // somma dei dadi

    srand(time(0));

	for (i=0; i<NUM_LANCI; i++){
		sommaDadi=myrng(FACCIA_MAX)+myrng(FACCIA_MAX); //lancia i due dadi e fa direttamente la somma

		frequenzeSomma[sommaDadi-2]++; /*aggiorna il contatore dell'elemento dell'array somma-2
										(se la somma è 12 sarà incrementato l'elemento con indice 10 */

	}
	stampaFrequenze(frequenzeSomma);



}



int myrng(int max)
{
    return (rand()%(max)+1);
}
void stampaFrequenze(int frequenze[])
{
	int sommaFrequenze=0;
	float percentuale [NUM_FREQUENZE]={0.0};
	puts("\n********** Frequenza delle somme di 36000 lanci di due dadi ****\n\n");
	puts("\t2\t|\t3\t|\t4\t|\t5\t|\t6\t|\t7\t|\t8\t|\t9\t|\t10\t|\t11\t|\t12\t|");
	for (int i=0; i<NUM_FREQUENZE; i++){
		printf("\t%d\t|",frequenze[i]);
		sommaFrequenze+=frequenze[i];
		percentuale[i]=frequenze[i]/360;
	}
	printf("\n\nSono stati fatti %d lanci in cui:\n", sommaFrequenze);
	for (int i=0;i<NUM_FREQUENZE; i++){
		printf("\t- La somma %d è apparsa il %2.f%%  delle volte\n", i+2, percentuale[i]);
	}
}
