//*****************************************************************************
// (part 3)
// purpose: node classes used while building a parse tree for
//              the arithmetic expression
// version: Fall 2022
//  author: Joe Crumpton / Ed Swan
//*****************************************************************************

#include "parse_tree_nodes.h"

bool printDelete = true;   // shall we print deleting the tree?

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

NotNode::NotNode(int level, string name) {
  _level = level;
  id = new string(name);
}
NotNode::~NotNode() {
  if(printDelete) 
    cout << "Deleting FactorNode:NotNode" << endl;
	delete id;
	id = nullptr;
}
void NotNode::printTo(ostream& os) {
	os << "(" << *id; os << endl;
  indent(_level);
  os << "Factor ( ";
  

}

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





StatementNode::~StatementNode() {}
ostream& operator<<(ostream& os, StatementNode& fn) {
  fn.printTo(os);
	return os;
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



// ---------------------------------------------------------------------
WriteNode::WriteNode(int level, string* name) {
  _level = level;
  id = name;
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
