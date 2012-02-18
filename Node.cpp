//
//  Node Implementation
//

#include "Node.h"

using namespace std;




//
// OBJECT ATTRIBUTES
//

bool Node::isTheirs() const
{
    if (myValue == THEIRS) return true;
    return false;
}


bool Node::isOurs() const
{
    if (myValue == OURS) return true;
    return false;
}

bool Node::isStart() const
{
    if (myValue == START) return true;
    return false;
}


bool Node::isStop() const
{
    if (myValue == STOP) return true;
    return false;
}


bool Node::isVisited() const
{
    return myVisited;
}


//
// OBJECT MUTATORS
//
void Node::setId (int x)
{
    myId = x;
}

void Node::setVisited (bool x)
{
    myVisited = x;
}

void Node::x (int x)
{
    myX = x;
}

void Node::y (int x)
{
    myY = x;
}





//
// OBJECT ACCESSORS
//
int Node::x () const        
{ 
    return myX; 
}


int Node::y () const        
{ 
    return myY; 
}


Node::Value Node::value () const    
{ 
    return myValue; 
}

int Node::id () const
{
    return myId;
}




//
// BOOKKEEPERS
//
Node::Node ()
{
    _zero();
}


Node::Node (int theX, int theY, int theValue, int theId)
{
    _zero();
    _initialize (theX, theY, theValue, theId);
}

Node::Node (const Node & theNode)
{
    _initialize (theNode.myX, theNode.myY, theNode.myValue, theNode.myId);
}

void Node::_zero ()
{
    myX         = 0;
    myY         = 0;
    myId        = 0;
    myValue     = OURS;
    myVisited   = false;
}

void Node::_initialize (int theX, int theY, int theValue, int theId)
{
    myX         = theX;
    myY         = theY;
    myId        = theId;
    myValue     = static_cast <Value> (theValue);
}

Node::~Node ()
{
}




//
// OUTPUT OPERATOR
//
ostream & operator << (ostream & theStream, const Node & theNode)
{
    theStream << "(" << theNode.myX << ", " << theNode.myY << ") = " << theNode.myValue << " ";
    return theStream;
}