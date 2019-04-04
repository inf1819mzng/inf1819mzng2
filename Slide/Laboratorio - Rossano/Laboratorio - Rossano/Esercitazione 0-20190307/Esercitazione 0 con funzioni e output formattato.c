/*
 ============================================================================
 Name        : Marino.c
 Author      : Marino Giuseppe
 Version     : La versione sottomessa è stata leggermente modificata per introdurre anche
               la visualizzazione dei dati che mancava. Grazie anche alla studentessa
               Stolbovoi Nicole
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Secondo Wikipedia l'altezza può variare dai 135 ai 200 centimetri (+- 20% dell'altezza standard)
//
// Altezza massima
#define HMAX 200
// Altezza minima
#define HMIN 150

// Questi valori permettono di avere un BMI che varia dall'obesità al sottopeso
// tenendo conto dell'altezza minima e massima.
// Vi sono casi estremi, ma sono estremi
// Peso massimo in kg
#define PMAX 100
// Peso minimo in kg
#define PMIN 50

// Età massima
// Il professor Farnsworth avrà almeno 160, ma restiamo nel reale
#define EMAX 80
// Età minima
#define EMIN 15

// Quante persone random devo generare?
#define RPGEN 10

/*
    I valori di altezza, peso ed età sono generati random
    poichè la funzione rand() ritorna un valore intero
    i dati verranno salvati sotto tipo unsigned int e normalizzati in seguito
*/

typedef struct {
    unsigned int altezza; // espressa in centimetri
    unsigned int peso;    // espresso in kgrammi
    unsigned short eta;   // espresso in anni
    float bmi;
} persona_t;

// Genera un intero pseudorandom x con min <= x <= max
int myrng(int min, int max);

// Genera una persona random
persona_t prandom();
// Stampa dati generati
void view_data(persona_t p, int index);

// Calcola l'indice di massa corporea
// Peso in grammi, altezza in centimetri
float calcBMI(unsigned int peso, unsigned int altezza);

// Ritorna il massimo tra A e B
int max(int a, int b);

// Stampa le statistiche
void printStats(float BMI, unsigned int pmax, unsigned int hmax);

int main()
{
    unsigned int pmaxOver = 0, pmaxUnder = 0, hmaxOver = 0, hmaxUnder = 0, over = 0, under = 0, i = 0;
    float BMIOver = 0, BMIUnder = 0;
    persona_t persona;
    // Inizializzo il seed per l'rng
    srand(time(0));
    puts("Campione da analizzare:");
    puts("----+-----+--------+--------");
    puts(" N. | Age | Height | Weight");
    puts("----+-----+--------+--------");
    // Generazione delle persone random
    for (i = 0; i < RPGEN; i++) {
    	persona = prandom();

    	view_data (persona, i);
        if (persona.eta < 40) { // Under 40
            pmaxUnder = max(pmaxUnder, persona.peso);
            hmaxUnder = max(hmaxUnder, persona.altezza);
            BMIUnder += persona.bmi;
            under++;
        } else { // Over 40
            pmaxOver = max(pmaxOver, persona.peso);
            hmaxOver = max(hmaxOver, persona.altezza);
            BMIOver += persona.bmi;
            over++;
        }
    }


    if (under) {
        printf("\nStatistiche under 40:\n\t");
        printStats(BMIUnder/under, pmaxUnder, hmaxUnder);
    }

    if (over) {
        printf("\nStatistiche over 40:\n\t");
        printStats(BMIOver/over, pmaxOver, hmaxOver);
    }

    return 0;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int myrng(int min, int max)
{
    return (rand()%(max-min+1))+min;
}

float calcBMI(unsigned int peso, unsigned int altezza)
{
    return (peso)/((float)altezza/100*altezza/100);
}

persona_t prandom()
{
    persona_t rpers;
    rpers.eta = myrng(EMIN, EMAX);
    rpers.altezza = myrng(HMIN, HMAX);
    rpers.peso = myrng(PMIN, PMAX);
    rpers.bmi = calcBMI(rpers.peso, rpers.altezza);
    return rpers;
}

void printStats(float BMI, unsigned int pmax, unsigned int hmax)
{
        printf("Altezza massima: %.2f cm\n\t", (float)hmax);
        printf("Peso massimo: %.1f Kg\n\t", (float)pmax);
        printf("BMI medio: %.2f\n\t", BMI);
        printf("Il campione risulta mediamente ");
        if (BMI <= 18.0f) {
            printf("sottopeso\n\n");
        } else if (BMI <= 25.0f) {
            printf("normopeso\n\n");
        } else if (BMI <= 30.0f) {
            printf("sovrappeso\n\n");
        } else {
            printf("obeso\n\n");
        }
}

void view_data(persona_t persona, int index) {
		printf("%3d | %3d | %6d | %6d\n"
				,index+1
				,persona.eta
				,persona.altezza
				,persona.peso
		);
	puts("----+-----+--------+--------");

}
