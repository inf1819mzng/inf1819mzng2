/*  
   Implementazione di automi DFA per il riconoscmento di linguaggi regolari
   v 1.3 - 16/05/2006
   Corrado Mencar
   
   History:
           1.0 (11/04/2005): Prima release
           1.1 (11/04/2005): inserita fclose(...) e #define
           1.2 (22/04/2005): aggiunto test su fgets
           1.3 (16/05/2006): aggiunto system("PAUSE") su controllo file
         
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100

int scan(char* s)
{
 enum {S,A,B,C,D,E,G,H,POZZA} current_state = S;
 int i = 0;
 
 while ((s[i]!='\0' && s[i]!='\n') && current_state != POZZA)
 {
  switch(current_state)
  {
   case S:
        if (s[i]=='+' || s[i]=='-')
           current_state = A;
        else if (s[i]=='0')
             current_state = B;
        else if (s[i] >= '1' && s[i] <= '9')
             current_state = C;
        else
            current_state = POZZA;
        break;
   case A:
        if (s[i] >= '1' && s[i] <= '9')
             current_state = C;
        else
            current_state = POZZA;
        break;        
   case B:
        current_state = POZZA;
   case C:
        if (s[i]=='.')
           current_state = D;
        else if (s[i]=='e' || s[i]=='E')
             current_state = E;
        else
            current_state = POZZA;
        break;
   case D:
        if (s[i]=='e' || s[i]=='E')
           current_state = E;
        else if (s[i] >= '0' && s[i] <= '9')
             current_state = D;
        else
            current_state = POZZA;
        break;
   case E:
        if (s[i]=='+' || s[i]=='-')
           current_state = H;
        else if (s[i] >= '0' && s[i] <= '9')
             current_state = G;
        else
            current_state = POZZA;
        break;
   case H:
        if (s[i] >= '0' && s[i] <= '9')
             current_state = G;
        else
            current_state = POZZA;
        break;   
   case G:
        if (s[i] >= '0' && s[i] <= '9')
             current_state = G;
        else
            current_state = POZZA;
        break;                
  }
  ++i;
 }
 return (current_state == B || current_state == G);
}



int main(int argc, char* argv[])
{
 char buffer[MAX_LENGTH+1];
 char* filename = argv[1];
 FILE* file;
 
 file = fopen(filename,"r");
 if (file == NULL)
 {
      printf("file inesistente");
      system("PAUSE");
      return -1;
 }

    
 while (!feof(file))
 {
  if (fgets(buffer,MAX_LENGTH,file))
     if (scan(buffer))
        printf("%s RICONOSCIUTO\n", buffer);
     else
         printf("%s NON RICONOSCIUTO\n", buffer);
 }
 
 fclose(file);
 system("PAUSE");
 return 0;
}
