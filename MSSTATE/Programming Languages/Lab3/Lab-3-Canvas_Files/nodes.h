//*****************************************************************************
// purpose: define the nodes functions for the driver 
//
//  author: Blade Arnold
//*****************************************************************************

#ifndef NODES_H
#define NODES_H

#include <iostream>
#include <string>

using namespace std;

// Abstract class. Base class for StringNode, IntegerNode, and FloatNode
//
// Do NOT change this class
class DataNode {
public:
    virtual void printTo(ostream &os) = 0; // pure virtual method, makes the class Abstract
    virtual ~DataNode();                   // labeling the destructor as virtual allows 
	                                       // the subclass destructors to be called
};
ostream& operator<<(ostream&, DataNode&);  // print method
// ---------------------------------------------------------------------
class StringNode : public DataNode {
public:
    string* mystring = nullptr;
    
    StringNode(string mystring)
    {
       this->mystring = new string(mystring);
    }

    ~StringNode ()
    { 
       cout << "Deleting DataNode:StringNode:" << *mystring << endl;
    }

    void printTo(ostream& os)
    {
        os << "(string: " << *mystring << ")";
    }

    // Add constructor, destructor, and printTo methods
};
// ---------------------------------------------------------------------
class IntegerNode : public DataNode {
public:
    int* myinteger = 0;
 
    IntegerNode(int myinteger)
    {
       this->myinteger = new int(myinteger);
    }

    ~IntegerNode ()
    {
       cout << "Deleting DataNode:IntegerNode:" << *myinteger << endl;
    }

    void printTo(ostream& os)
    {
        os << "(integer: " <<*myinteger << ")";
    }
    // Add constructor, destructor, and printTo methods
};
// ---------------------------------------------------------------------
class FloatNode : public DataNode {
public:
    float myfloat = 0.0;

    FloatNode(float newfloat)
    {
       myfloat = newfloat;
    }

    ~FloatNode ()
    {
       cout << "Deleting DataNode:FloatNode:" << myfloat << endl;
    }

    void printTo(ostream& os)
    {
         os << "(float: " << myfloat << ")";
    }

    // Add constructor, destructor, and printTo methods
};


#endif /* NODES_H */ 
