//*****************************************************************************
// (part 3)
// purpose: node classes used while building a parse tree for
//              the arithmetic expression
// version: Fall 2022
//  author: Joe Crumpton / Ed Swan
//*****************************************************************************

#include "parse_tree_nodes.h"
#include "parser.h"
#include <map>
#include <math.h>


bool printDelete = false;   // shall we print deleting the tree?

// ---------------------------------------------------------------------
// Indent according to tree level
static void indent(int level) {
  for (int i = 0; i < level; i++)
    cout << ("|  ");
}
// ---------------------------------------------------------------------
FactorNode::~FactorNode() {}
// Uses double dispatch to call the overloaded method printTo in the 
// FactorNodes: IdNode, IntLitNode, and NestedExprNode
ostream& operator<<(ostream& os, FactorNode& fn) {
  fn._level--;
  os << endl; indent(fn._level); os << "(factor ";
  fn._level++;
  fn.printTo(os);
  fn._level--;
  os << endl; indent(fn._level); os << "factor) ";
  fn._level++;
	return os;
}

float FactorNode::interpret() 
{
  return this->interpret();
}
// ---------------------------------------------------------------------
IdNode::IdNode(int level, string name) {
  _level = level;
  id = new string(name);
}
IdNode::~IdNode() {
  if(printDelete) 
    cout << "Deleting FactorNode:IdNode" << endl;
	delete id;
	id = nullptr;
}
void IdNode::printTo(ostream& os) {
	os << "( IDENT: " << *id << " ) ";
}
float IdNode::interpret() 
{
  symbolTableT::iterator variable = symbolTable.find(*id);
  return variable->second;
}
// ---------------------------------------------------------------------
IntLitNode::IntLitNode(int level, int value) {
  _level = level;
  int_literal = value;
}
IntLitNode::~IntLitNode() {
  if(printDelete)
    cout << "Deleting FactorNode:IntLitNode" << endl;
	  // Nothing to do since the only members are not pointers
}
void IntLitNode::printTo(ostream& os) {
	os << "( INTLIT: " << int_literal << " ) ";
}
float IntLitNode::interpret() 
{
  return int_literal;

}
// ---------------------------------------------------------------------



// ---------------------------------------------------------------------
FloatLitNode::FloatLitNode(int level, float value) {
  _level = level;
  Float_literal = value;
}
FloatLitNode::~FloatLitNode() {
  if(printDelete)
    cout << "Deleting FactorNode:FloatLitNode" << endl;
	  // Nothing to do since the only members are not pointers
}
void FloatLitNode::printTo(ostream& os) {
	os << "( FLOATLIT: " << Float_literal << " ) ";
}
float FloatLitNode::interpret() 
{
  return Float_literal;
}


// NotNode::NotNode(int level, string name) {
//   _level = level;
//   id = new string(name);
// }
// NotNode::~NotNode() {
//   if(printDelete) 
//     cout << "Deleting FactorNode:NotNode" << endl;
// 	delete id;
// 	id = nullptr;
// }
// void NotNode::printTo(ostream& os) {
// 	os << "(" << *id; os << endl;
//   indent(_level);
//   os << "Factor ( ";
// }
// float NotNode::interpret() 
// {
//   return 0.0;
// }

MinusNode::MinusNode(int level, FactorNode* en) {
  _level = level;
  factor4Ptr = en;
}
MinusNode::~MinusNode() {
  if(printDelete) 
    cout << "Deleting FactorNode:MinusNode" << endl;
  delete factor4Ptr;
  factor4Ptr = nullptr;
}
void MinusNode::printTo(ostream& os) {

	os << "(- " ;
  os << *factor4Ptr;
  // _level--;
  os << ")"; 
}
float MinusNode::interpret() 
{
  float num;
  num = factor4Ptr->interpret();
  num = num * (-1); 
  return num;
}


NestedExprNode::NestedExprNode(int level, ExprNode* en) {
  _level = level;
	exprPtr = en;
}
void NestedExprNode::printTo(ostream& os) {
	os << *exprPtr;
  os << ")";
}
NestedExprNode::~NestedExprNode() {
  if(printDelete)
    cout << "Deleting FactorNode:NestedExprNode" << endl;
  delete exprPtr;
  exprPtr = nullptr;
}
float NestedExprNode::interpret() 
{
  return exprPtr->interpret();
}

// Not Node
NestedFactorNode::NestedFactorNode(int level, FactorNode* en) {
  _level = level;
	factor3Ptr = en;
}
void NestedFactorNode::printTo(ostream& os) {
	os << "(NOT" ;
  os << *factor3Ptr;
  os << ")";
}
NestedFactorNode::~NestedFactorNode() {
  if(printDelete)
    cout << "Deleting FactorNode:NotNode" << endl;
  delete factor3Ptr;
  factor3Ptr = nullptr;
}
float NestedFactorNode::interpret() 
{
    if (truth(factor3Ptr->interpret()) == 1.0)
      {
        return 0.0; // true
      }
      else
      {
        return 1.0; // false
      }
}





// ---------------------------------------------------------------------
TermNode::TermNode(int level) {
  _level = level;
}
ostream& operator<<(ostream& os, TermNode& tn) {
  os << endl; indent(tn._level); os << "(term ";
	os << *(tn.firstFactor);

	int length = tn.restFactorOps.size();
	for (int i = 0; i < length; ++i) {
		int op = tn.restFactorOps[i];
    if (op == TOK_MULTIPLY) {
      os << endl; indent(tn._level); os << "* ";
    } else {
      os << endl; indent(tn._level); os << "/ ";
    }
		os << *(tn.restFactors[i]);
	}
  os << endl; indent(tn._level); os << "term) ";
	return os;
}
TermNode::~TermNode() {
  if(printDelete)
    cout << "Deleting TermNode" << endl;
	delete firstFactor;
	firstFactor = nullptr;

	int length = restFactorOps.size();
	for (int i = 0; i < length; ++i) {
		delete restFactors[i];
		restFactors[i] = nullptr;
	}
}
float TermNode::interpret()
{ 
  // a Term is a Factor followed by 0 or more Factors separated by * or / operations 
 
  // get the value of the first Factor 
  float returnValue = firstFactor->interpret(); 
 
  int length = restFactorOps.size(); 
  for (int i = 0; i < length; ++i) 
  { 
    // get the value of the next Factor 
    float nextValue = restFactors[i]->interpret(); 
     
    // perform the operation (* or /) that separates the Factors 
    switch(restFactorOps[i]) 
    { 
      case TOK_MULTIPLY:
  
        returnValue = returnValue * nextValue; 
      break; 
      case TOK_DIVIDE: 
        returnValue = returnValue / nextValue; 
      break; 
      case TOK_AND: 
        returnValue = returnValue && nextValue; 
      break; 
    } 
  } 
  return returnValue; 
} 





SimpleNode::SimpleNode(int level) {
  _level = level;
}
ostream& operator<<(ostream& os, SimpleNode& en) {
  os << endl; indent(en._level); os << "(simple_exp ";
	os << *(en.firstTerm);

	int length = en.restTermOps.size();
	for (int i = 0; i < length; ++i) {
		int op = en.restTermOps[i];
    if (op == TOK_PLUS) {
      os << endl; indent(en._level); os << "+ ";
    } else {
      os << endl; indent(en._level); os << "- ";
    }
		os << *(en.restTerms[i]);
	}
  os << endl; indent(en._level); os << "simple_exp) ";
	return os;
  
}
SimpleNode::~SimpleNode() {
  if(printDelete)
    cout << "Deleting SimpleExpNode" << endl;
	delete firstTerm;
	firstTerm = nullptr;

	int length = restTermOps.size();
	for (int i = 0; i < length; ++i) {
		delete restTerms[i];
		restTerms[i] = nullptr;
	}
}
float SimpleNode::interpret()
{
   // an Expr is a Term followed by 0 or more Terms separated by + or - operations

  // get the value of the first Term
  float returnValue = firstTerm->interpret();

  int length = restTermOps.size();
  for (int i = 0; i < length; ++i) {
    // get the value of the next Term
    float nextValue = restTerms[i]->interpret();

    // perform the operation (+ or -) that separates the Terms
    switch(restTermOps[i]) {
      case TOK_PLUS:
        returnValue = returnValue + nextValue; 
      break;
      case TOK_MINUS:
        returnValue = returnValue - nextValue; 
      break;
      case TOK_OR:
        returnValue = returnValue || nextValue; 
      break;
    }
  }
  return returnValue;
}




// ---------------------------------------------------------------------
ExprNode::ExprNode(int level) {
  _level = level;
}
ostream& operator<<(ostream& os, ExprNode& en) {
  os << endl; indent(en._level); os << "(expression ";
	os << *(en.firstSimple);

	int length = en.restSimpleOps.size();
	for (int i = 0; i < length; ++i) {
		int op = en.restSimpleOps[i];
    if (op == TOK_LESSTHAN) {
      os << endl; indent(en._level); os << "< ";
    } else if (op == TOK_GREATERTHAN) {
      os << endl; indent(en._level); os << "> ";
    }
    else if (op == TOK_NOTEQUALTO) {
      os << endl; indent(en._level); os << "<> ";
    }
     else if (op == TOK_EQUALTO) {
      os << endl; indent(en._level); os << "= ";
    }
		os << *(en.restSimple[i]);
	}
  os << endl; indent(en._level); os << "expression) ";
	return os;
}
ExprNode::~ExprNode() {
  if(printDelete)
    cout << "Deleting ExpressionNode" << endl;
	delete firstSimple;
	firstSimple = nullptr;

	int length = restSimpleOps.size();
	for (int i = 0; i < length; ++i) {
		delete restSimple[i];
		restSimple[i] = nullptr;
	}

}
float ExprNode::interpret()
{
   // an Expr is a Term followed by 0 or more Terms separated by + or - operations

  // get the value of the first Term
  float returnValue = firstSimple->interpret();

  int length = restSimpleOps.size();
  for (int i = 0; i < length; ++i) {
    // get the value of the next Term
    float nextValue = restSimple[i]->interpret();

    // perform the operation (+ or -) that separates the Terms
    switch(restSimpleOps[i]) {
      case TOK_EQUALTO:
     if(abs(returnValue - nextValue) <= EPSILON) 
     {
        return 1.0; // true 
     }
      
      else
      {
        return 0.0; // false 
      } 
       
      break;
      case TOK_LESSTHAN:
      if (returnValue < nextValue)
      {
        return 1.0;
      }
      else
      {
        return 0.0;
      }
      break;
      case TOK_GREATERTHAN:
      if (returnValue > nextValue)
      {
        return 1.0;
      }
      else
      {
        return 0.0;
      }
      break;
      case TOK_NOTEQUALTO:
       if(abs(returnValue - nextValue) > EPSILON) 
      return 1.0; // true 
    else 
      return 0.0; // false 
  break;
 
    }
  }
  return returnValue;
}






ProgramNode::ProgramNode(int level) {
  _level = level;
}
ostream& operator<<(ostream& os, ProgramNode& en) {
  os << endl; indent(en._level); os << "(program ";
	os << *(en.firstBlock);

  os << endl; indent(en._level); os << "program) ";
	return os;
}
ProgramNode::~ProgramNode() {
  if(printDelete)
    cout << "Deleting ProgramNode" << endl;
	delete firstBlock;
	firstBlock = nullptr;

}
void ProgramNode::interpret()
{
  firstBlock->interpret();
  
}





BlockNode::BlockNode(int level) {
  _level = level;
}
ostream& operator<<(ostream& os, BlockNode& en) {
  os << endl; indent(en._level); os << "(block ";
	os << *(en.firstStatement);


  os << endl; indent(en._level); os << "block) ";
	return os;
}
BlockNode::~BlockNode() {
  if(printDelete)
    cout << "Deleting BlockNode" << endl;
	delete firstStatement;
	firstStatement = nullptr;
}
void BlockNode::interpret()
{
  firstStatement->interpret();
}





StatementNode::~StatementNode() {}
ostream& operator<<(ostream& os, StatementNode& fn) {
  fn.printTo(os);
	return os;
}
void StatementNode::interpret()  
{ 
  this->interpret(); 
} 

CompoundNode::CompoundNode(int level, vector<StatementNode*> _statement) {
  statement = _statement;
  _level = level;
}

ostream& operator<<(ostream& os, CompoundNode& en) {
  en.printTo(os);
	return os;
}

CompoundNode::~CompoundNode() {
  if(printDelete) 
    cout << "Deleting StatementNode:CompoundStmtNode" << endl;
    for (int i = 0; i < statement.size(); i++)
    {
      delete statement[i];
      statement[i] = nullptr;
    }
    statement.clear();
}

void CompoundNode::printTo(ostream& os) {
  os << endl; indent(_level); os << "(compound_stmt";

	 int length = statement.size();
   for (int i = 0; i < length; ++i) {
	 os << *(statement[i]);
	 }
  os << endl; indent(_level);
   os << "compound_stmt)";
}
void CompoundNode::interpret()
{
  int length = statement.size();
  for (int i = 0; i < length; ++i) {
	statement[i]->interpret();
	}
}


// ---------------------------------------------------------------------
WriteNode::WriteNode(int level, string* name, int value) {
  _level = level;
  id = name;
  type = value;

  
}
WriteNode::~WriteNode() {
  if(printDelete)
    cout << "Deleting StatementNode:WriteStmtNode" << endl;
  delete id;
  id = nullptr; 
}
void WriteNode::printTo(ostream& os) {
	os << endl; indent(_level); os << "(write_stmt ( " << *id << " )";
  os << endl; indent(_level); os << "write_stmt)";
}
void WriteNode::interpret()
{    
// Implement the write statement, depending on what is being written 
  switch(type) { 
    case TOK_STRINGLIT: 
      // If we are writing a string, write it. First, strip  
      // leading and trailing quote characters.  
      cout << id->substr(1, id->length()-2) << endl; 
    break; 
    case TOK_IDENT: 
      // If we are writing a variable, look up and print value  
      symbolTableT::iterator variable = symbolTable.find(*id); 
      cout << variable->second << endl; 
    break;
  }
}

AssginNode::AssginNode(int level) {
  _level = level;
}
AssginNode::~AssginNode() {
  if(printDelete)
    cout << "Deleting StatementNode:AssignmentStmtNode" << endl;
  delete id;
  delete expr1Ptr;
  id = nullptr;
  expr1Ptr = nullptr; 
}
void AssginNode::printTo(ostream& os) {
	os << endl; indent(_level); os << "(assignment_stmt ( " << *id << " := )";
  os << *expr1Ptr;
  os << endl; indent(_level); os << "assignment_stmt)";
}
void AssginNode::interpret()
{
  // Look up the variable that will store expression result 
  symbolTableT::iterator variable = symbolTable.find(*id); 
  // Put the expression in the variable 
  variable->second = expr1Ptr->interpret();
}


ReadNode::ReadNode(int level) {
  _level = level;
}
ReadNode::~ReadNode() {
  if(printDelete)
    cout << "Deleting StatementNode:ReadStmtNode" << endl;
  delete id;
  id = nullptr; 
}
void ReadNode::printTo(ostream& os) {
	os << endl; indent(_level); os << "(read_stmt ( " << *id << " )";
  os << endl; indent(_level); os << "read_stmt)";
}
void ReadNode::interpret()
{
  string input;
  cin >> input;
  // Look up the variable that will store expression result 
  symbolTableT::iterator variable = symbolTable.find(*id); 
  // Put the expression in the variable 
  variable->second = stof(input);
} 

IfNode::IfNode(int level) {
  _level = level;
}
IfNode::~IfNode() {
  if(printDelete)
    cout << "Deleting StatementNode:IfStmtNode" << endl;
  delete id;
  delete exprPtr;
  delete cmpPtr;
  delete writePtr;
  delete cmp2Ptr;
  delete write2Ptr;
  delete ifPtr;
  
  delete assignPtr;
  id = nullptr;
  exprPtr = nullptr;
  cmpPtr = nullptr;
  cmp2Ptr = nullptr;
  writePtr = nullptr;
  ifPtr = nullptr;
  write2Ptr = nullptr;
  assignPtr = nullptr;
}
void IfNode::printTo(ostream& os) {
	os << endl; indent(_level); os << "(if_stmt";
  os << *exprPtr;
  if (cmpPtr != nullptr)
  {
    os << endl; indent(_level); os << "(then"; 
    os << *cmpPtr;
    os << endl; indent(_level); os << "then)";
  }

  if (writePtr != nullptr)
  {
    os << endl; indent(_level); os << "(then"; 
    os << *writePtr;
    os << endl; indent(_level); os << "then)";
  }

  if (ifPtr != nullptr)
  {
  os << endl; indent(_level); os << "(else"; 
  os << *ifPtr;
  os << endl; indent(_level); os << "else)";
  }
 if (cmp2Ptr != nullptr)
 {
  os << endl; indent(_level); os << "(else"; 
  os << *cmp2Ptr;
  os << endl; indent(_level); os << "else)";
 }

  if (write2Ptr != nullptr)
  {
  os << endl; indent(_level); os << "(else"; 
  os << *write2Ptr;
  os << endl; indent(_level); os << "else)";
  }

  if (assignPtr != nullptr)
  {
  os << endl; indent(_level); os << "(else"; 
  os << *assignPtr;
  os << endl; indent(_level); os << "else)";
  }

  os << endl; indent(_level); os << "if_stmt)";
}
void IfNode::interpret()
{
  if (truth(exprPtr->interpret() == 1.0))
  {

    if (cmpPtr != nullptr)
    {
      cmpPtr->interpret();
    }
    if (writePtr != nullptr)
    {
      writePtr->interpret();
    }
    
  }
  else
  {

    if (ifPtr != nullptr)
    {
      ifPtr->interpret();
    }
    if (cmp2Ptr != nullptr)
    {
      cmp2Ptr->interpret();
    }
    if (write2Ptr != nullptr)
    {
      write2Ptr->interpret();
    }
    if (assignPtr != nullptr)
    {
      assignPtr->interpret();
    }

  }
}


WhileNode::WhileNode(int level) {
  _level = level;
}
WhileNode::~WhileNode() {
  if(printDelete)
    cout << "Deleting StatementNode:WhileStmtNode" << endl;
  delete id;
  delete exprPtr;
  delete cmpPtr;
  delete assignPtr;
  id = nullptr;
  exprPtr = nullptr;
  cmpPtr = nullptr;
  assignPtr = nullptr; 
}
void WhileNode::printTo(ostream& os) {
	os << endl; indent(_level); os << "(while_stmt ";
   if (exprPtr != nullptr)
   {
    os << *exprPtr;
   }
   if (cmpPtr != nullptr)
   {
    os << *cmpPtr;
   }
   if (assignPtr != nullptr)
   {
    os << *assignPtr;
   }
  os << endl; indent(_level); os << "while_stmt)";
}
void WhileNode::interpret()
{
  bool finshed = false;

  while (!finshed)
  {
    if(truth(exprPtr->interpret()) == 1.0) 
    {
      if (cmpPtr != nullptr)
      {
        cmpPtr->interpret();
      }
      if (assignPtr != nullptr)
      {
        assignPtr->interpret();
      }
    }

    else
    {
      finshed = true;
      return;
    }

  }

}