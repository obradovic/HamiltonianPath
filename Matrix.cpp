//
//  Matrix.cpp
//
//  Created by Zo Obradovic on 2/1/12.
//

#include "Matrix.h"
#include <iostream>
#include <list>
#include <queue>

using namespace std;



//
// FINDS THE PATH THROUGH THE MATRIX
//


// bfs
void Matrix::bfs()
{
    bfs(myStart, 0);
}

void Matrix::bfs (Node * theNode, int theNodeCount)
{
    theNodeCount += 1;
    theNode->setVisited(true);
 
    // if this node is the end node, check to see how many we traversed
    if (theNode->isStop())
    {
        // cout << "END NODE FOUND " << theNodeCount << " and " << myOursCount << endl; 
        if (theNodeCount == myOursCount + 2)    // + 2 to account for the start and end nodes
        {
            cout << "SOLUTION FOUND " << theNodeCount << endl;
            mySolutionCount++;
        }
    }
        
    // iterate over its edges
    NodeVector & v = myAdjacencyMap[*theNode];
    for (NodeVector::iterator node = v.begin(); node != v.end(); ++node)
    {    
        if (node->isVisited()) continue;
        
        /*
        if (! node->isVisited())
        {
            bfs(&(*node), theNodeCount);
        }
        */
    }
    

    Node * node = theNode;      // we start at the start node
    vector <Node> * vect;       // points to the right adjacency list
    queue <Node *> q;           // keeps track of our "current path"
    
    while (true)
    {
        // get the vector for this node
        vect = &(myAdjacencyMap[*node]);
        
        for (NodeVector::iterator iter = vect->begin(); iter != vect->end(); ++iter)
        {
            if (iter->isVisited()) continue;
            
            node = &(*iter);
            node->setVisited(true);
            q.push(node);
        }
    }
    
    theNode->setVisited(false);
}




void Matrix::printAdjacencyList() const
{
   
    // iterate over the adjacency list (aka map)
    for (NodeVectorMap::const_iterator i = myAdjacencyMap.begin(); i != myAdjacencyMap.end(); ++i) 
    {
        const Node & key = i->first;        // get the key
        const NodeVector & v = i->second;   // get all its edges
        
        cout << v.size() << " edges for " << key << ":  " << flush;
        
        // iterate over its edges
        for (NodeVector::const_iterator j = v.begin(); j != v.end(); ++j)
        {
            cout << *j << "    " << flush;
        }
        cout << endl;
    }

    
    /*
    for (int i = 0; i < myAdjacencyMap.size(); i++)
    {
        NodeVector v = myAdjacencyList[i];
        // vector <Node> v = myAdjacencyList[node];
        cout << "node " << i << ": " << flush;
        
        for (int j = 0; j < v.size(); j++)
        {
            Node & node = v[j];
            cout << node << "    " << flush;
        }
        
        cout << endl;
    }
    */
}



// creates the adjancency list.  Stores it in a private member
void Matrix::createAdjacencyList()
{
    // cout << "creating adj " << myXLen << endl;
    for (int x = 0; x < myXLen; x++)
    {
        for (int y = 0; y < myYLen; y++)
        {
            // cout << "creating y " << y << endl;
            
            // get this node
            Node * node = & (myMatrix[x][y]);
                
            // if this is the end node or not ours, dont bother putting it in
            if (node->isStop()) continue;
            if (node->isTheirs()) continue;
            
            // create the adjacency list for this node
            NodeVector v;
            
            // put this node at the head
            // v.push_back(*node);
            
            // and see which ones we should add
            if (upz(node)    != NULL) v.push_back(*upz(node));
            if (downz(node)  != NULL) v.push_back(*downz(node));
            if (leftz(node)  != NULL) v.push_back(*leftz(node));
            if (rightz(node) != NULL) v.push_back(*rightz(node));
            
            // and add this vector to the adjacency list
            // myAdjacencyList.push_back(v);
            myAdjacencyMap[*node] = v;
        }
    }
    
}


Node * Matrix::upz (const Node * const theNode) const
{
    return traversez (theNode->x(), theNode->y() - 1);
}

Node * Matrix::downz (const Node * const theNode) const
{
    return traversez (theNode->x(), theNode->y() + 1);
}

Node * Matrix::leftz (const Node * const theNode) const
{
    return traversez (theNode->x() - 1, theNode->y());
}

Node * Matrix::rightz (const Node * const theNode) const
{
    return traversez (theNode->x() + 1, theNode->y());
}


//
// This returns the correct item from the array.  
// NULL if its not traversable.  Only called from the abovementioned up/down/left/right methods
//
Node * Matrix::traversez (int theX, int theY) const
{
    // are we exceeding matrix boundaries?
    if (theX < 0)           { /* cout << "(" << theX << ", " << theY << ") is too left  " << endl; */ return NULL; }
    if (theY < 0)           { /* cout << "(" << theX << ", " << theY << ") is too up    " << endl; */ return NULL; }
    if (theX > myXLen - 1)  { /* cout << "(" << theX << ", " << theY << ") is too right " << endl; */ return NULL; }
    if (theY > myYLen - 1)  { /* cout << "(" << theX << ", " << theY << ") is too down  " << endl; */ return NULL; }
    
    // should we return it? not if it's been visited already or isn't ours
    if (myMatrix[theX][theY].isTheirs())  return NULL;
    if (myMatrix[theX][theY].isStart())   return NULL; 
    
    // auf!  return!
    return const_cast <Node *> (& myMatrix[theX][theY]);    // const_cast admittedly hacky, but necessary 
}








void Matrix::findHamiltonianPath (Node * theCurrentNode, int theNodeCount)
{
    // if this node cannot, or should not, be traversed, return
    if (theCurrentNode == NULL) { /* cout << "null. returning" << endl; */ return; }
    
    // increment the node count
    theNodeCount += 1;
    
    // mark this node as visited
    theCurrentNode->setVisited(true);
    
    // add this to the path
    if (myDebug) myCurrentPath.push_back(theCurrentNode);


    // traverse
    findHamiltonianPath(up    (theCurrentNode), theNodeCount);
    findHamiltonianPath(left  (theCurrentNode), theNodeCount);
    findHamiltonianPath(down  (theCurrentNode), theNodeCount);
    findHamiltonianPath(right (theCurrentNode), theNodeCount);
    
    // if this node is the end node, check to see how many we traversed
    if (theCurrentNode->isStop())
    {
        // cout << "END NODE FOUND " << theNodeCount << " and " << myOursCount << endl; 
        
        if (theNodeCount == myOursCount + 2)    // + 2 to account for the start and end nodes
        {
            if (myDebug)
            {
                cout << "Solution " << (mySolutionCount + 1) << " has " << myCurrentPath.size() << " nodes." << endl;
                for (int i = 0; i < myCurrentPath.size(); i++)
                {
                    cout << "  " << i << ": " << *(myCurrentPath[i]) << endl;
                }
                cout << endl;
            }
            
            mySolutionCount++;
        }
    }
    
    // mark this node as NOT visited
    theCurrentNode->setVisited(false);
    
    // remove this node from the current path
    if (myDebug) myCurrentPath.pop_back();
}


// Just calls the above method, passing in the Start node and 0
void Matrix::findHamiltonianPath ()
{
    findHamiltonianPath (myStart, 0);
}




//
// HELPERS
//


//
// these return the Node up/down/left/right from the passed-in Node
// NULL if its not traversible
//

Node * Matrix::up (const Node * const theNode) const
{
    return traverse (theNode->x(), theNode->y() - 1);
}

Node * Matrix::down (const Node * const theNode) const
{
    return traverse (theNode->x(), theNode->y() + 1);
}

Node * Matrix::left (const Node * const theNode) const
{
    return traverse (theNode->x() - 1, theNode->y());
}

Node * Matrix::right (const Node * const theNode) const
{
    return traverse (theNode->x() + 1, theNode->y());
}


//
// This returns the correct item from the array.  
// NULL if its not traversable.  Only called from the abovementioned up/down/left/right methods
//
Node * Matrix::traverse (int theX, int theY) const
{
    // are we exceeding matrix boundaries?
    if (theX < 0)           { /* cout << "(" << theX << ", " << theY << ") is too left  " << endl; */ return NULL; }
    if (theY < 0)           { /* cout << "(" << theX << ", " << theY << ") is too up    " << endl; */ return NULL; }
    if (theX > myXLen - 1)  { /* cout << "(" << theX << ", " << theY << ") is too right " << endl; */ return NULL; }
    if (theY > myYLen - 1)  { /* cout << "(" << theX << ", " << theY << ") is too down  " << endl; */ return NULL; }
    
    // should we return it? not if it's been visited already or isn't ours
    if (myMatrix[theX][theY].isVisited())    { /* cout << "(" << theX << ", " << theY << ") has been VISITED" << endl; */   return NULL; }
    if (myMatrix[theX][theY].isTheirs())     { /* cout << "(" << theX << ", " << theY << ") is THEIRS" << endl; */          return NULL; }
    if (myMatrix[theX][theY].isStart())      { /* cout << "(" << theX << ", " << theY << ") is START" << endl; */           return NULL; }
    
    // auf!  return!
    return const_cast <Node *> (& myMatrix[theX][theY]);    // const_cast admittedly hacky, but necessary 
}








//
// Reads the matrix from stdin
//
void Matrix::read ()
{
    // read the y and x values first
    cin >> myXLen >> ws >> myYLen;
    
    // some placeholers
    int nodeCount = myXLen * myYLen;
    myOursCount = 0;
    int temp;
    
    // put the stuff into a regular array first
    vector <int> initialArray;
    for (int i = 0; i < nodeCount; i++)
    {
        cin >> temp;
        initialArray.push_back(temp);
    }
    
    // make the vectors
    for (int i = 0; i < myXLen; i++)
    {
        vector <Node> v;
        myMatrix.push_back(v);
    }
    
    
    // iterate over each value, placing it into the right spot in the matrix 
    for (int y = 0; y < myYLen; y++)
    {
        // iterate over that vector
        for (int x = 0; x < myXLen; x++)
        {
            int i = (myXLen * y) + x; // compiler optimizes this
            
            // get a reference to the x
            vector <Node> & v = myMatrix[x];
            
            // make the Node object
            int value = initialArray[i];
            Node node (x, y, value, i);
            
            // put it onto the vector
            v.push_back (node);
          
            // If this is the start node, make a note of it. We'll use this later
            if (node.isStart()) myStart = new Node (x, y, value, i);
            
            // Keep track of how many "ours" nodes there are. We'll use this later
            if (node.isOurs())  myOursCount++;     
        }
    }
}






//
// Prints the matrix. Useful for debugging.
//
void Matrix::printMatrix () const
{
    for (int y = 0; y < myYLen; y++)
    {
        vector <Node> v = myMatrix[y];
        
        for (int x = 0; x < myXLen; x++)
        {
            Node node = myMatrix[x][y];
            cout << node;
        }
        cout << endl;
    }
}


//
// prints out results.
//
void Matrix::printResults() const
{
    cout << "We found " << mySolutionCount << " solutions" << endl;
}




//
// BOOKKEEPERS
// 
Matrix::Matrix ()
{
    myOursCount = 0;
    myXLen      = 0;
    myYLen      = 0;
    myStart     = NULL;
    mySolutionCount = 0;
}


Matrix::~Matrix ()
{
    // nada, for now.
    if (myStart != NULL) delete myStart;
}

