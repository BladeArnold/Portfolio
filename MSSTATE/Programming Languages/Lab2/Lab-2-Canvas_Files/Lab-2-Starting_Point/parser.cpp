/********************************************************************* 
  Name: Blade Arnold             NetID: baa215
  Course: CSE 4714               
  Lab: 02 - Parser  
  Purpose of File: Contains the parser code and parses the inputs into the correct order.
*********************************************************************/ 

#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

extern "C"
{
  extern int   yylex();      // the generated lexical analyzer
  extern char *yytext;       // text of current lexeme
}


int nextToken = 0;
int nouncount = 0;      // number of times nounphrase has started
int adjcount = 0;       // number of times adjphrase has started
int verbcount = 0;      // number of times verbphrase has started
int verbinsentence = 0;

// Production functions
bool firstOf_sentence();

//*****************************************************************************
// Get the next lexeme (word in sentence)
int lex() {
  nextToken = yylex();
  if( nextToken == TOK_EOF ) {
    yytext[0] = 'E'; yytext[1] = 'O'; yytext[2] = 'F'; yytext[3] = 0;   
  }

  printf("Next token: %d, lexeme: |%s|\n", nextToken, yytext);
  return nextToken;
}
//*****************************************************************************
// Report what we found
void output( string what ) {
  cout << "===> Accepted " << what << ": |" << yytext << "| <===" << endl;
}
//*****************************************************************************
// <sentence> -> <noun phrase> <verb phrase> <noun phrase>
void sentence() 
{
  if( firstOf_sentence() == false )
    throw( "<sentence> did not start with an article or possessive." );
  
  cout << "Enter <sentence>" << endl;
  nounphrase();     // does the nounphrase
  verbphrase();     // does the verbphrase
  nounphrase();     // does the nounphrase again


  cout << "Exit <sentence>" << endl;
} 
//*****************************************************************************
bool firstOf_sentence()       // Checks the first word of the sentance for article or possessive
{
  return nextToken == ARTICLE || nextToken == POSSESSIVE;
  return true;
}

bool firstOf_noun()         // Checks to see if the nounphrase for article or possessive
{
  return  nextToken == ARTICLE || nextToken == POSSESSIVE;
  return true;
}

bool firstOf_adj()      // Checks to see adjpharse for article or adjective
{
  return nextToken == ARTICLE || nextToken == ADJECTIVE || nextToken == POSSESSIVE;
  return true;
}

bool firstOf_verb()   // Checks to see verbphrase for verb or adverb
{
  return nextToken == VERB || nextToken == ADVERB;
  return true;
}

void nounphrase(void)     // function for the nounphrase
{
  
  nouncount++;      // adds to noun count 

    if( firstOf_noun() == false )
    throw( "<noun phrase> did not start with an article or possessive." );     // checks for the nounphrase

  cout << "  Enter <noun phrase> " << nouncount << endl;      // prints out the words and counts

  if (nextToken == ARTICLE || nextToken == POSSESSIVE)     // checks for the article or possessive and sends it to adjphrase
  {
    adjphrase();
  }

  if (nextToken == NOUN)      // see if its a noun
  {
    output("NOUN");       // output when the noun is found
  } 

  lex();

  cout << "   Exit <noun phrase> " << nouncount << endl;    // prints out the words and counts
}

void adjphrase()    // function for the adjective phrase
{

if( firstOf_adj() == false )
    throw( "<adjective phrase> did not start with an ARTICLE or POSSESSIVE." );     // checks for the adjphrase

  adjcount++;     // adds to adj count 
  
  
  cout << "  Enter <adjective phrase> " << adjcount << endl;      // prints out the words and counts
  
    while (nextToken == ARTICLE || nextToken == ADJECTIVE || nextToken == POSSESSIVE) // loops for these words
    {
      if (nextToken == ADJECTIVE)   // checks for adjective and outputs it. Then lexes
      {
       output("ADJECTIVE");
       lex();
      }
     if (nextToken == ARTICLE)    // checks for ARTICLE and outputs it. Then lexes
     {
       output("ARTICLE");
       lex();
     }
     if (nextToken == POSSESSIVE)   // checks for POSSESSIVE and outputs it. Then lexes
     {
       output("POSSESSIVE");
       lex();
     }
     if (firstOf_adj() == false)  // checks for adjectives tokens and outputs it. Then leave
     {
       cout << "   Exit <adjective phrase> " << adjcount << endl;     // prints out the words and counts
       break;
     }
      
    
  }
}

void verbphrase() // function for the verbphrase
{
  
  verbcount++;    // adds to verb count 
  

  if( firstOf_verb() == false )
    throw( "<verb phrase> did not start with an Verb or Adverb." );    // checks for the verbphrase

  cout << "  Enter <verb phrase> " << verbcount << endl;      // prints out the words and counts

  while (nextToken == VERB || nextToken == ADVERB)      // checks for adjective and outputs it. Then lexes
  {

   if (nextToken == VERB)     // checks for VERB and outputs it. Then lexes
    {
    output("VERB"); 
    lex();
    if (nextToken == ADVERB)
    {
      nounphrase();
      break;
    }
    }

  if (nextToken == ADVERB)      // checks for ADVERB and outputs it. Then lexes. then restarts
   {
    output("ADVERB"); 
    lex();
    verbphrase();
   }

   if (firstOf_verb() == false)     // checks for verbs then break
    {
     break;
    }
  } 
     cout <<"   Exit <verb phrase> " << verbcount-- << endl;    // prints out the words and counts
     verbinsentence++;

}

