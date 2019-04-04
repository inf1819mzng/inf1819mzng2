#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Costanti -----------------------------------------------------------------*/

#define MAX_STRING_LENGTH 40

/* Tipi di dati -------------------------------------------------------------*/

typedef char String[MAX_STRING_LENGTH+1];

typedef enum
{
 IDENTIFIER,
 KEYWORD,
 COMMENT,
 LEFT_PAR,
 RIGHT_PAR,
 PLUS,
 MINUS,
 ASTERIX,
 SLASH,
 EQUAL,
 SEMICOLON,
 DOT,
 COMMA,
 GREATER,
 GREATER_OR_EQUAL,
 LESS,
 LESS_OR_EQUAL,
 DIFFERENT,
 COLON,
 ASSIGNMENT,
 INTEGER,
 REAL,
 STRING,
 ERROR
} TokenType;

typedef struct
{
 TokenType type;
 String value;
} Token;

/* Variabili globali --------------------------------------------------------*/

char *keywords[]={"begin","boolean","char", "do", "else","end",
                    "false","for","if","integer","program","real", "repeat",
                    "then", "to", "true","until","var","while",NULL};
                    
/* Funzioni -----------------------------------------------------------------*/
                    
int is_keyword(String s)
{
    char* keyw = keywords[0];
    int i = 0;
    
    while (keywords[i]) if (strcmpi(keywords[i++],s)==0) return !0;
    
    return 0;
          
}

int getToken (FILE* src, Token* tkn)
{
 static char c;
 static int lookahead = 0;
 
 enum 
 {
      S,              /* Stato Iniziale */
      ID_KW,          /* Identificatore o Keyword */
      BR_COM,         /* Parentesi o commento */
      START_COM,      /* All'interno di un commento */
      AST_IN_COM,     /* Asterisco in commento*/ 
      G_GE,           /* Maggiore o maggiore-uguale*/ 
      L_LE_D,         /* Minore, minore-uguale, o diverso*/ 
      COL_ASS,        /* Due punti o assegnamento*/
      NUM,            /* Numero intero o reale*/
      NUM_R,          /* Numero reale */
      IN_STR,         /* Stringa*/
      APEX            /* Apice in stringa*/
 } current_state = S;
 
 int i = 0;
 int eot = 0;    /*end of token*/
  

 tkn->type = ERROR;
 
 while (!eot && i<MAX_STRING_LENGTH)
 { 
  if (!lookahead) 
     c = fgetc(src);
  else
     lookahead = 0;
  
  if (c==EOF)
     break;
  else switch (current_state)
  {
   case S:
        if (isalpha(c)||c=='_')
        {
           current_state = ID_KW;
           tkn->value[i++] = c;
           tkn->type = IDENTIFIER;
        }
        else if (isspace(c))
             current_state = S;
        else if (isdigit(c))
        {
             current_state = NUM;
             tkn->value[i++] = c;
             tkn->type = INTEGER;             
        }
        else switch (c)
        {
         case '+':
              tkn->type = PLUS;
              tkn->value[i++] = c;
              eot = !0;
              break;
         case '-':
              tkn->type = MINUS;
              tkn->value[i++] = c;
              eot = !0;
              break;
         case '*':
              tkn->type = ASTERIX;
              tkn->value[i++] = c;
              eot = !0;
              break;
         case '/':
              tkn->type = SLASH;
              tkn->value[i++] = c;
              eot = !0;
              break;
         case '=':
              tkn->type = EQUAL;
              tkn->value[i++] = c;
              eot = !0;
              break;
         case ';':
              tkn->type = SEMICOLON;
              tkn->value[i++] = c;
              eot = !0;
              break;
         case '.':
              tkn->type = DOT;
              tkn->value[i++] = c;
              eot = !0;
              break;
         case ',':
              tkn->type = COMMA;
              tkn->value[i++] = c;
              eot = !0;
              break;
         case '(':
              current_state = BR_COM;
              tkn->value[i++]=c;
              break;             
         case ')':
              tkn->type = RIGHT_PAR;
              tkn->value[i++] = c;
              eot = !0;
              break;
         case '>':
              current_state = G_GE;
              tkn->value[i++] = c;
              break;
         case '<':
              current_state = L_LE_D;
              tkn->value[i++] = c;
              break;
         case ':':
              current_state = COL_ASS;
              tkn->value[i++] = c;
              break;
         case '\'':
              current_state = IN_STR;
              break;
         default: 
                  eot = !0;
                  tkn->value[i++]=c;
        }
        break;
   case ID_KW:
        if (isalnum(c)||c=='_')
        {
           current_state = ID_KW;
           tkn->value[i++] = c;
        }
        else
        {
            lookahead = !0;
            eot = !0;            
        }
        break;
   case BR_COM:
        if (c == '*')
        {
           current_state = START_COM;
           i--;
        }
        else
        {
            lookahead = !0;
            eot = !0;
            tkn->type = LEFT_PAR;
        }
        break;
   case START_COM:
        if (c == '*')
        {
           current_state = AST_IN_COM;
        }
        break;
   case AST_IN_COM:
        if (c == ')')
        {
           current_state = S;
        }
        else
            current_state = START_COM;
        break;
   case G_GE:
        if (c == '=')
        {
           tkn->type = GREATER_OR_EQUAL;
           tkn->value[i++] = c;
           eot = !0;
        }
        else
        {
            tkn->type = GREATER;
            eot = lookahead = !0;
        }
        break;
   case L_LE_D:
        if (c == '=')
        {
           tkn->type = LESS_OR_EQUAL;
           tkn->value[i++] = c;
           eot = !0;
        }
        else if (c == '>')
        {
           tkn->type = DIFFERENT;
           tkn->value[i++] = c;
           eot = !0;         
        }
        else
        {
            tkn->type = LESS;
            eot = lookahead = !0;
        }
        break;
   case COL_ASS:
        if (c == '=')
        {
           tkn->type = ASSIGNMENT;
           tkn->value[i++] = c;
           eot = !0;
        }
        else
        {
            tkn->type = COLON;
            eot = lookahead = !0;
        }
        break;
   case NUM:
        if (isdigit(c))
           tkn->value[i++] = c;
        else if (c == '.')
        {
             current_state = NUM_R;
             tkn->value[i++] = c;
        }
        else
        {
            tkn->type = INTEGER;
            eot = lookahead = !0;
        }
        break;
   case NUM_R:
        if (isdigit(c))
           tkn->value[i++] = c;
        else
        {
            tkn->type = REAL;
            eot = lookahead = !0;  
        }
        break;
   case IN_STR:
        if (c == '\'')
           current_state = APEX;
        else
        {
            tkn->value[i++] = c;
        }
        break;
   case APEX:
        if (c == '\'')
        {
           current_state = IN_STR;
           tkn->value[i++] = c;
        }
        else
        {
            eot = lookahead = !0;
            tkn->type = STRING;
        }
        break;
  }
  
 }
 
 tkn->value[i++]='\0';
 
 if (is_keyword(tkn->value)) tkn->type = KEYWORD;
      
 return (c!=EOF);
       
}

/* Main Program --------------------------------------------------------------*/
int main (int argc, char* argv[])
{
 char* filename = argv[1];
 FILE* source;
 Token token;
 
 source = fopen(filename,"r");
 
 while (getToken(source,&token))
 {
  if (token.type == ERROR)
     printf ("Lexical Error (%s)\n",token.value);
  else
  
      printf ("Tipo = %d, Valore = %s\n", token.type, token.value);
 }
 
 fclose(source);
 
 system("PAUSE");
}
