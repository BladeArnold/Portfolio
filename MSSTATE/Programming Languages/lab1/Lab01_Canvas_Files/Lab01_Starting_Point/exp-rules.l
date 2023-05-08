/*********************************************************************
  Name: Blade Arnold           NetID: baa215
  Course: CSE 4714              
  Lab: 01 - Lexical Analyzer 
  Purpose of File: Contains the the rules for the flex parser. It goes throught all of the table from the lab one document.

This is the file that you should modify for Lab 1.
**********************************************************************/

%option noyywrap
%{
#include "lexer.h"

// global variable to hold current line number being read
int line_number = 1;


#define HYPE [-];

%}

/*This section follows closely to the assignment table.*/
/*This first part covers the Generic Data Values*/
/*The first function covers all the dates and will stop if they are two or more slashes.*/
Date [0-9]{4}\/[0-9][0-9]\/[0-9]{2} 

/*The second definition just looks for the Yes. Upper or lower case does not matter.*/ 
Yes (?i:Yes)

/*The third definition just looks for the No. Upper or lower case does not matter.*/ 
No (?i:No)

/*The fourth definition just looks for the Unknown. Upper or lower case does not matter.*/ 
Unknown (?i:Unknown)

/*The fith definition just looks for the Missing. Upper or lower case does not matter.*/ 
Missing (?i:Missing)


/*This second part covers the Data Values*/
/*The first function looks for lab probably cases.Upper or lower case does not matter. This was coded this way because it worked, and i did not want to fix and break . */
Lab [a-zA-Z]{10}[-][a-z]{9}[ ][a-z]{4}

/*The second definition just looks for the Probable Case. Upper or lower case does not matter.*/
Probable (?i:Probable)[ ](?i:Case)

/*The third definition just looks for the Male. Upper or lower case does not matter.*/
Male (?i:Male)

/*The fourth definition just looks for the Female. Upper or lower case does not matter.*/
Female (?i:Female)

/*The Fifth definition just looks for the Other. Upper or lower case does not matter.*/
Other (?i:Other)


/*The definitions 6-13 just looks for the ages and the word Years. Upper or lower case does not matter.*/
AGE0 [0-9][ ][-][ ][0-9][ ](?i:Years)
AGE1 [1][0-9][ ][-][ ][1][0-9][ ](?i:Years)
AGE2 [2][0-9][ ][-][ ][3][0-9][ ](?i:Years)
AGE4 [4][0-9][ ][-][ ][4][0-9][ ](?i:Years)
AGE5 [5][0-9][ ][-][ ][5][0-9][ ](?i:Years)
AGE6 [6][0-9][ ][-][ ][6][0-9][ ](?i:Years)
AGE7 [7][0-9][ ][-][ ][7][0-9][ ](?i:Years)
AGE8 [0-9]{2}[+][ ](?i:Years)


/*The rules 14-20 just looks for the race of the person. Upper or lower case does not matter. It also will incldue the slashes.*/
Hispanic ["](?i:Hispanic)[/](?i:Latino)["]
Native ["](?i:American)[ ](?i:Indian)[ ][/][ ](?i:Alaska)[ ](?i:Native,)[ ](?i:Non-Hispanic)["]
Asian ["](?i:Asian,)[ ](?i:Non-Hispanic)["]
Black ["](?i:Black,)[ ](?i:Non-Hispanic)["]
Pacific_Islander ["](?i:Native)[ ](?i:Hawaiian)[ ][/][ ](?i:Other)[ ](?i:Pacific)[ ](?i:Islander,)[ ](?i:Non-Hispanic)["]
White ["](?i:White,)[ ](?i:Non-Hispanic)["]
Multiple_Other ["](?i:Multiple)[/](?i:Other,)[ ](?i:Non-Hispanic)["]




%%
 /*These fuctions take the defentions of the generic data values and parses for them and when said defiention is found returns the token value.*/
, {return SEPARATOR;}

{Date} {return DATE;}

{Yes} {return YES;}

{No} {return NO;}

{Unknown} {return UNKNOWN_VALUE;}

{Missing} {return MISSING;}


 /*These fuctions take the defentions of the data values and parses for them and when said defiention is found returns the token value.*/
[Ll]aboratory-confirmed\ [Cc]ase   {return LABORATORY;}

{Probable} {return PROBABLE;}

{Male} {return MALE;}

{Female} {return FEMALE;}

{Other} {return OTHER;}


 /*These fuctions take the defentions of the ages and parses for them and when said defiention is found returns the token value.*/
{AGE0} {return AGE_0X;}

{AGE1} {return AGE_1X;}

{AGE2} {return AGE_2X;}

{AGE4} {return AGE_4X;}

{AGE5} {return AGE_5X;}

{AGE6} {return AGE_6X;}

{AGE7} {return AGE_7X;}

{AGE8} {return AGE_8X;}


 /*These fuctions take the defentions of the races and parses for them and when said defiention is found returns the token value.*/

{Hispanic} {return HISPANIC;}

{Native} {return NATIVE_AMERICAN;}

{Asian} {return ASIAN;}

{Black} {return BLACK;}

{Pacific_Islander} {return PACIFIC_ISLANDER;}

{White} {return WHITE;}

{Multiple_Other} {return MULTIPLE_OTHER;}

\n     { ++line_number;}


 /* Eat any whitespace, will need to be modified to count lines */

[ \t\r]+             /* nop */


 /* Found an unknown character */

.         { return UNKNOWN_TOKEN; }

 /* Recognize end of file */

<<EOF>>   { return EOF_TOKEN; }

