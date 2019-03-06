/* 
   GrammarReader
   v. 1.2.2
   Corrado Mencar, Pasquale Lops
*/

#include <stdio.h>

#define MAX_WORD_LENGTH 100
#define MAX_PRODUCTIONS 100

// Definizione dei tipi ------------------------------------------------------*/

typedef char Symbol;

typedef struct
{
        Symbol word [MAX_WORD_LENGTH];
        unsigned length;
} Word;

typedef struct
{
        Word left;
        Word right;
} Production;

typedef struct
{
        Production productions[MAX_PRODUCTIONS];
        unsigned numprod;
} Grammar;

// Procedure di riconoscimento dei simboli -----------------------------------*/

int is_terminal(Symbol s)
{
    return (islower(s));
    //return (s >= 'a') && (s <= 'z');
}

int is_nonterminal(Symbol s)
{
    return (isupper(s));
    //return (s >= 'A') && (s <= 'Z');
}

int is_prodsym(Symbol s)
{
    return (s == '>');
}

int is_prodsep(Symbol s)
{
    return (s == '\n');
}

/* Lettura di simboli da file ------------------------------------------------*/

Symbol read_sym(FILE* file)
{
       Symbol s;
       
       // fscanf(file,"%c",&s); 
       
       //questo ciclo permette di saltare la lettura di spazi tra i simboli
       do 
          s = getc(file);
       while (s==' ');
       
       return s;
}

Production* add_new_production(Grammar *g)
{
  Production* p;
  p = &(g->productions[g->numprod++]);
  p->left.length = 0;
  p->right.length = 0;
  
  return p;
}
                       

void add_symbol(Word *w, Symbol s)
{
  w->word[w->length++] = s;  
}


// Procedura di acquisizione di una grammatica da un file --------------------*/
                       
Grammar* load_grammar(FILE* file, Grammar* g)
{
         enum States {START,LEFT,RIGHT,ERROR};
         /*   START  = Scansione di una nuova produzione [F]
              LEFT   = Scansione della parte sinistra
              RIGHT  = Scansione della parte destra [F]
              ERROR  = Errore di scansione
         */
         enum States current_state = START;  // Stato iniziale
         Symbol s;
         Production* p;
         
         g->numprod = 0; // Inizializza la grammatica
                  
         while (current_state != ERROR && !feof(file)) 
         {
               s = read_sym(file);
               if (feof(file)) break;
               switch(current_state)
               {
               case START:
                    if (is_terminal(s) || is_nonterminal(s))
                    {
                       current_state = LEFT;
                       
                       //p = &(g->productions[g->numprod++]);
                       //p->left.length = 0;
                       p = add_new_production(g);
                       add_symbol(&p->left,s);
                       //L'istruzione precedente corrisponde a p->left.word[p->left.length++] = s;
                    }
                    else if (is_prodsep(s))
                    {
                       current_state = START;
                    }
                    else 
                         current_state = ERROR;
                    break;
               case LEFT:
                    if (is_terminal(s) || is_nonterminal(s))
                    {
                       current_state = LEFT;
                       add_symbol(&p->left,s);
                    }
                    else if (is_prodsym(s))
                    {
                       current_state = RIGHT;
                    }
                    else
                        current_state = ERROR;
                    break;
               case RIGHT:
                    if (is_terminal(s) || is_nonterminal(s))
                    {
                       current_state = RIGHT;
                       add_symbol(&p->right,s);
                    }
                    else if (is_prodsep(s))
                    {
                       current_state = START;
                    }
                    else 
                         current_state = ERROR;
                    break;
               }
         }
         
         if (current_state == START || current_state == RIGHT)
            return g;
         else
             return NULL;

}       

// Procedure di stampa

void print_sym (Symbol s)
{
     printf("%c ",s);
}


void print_word (Word* w)
{
     int i;
     
     for (i=0; i<w->length; i++)
         print_sym(w->word[i]);
}

void print_production (Production* p) 
{
     print_word(&p->left);
     printf (" --> ");
     print_word(&p->right);
}

void print_grammar(Grammar* g)
{
     int i;
     
     if (g == NULL)
        printf ("Errore! Grammatica non valida! \n");
     else
     {
        printf ("Numero di produzioni: %d\n", g->numprod);
        for (i=0; i<g->numprod; i++)
        {
            print_production(&g->productions[i]);
            printf ("\n");
        }
     }
}

// MAIN ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  char* filename = argv[1];
  FILE* gram_file;
  Grammar grammar;
  
  // controlla se è stato inserito il nome del file
  
  if (filename == 0)
  {
     printf("nome file non specificato \n");
     return -1;
  }
  
  // apertura del file contenente la grammatica
  
  gram_file = fopen(filename,"r");
  if (gram_file == NULL)
  {
     printf("nome di file errato\n");
     return -1;
  }
  
  print_grammar(load_grammar(gram_file,&grammar));
  
  fclose(gram_file);
  
  
  system("PAUSE");	
  return 0;
}


