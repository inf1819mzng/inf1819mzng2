/*
 ============================================================================
 Name        : BMI.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SOGLIA_ETA 40 			// valore soglia under/over
#define BMI_SOVRAPPESO 25   // valore soglia BMI
#define CAMPIONE 10				 // numero individui

#define MIN_ETA 15			  // range di lavori per la generazione random
#define MAX_ETA 80
#define MIN_ALTEZZA 150
#define MAX_ALTEZZA 200
#define MIN_PESO 50
#define MAX_PESO 100

int main() {
  int max_altezza_over = 0;    // variabili per memorizzare i valori massimi
  int max_peso_over = 0;
  int max_altezza_under = 0;
  int max_peso_under = 0;

  float somma_BMI_over = 0; 	// variabili di appoggio per il calcolo della media
  float somma_BMI_under = 0;
  int numero_under = 0;
  int numero_over = 0;
  float media_BMI_over = 0.0;
  float media_BMI_under = 0.0;

  int eta = 0;  // variabili locali
  int peso = 0;
  int altezza = 0;

  float BMI = 0.0;

  int seed = time(NULL); // randomizzazione del seed
	srand(seed);

	for(unsigned int i=0; i<CAMPIONE; i++)
	{

		eta = rand() % (MAX_ETA-MIN_ETA+1) + MIN_ETA;  // generazione di valori nel range
		altezza = rand() % (MAX_ALTEZZA-MIN_ALTEZZA+1) + MIN_ALTEZZA; // altezza espressa in cm
		peso = rand() % (MAX_PESO-MIN_PESO+1) + MIN_PESO; //peso espresso in kg

		BMI = peso / ( (float) altezza/100*altezza/100);  // calcolo del BMI

		// stampa dei valori
		printf("Eta: %d \t Altezza: %d m\t Peso: %d kg \t BMI: %.2f\n", eta, altezza, peso, BMI);

		if(eta>=SOGLIA_ETA)
		{  // biforcazione del programma in base all'età
			if(altezza > max_altezza_over)
			{  // aggiornamento eventuale dell'altezza massima
				max_altezza_over = altezza;
			}
			if(peso > max_peso_over) {
				max_peso_over = peso;
			}

			somma_BMI_over += BMI;
			numero_over++;

		}
		else
		{
			if(altezza > max_altezza_under)
			{ // aggiornamento eventuale dell'altezza massima
				max_altezza_under = altezza;
			}
			if(peso > max_peso_under)
			{ // aggiornamento eventuale del peso massimo
				max_peso_under = peso;
			}

			somma_BMI_under += BMI; // somma per il calcolo successivo della media
			numero_under++;
		}

	}

  if(numero_over > 0) { // programmazione difensiva
  	media_BMI_over = somma_BMI_over / numero_over;  //media del BMI

  	// stampe di output
  	printf("\nI valori massimi di altezza e peso per gli Over 40 sono %d e %d\n", max_altezza_over, max_peso_over);
  	printf("Il valore medio di BMI per gli Over 40 è %.2f, ", media_BMI_over);

  	if(media_BMI_over > BMI_SOVRAPPESO)
    	printf("quindi possiamo affermare che il campione sia in sovrappeso.\n");
		else
    	printf("quindi possiamo affermare che il campione sia normopeso.\n");
  }


  if(numero_under > 0) { // programmazione difensiva
  		media_BMI_under = somma_BMI_under / numero_under;

  	 printf("\nI valori massimi di altezza e peso per gli Under 40 sono %d e %d\n", max_altezza_under, max_peso_under);
  	 printf("Il valore medio di BMI per gli Under 40 è %.2f, ", media_BMI_under);

    	if(media_BMI_under > BMI_SOVRAPPESO)
    		printf("quindi possiamo affermare che il campione sia in sovrappeso.\n");
  		else
    		printf("quindi possiamo affermare che il campione sia normopeso.\n");
  }
}
