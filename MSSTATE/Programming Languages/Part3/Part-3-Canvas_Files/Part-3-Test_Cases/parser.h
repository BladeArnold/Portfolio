//**************************************************************************
 
// Replace with appropriate header comment......

//**************************************************************************

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <set>
#include <iostream>
#include "parse_tree_nodes.h"

using namespace std;

// Holds the symbols in the interpreted program
extern set<string> symbolTable;

extern int nextToken;        // next token returned by lexer

extern "C" {
	// Instantiate global variables used by flex
	extern int   yylex();      // the generated lexical analyzer
	extern char* yytext;       // text of current lexeme
}

// Function declarations
ProgramNode* program();

BlockNode* block();

AssginNode* assignment();
CompoundNode* compound();
IfNode* ifstatement();
WhileNode* whilestatement();
ReadNode* read();
WriteNode* write();
IfNode* elsestatement();


ExprNode* express();
SimpleNode* simpleexpress();
TermNode* term();
FactorNode* factor();

#endif /* PARSER_H */
