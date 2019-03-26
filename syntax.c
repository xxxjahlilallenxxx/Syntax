/*syntax.c - a lexical analyzer system for simple
arithmetic expressions*/

#include <stdio.h>
#include <ctype.h>

/*Global declarations*/
/*Variables*/
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

/*Function declarations*/
void addChar();
void getChar();
void getNonBlank();
int lex();

/*Character classes*/
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/*Token codes*/
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/* main driver*/
int main(int argc, char *argv[]){
/* Open the input data file and process its contents */
  if ((in_fp = fopen(argv[1],"r")) == NULL)
    printf("ERROR - cannot open file \n");
  else {
    getChar();
    do {
      lex();
    } while (nextToken != EOF);
  }
}

/* lookup - a function to lookup operators and parentheses and return the token */
int lookup(char ch) {
  switch(ch) {
    case '(':
      addChar();
      nextToken = LEFT_PAREN;
      break;
    case ')':
      addChar();
      nextToken = RIGHT_PAREN;
      break;
    case '+':
      addChar();
      nextToken = ADD_OP;
      break;
    case '-':
      addChar();
      nextToken = SUB_OP;
      break;
    case '*':
      addChar();
      nextToken = MULT_OP;
      break;
    case '/':
      addChar();
      nextToken = DIV_OP;
      break;
    default:
      addChar();
      nextToken = EOF;
      break;
  }
  return nextToken;
}

/**/
void addChar() {
  if (lexLen <= 98){
    lexeme[lexLen++] = nextToken;
    lexeme[lexLen] = 0;
  }
  else
    printf("Error - lexeme is too long");
}

/**/
void getChar(){
  if ((nextChar = getc(in_fp)) != EOF) {
    if (isalpha(nextChar))
      charClass = LETTER;
    else if (isdigit(nextChar))
      charClass = DIGIT;
    else
      charClass = UNKNOWN;
  }
  else
    charClass = EOF;
}

/**/
void getNonBlank() {
  while (isspace(nextChar))
    getChar();
}

/**/
int lex(){
  lexLen = 0;
  getNonBlank();
  switch(charClass){
    case LETTER:
      addChar();
      getChar();
      while(charClass == LETTER || charClass == DIGIT){
        addChar();
        getChar();
      }
      nextToken = IDENT;
      break;
    case DIGIT:
      addChar();
      getChar();
      while(charClass == DIGIT){
        addChar();
        getChar();
      }
      nextToken = INT_LIT;
      break;
    case UNKNOWN:
      lookup(nextChar);
      getChar();
      break;
    case EOF:
      nextToken = EOF;
      lexeme[0] = 'E';
      lexeme[1] = 'O';
      lexeme[2] = 'F';
      lexeme[3] = 0;
      break;
    }
    printf("Next token is: %d, Next lexeme is %s \n", nextToken, lexeme);
    return nextToken;
}
