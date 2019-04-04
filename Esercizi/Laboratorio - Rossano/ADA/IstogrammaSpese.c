/* Programma per la gestione di un conto spese */

#include <stdio.h>

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	char scelta=' ';
	float contospese[4]={0.0};
	float spesa =0.0;
	float totale=0.0;
	int i,percentuale=0;
	char simbolo=' ';
      do
      {
    	  /* Stampa a video del menù di scelta */
        printf("\n\n\nC - Cancelleria\n");
        printf("T - Telefono\n");
        printf("E - Elettricita\'\n");
        printf("A - Altro\n");
        printf("S - Statistiche\n");
        printf("X - Uscita dal programma\n\n");
        printf("Effettuare una scelta: ");

        scanf("\n%c", &scelta);
        /* Selezione dell'operazione da effettuare */
        switch (scelta) {
          case 'c': case 'C':
            printf("\nSpese cancelleria - Importo: ");
            scanf("%f",&spesa);
            contospese[0]+=spesa;
            break;
          case 't': case 'T':
            printf("\nSpese telefoniche - Importo: ");
            scanf("%f",&spesa);
            contospese[1]+=spesa;
            break;
          case 'e': case 'E':
            printf("\nSpese elettricita\' - Importo: ");
            scanf("%f",&spesa);
            contospese[2]+=spesa;
            break;
          case 'a': case 'A':
            printf("\nSpese diverse - Importo: ");
            scanf("%f",&spesa);
            contospese[3]+=spesa;
            break;
          case 's': case 'S':
          {
        	  totale=contospese[0]+contospese[1]+contospese[2]+contospese[3];

        	  if (totale==0)
        		  printf ("\nNon sono state effettuate spese.\n");
        	  else
        	  {
        		  /* Visualizzazione del riepilogo */
        		  printf("\n\nRIEPILOGO SPESE:\n");
        		  printf("Cancelleria:  %10.2f\n",contospese[0]);
         		  printf("Telefono:     %10.2f\n",contospese[1]);
        		  printf("Elettricita': %10.2f\n",contospese[2]);
        		  printf("Altro:        %10.2f\n",contospese[3]);
        		  /* Visualizzazione delle statistiche */
        		  printf("\nSTATISTICHE SPESE:\n");

        		  for (i=0; i<=3;i++)
        		  { /* Individuazione della voce di spesa da rappresentare */
        			  switch (i) {
        			  case 0: printf("C: "); simbolo='+'; break;
        			  case 1: printf("T: "); simbolo='-'; break;
        			  case 2: printf("E: "); simbolo='*'; break;
        			  case 3: printf("A: "); simbolo='o';
        			  };

        			  /* Calcolo e rappresentazione della percentuale di spesa */
        			  percentuale=contospese[i]*100/totale;

        			  while (percentuale>0) /* il ciclo serve a rappresentare graficamente
        				                           lo stato corrente della spesa attraverso istogrammi
        				                           orizzontali. Ogni simbolo rappresenta 2 punti percentuali*/
        			  {
        				  if (percentuale>1)
        					  printf("%c",simbolo);
        				  percentuale-=2;
        			  }
        			  printf("\n");
        		  }
              }
            }
            break;
          case 'x': case 'X':
            break;
          default:
            printf("\nQualcosa non ha funzionato. Le scelte possibili sono quelle indicate nel menu\'\n\n");
        }

      }
      while ((scelta!='X')&&(scelta!='x'));
      return 0;
}
