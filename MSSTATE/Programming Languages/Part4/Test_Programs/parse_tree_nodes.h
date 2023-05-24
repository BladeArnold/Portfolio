//*****************************************************************************
// (part 3)
// purpose: node classes used while building a parse tree for
//              the arithmetic expression
// version: Fall 2022
//  author: Blade Arnold
//*****************************************************************************

#ifndef PARSE_TREE_NODES_H
#define PARSE_TREE_NODES_H


#include <iostream>
#include <vector>
#include <string>
#include "lexer.h"
//#include "parser.h"

using namespace std;

extern bool printDelete;      // shall we print deleting the tree?

// ---------------------------------------------------------------------
// Forward declaration of node types
class ExprNode; 
class SimpleNode;
class TermNode;
class FactorNode;
class ProgramNode;
class BlockNode;

class StatementNode;


// ---------------------------------------------------------------------
// Program node
class ProgramNode {
public:
  int _level = 0;          // recursion level of this node
  BlockNode* firstBlock = nullptr;
  vector<int> restBlockOps; // TOK_ADD_OP or TOK_SUB_OP
  vector<BlockNode*> restBlock;

  ProgramNode(int level);
  ~ProgramNode();
  void interpret();
};
ostream& operator<<(ostream&, ProgramNode&); // Node print operator
// ---------------------------------------------------------------------


// ---------------------------------------------------------------------
// Block node
class BlockNode {
public:
  int _level = 0;          // recursion level of this node
  StatementNode* firstStatement = nullptr;
  vector<int> restStatementOps; // TOK_ADD_OP or TOK_SUB_OP
  vector<StatementNode*> restStatement;

  BlockNode(int level);
  ~BlockNode();
  void interpret();
};
ostream& operator<<(ostream&, BlockNode&); // Node print operator
// --------------------------------------------------------------------



// ---------------------------------------------------------------------
// <expr> -> <term> {{ (( + || - )) <term> }}
class ExprNode {
public:
  int _level = 0;          // recursion level of this node
  SimpleNode* firstSimple = nullptr;
  vector<int> restSimpleOps; // TOK_ADD_OP or TOK_SUB_OP
  vector<SimpleNode*> restSimple;

  ExprNode(int level);
  ~ExprNode();
  float interpret();

};
ostream& operator<<(ostream&, ExprNode&); // Node print operator
// ---------------------------------------------------------------------

// <expr> -> <term> {{ (( + || - )) <term> }}
class SimpleNode {
public:
  int _level = 0;          // recursion level of this node
  TermNode* firstTerm = nullptr;
  vector<int> restTermOps; // TOK_ADD_OP or TOK_SUB_OP
  vector<TermNode*> restTerms;

  SimpleNode(int level);
  ~SimpleNode();
  float interpret();

};
ostream& operator<<(ostream&, SimpleNode&); // Node print operator
// ---------------------------------------------------------------------



// <term> -> <factor> {{ (( * || / )) <factor> }}
class TermNode {
public:
  int _level = 0;              // recursion level of this node
  FactorNode* firstFactor = nullptr;
  vector<int> restFactorOps;   // TOK_MULT_OP or TOK_DIV_OP
  vector<FactorNode*> restFactors;

  TermNode(int level);
  ~TermNode();
  float interpret();

};
ostream& operator<<(ostream&, TermNode&); // Node print operator
// ---------------------------------------------------------------------
// Abstract class. Base class for IdNode, IntLitNode, NestedExprNode.
// <factor> -> ID || INTLIT || ( <expr> )
class FactorNode {
public:
  int _level = 0;                        // recursion level of this node

  virtual float interpret() = 0; 
  virtual void printTo(ostream &os) = 0; // pure virtual method, makes the class Abstract
  virtual ~FactorNode();                 // labeling the destructor as virtual allows 
	                                       // the subclass destructors to be called
};
ostream& operator<<(ostream&, FactorNode&); // Node print operator
// ---------------------------------------------------------------------
// class IdNode (Identifier Node)
class IdNode : public FactorNode {
public:
    string* id = nullptr;

    IdNode(int level, string name);
    ~IdNode();
    void printTo(ostream & os);
    float interpret();
};
// ---------------------------------------------------------------------
// class IntLitNode (Integer Literal Node)
class IntLitNode : public FactorNode {
public:
    int int_literal = 0;

    IntLitNode(int level, int value);
    ~IntLitNode();
    void printTo(ostream & os);
    float interpret();
};
// ---------------------------------------------------------------------

// class IntLitNode (Integer Literal Node)
class FloatLitNode : public FactorNode {
public:
    float Float_literal = 0.0;

    FloatLitNode(int level, float value);
    ~FloatLitNode();
    void printTo(ostream & os);
    float interpret();
};
// ---------------------------------------------------------------------

// class NestedExprNode (Nested Expression Node)
class NestedExprNode : public FactorNode {
public:
    ExprNode* exprPtr = nullptr;
    

    NestedExprNode(int level, ExprNode* en);
    void printTo(ostream & os);
    ~NestedExprNode();
    float interpret();
};

// class NestedExprNode (Nested Expression Node)
class NestedFactorNode : public FactorNode {
public:
    FactorNode* factor3Ptr = nullptr;
    

    NestedFactorNode(int level, FactorNode* en);
    void printTo(ostream & os);
    ~NestedFactorNode();
    float interpret();
};



// ---------------------------------------------------------------------
class NotNode : public FactorNode {
public:
    string* id = nullptr;
    ExprNode* exprPtr = nullptr;

    NotNode(int level, string name);
    ~NotNode();
    void printTo(ostream & os);
    float interpret();
};


// ---------------------------------------------------------------------
class MinusNode : public FactorNode {
public:
    FactorNode* factor4Ptr = nullptr;
    

    MinusNode(int level, FactorNode* en);
    void printTo(ostream & os);
    ~MinusNode();
    float interpret();
};


// ---------------------------------------------------------------------
// Statement node
class StatementNode {
public:
 int _level = 0;                        // recursion level of this node


  virtual void printTo(ostream &os) = 0; // pure virtual method, makes the class Abstract
  virtual void interpret() = 0; 
  virtual ~StatementNode();                 // labeling the destructor as virtual allows 
	                                       // the subclass destructors to be called
};
ostream& operator<<(ostream&, StatementNode&); // Node print operator


// ---------------------------------------------------------------------
// class Compound (Identifier Node)
class CompoundNode : public StatementNode {
public: 
    int _level = 0; 
   
    vector<StatementNode*> statement;

    CompoundNode(int level, vector<StatementNode*> statement);
    ~CompoundNode();
    void printTo(ostream & os);
    void interpret();
};
ostream& operator<<(ostream&, CompoundNode&);
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// class Compound (Identifier Node)
class WriteNode : public StatementNode {
public:
    int _level = 0; 
    string* id = nullptr;
    int type;
    
    WriteNode(int level, string* name, int value);
    ~WriteNode();
    void printTo(ostream & os);
    void interpret();
};
// ostream& operator<<(ostream&, WriteNode&);
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// class Compound (Identifier Node)
class AssginNode : public StatementNode {
public: 
    int _level = 0; 
   string* id = nullptr;
   ExprNode* expr1Ptr = nullptr;

    AssginNode(int level);
    ~AssginNode();
    void printTo(ostream & os);
    void interpret();
};
// ostream& operator<<(ostream&, AssginNode&);
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// class Compound (Identifier Node)
class ReadNode : public StatementNode {
public: 
    int _level = 0; 
   string* id = nullptr;
   
   ReadNode(int level);
    ~ReadNode();
    void printTo(ostream & os);
    void interpret();
};
// ostream& operator<<(ostream&, AssginNode&);
// ---------------------------------------------------------------------

// class Compound (Identifier Node)
class IfNode : public StatementNode {
public: 
    int _level = 0; 
   string* id = nullptr;
   ExprNode* exprPtr = nullptr;
   CompoundNode* cmpPtr = nullptr;
   CompoundNode* cmp2Ptr = nullptr;
   WriteNode* writePtr = nullptr;
   WriteNode* write2Ptr = nullptr;
   IfNode* ifPtr = nullptr;
   AssginNode* assignPtr = nullptr;

   IfNode(int level);
    ~IfNode();
    void printTo(ostream & os);
    void interpret();
};

class WhileNode : public StatementNode {
public: 
    int _level = 0; 
   string* id = nullptr;
   ExprNode* exprPtr = nullptr;
   CompoundNode* cmpPtr = nullptr;
   AssginNode* assignPtr = nullptr;
   WhileNode(int level);
    ~WhileNode();
    void printTo(ostream & os);
    void interpret();
};

#endif /* PARSE_TREE_NODES_H */
