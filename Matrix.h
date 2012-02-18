//
//  Matrix.h
//  Defines, well, the Matrix class
//
//  Created by Zo Obradovic on 2/1/12.
//

#ifndef QUORA_MATRIX_H
#define QUORA_MATRIX_H

#include "Node.h"
#include <vector>
#include <map>




class Matrix
{
    
  public:
    
    //
    // BEHAVIORS
    // 
    void findHamiltonianPath    ();
    void createAdjacencyList    ();
    void bfs                    ();
    void read                   ();

    void printMatrix            ()      const;
    void printAdjacencyList     ()      const;
    void printResults           ()      const;

    
    
    //
    // BOOKKEEPERS
    //
    Matrix ();
    ~Matrix();
    
    
  private:
    
    //
    // HELPERS
    // 
    Node * up        (const Node const *)        const;
    Node * down      (const Node const *)        const;
    Node * left      (const Node const *)        const;
    Node * right     (const Node const *)        const;
    Node * traverse  (int, int)                  const;
    void findHamiltonianPath  (Node *, int);
    
    Node * upz       (const Node const *)        const;
    Node * downz     (const Node const *)        const;
    Node * leftz     (const Node const *)        const;
    Node * rightz    (const Node const *)        const;
    Node * traversez (int, int)                  const;
    void   bfs       (Node *, int);

    
    
    
    struct NodeCompare
    {
        bool operator() (const Node & s1, const Node & s2) const
        {
            return s1.id() < s2.id();
        }
    };
    
    
    // 
    // INTERNAL TYPEDEFS
    //
    typedef std::vector <Node > NodeVector;
    typedef std::vector <NodeVector> NodeMatrix;
    typedef std::map < const Node, NodeVector, NodeCompare > NodeVectorMap;

    
    
    //
    // PRIVATE MEMBERS
    //
    int     mySolutionCount;
    int     myOursCount;
    int     myXLen;
    int     myYLen;
    Node *  myStart;
    NodeMatrix myMatrix;
    NodeMatrix myAdjacencyList;
    NodeVectorMap myAdjacencyMap;
    
    // these two only used for debugging
    std::vector <Node *> myCurrentPath;
    bool myDebug;
    
};



#endif
