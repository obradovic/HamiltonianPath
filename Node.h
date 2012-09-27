//
//  This defines the Node class. Used as a Node of the graph
//
//  Created by Zo Obradovic on 2/1/12.
//

#ifndef QUORA_NODE_H
#define QUORA_NODE_H

// includes
#include <iostream>
#include <sstream>
#include <vector>



class Node 
{
    
  public:
    
    //
    // CLASS CONSTANTS
    //
    typedef enum
    {
        OURS    = 0,
        THEIRS  = 1,
        START   = 2,
        STOP    = 3
    } 
    Value;
     
    
    
    //
    // OBJECT ACCESSORS
    // 
    int x           () const;
    int y           () const;
    Value value     () const;
    int id          () const;

    
    //
    // OBJECT ATTRIBUTES
    //
    bool isVisited  () const;
    bool isOurs     () const;
    bool isTheirs   () const;
    bool isStart    () const;
    bool isStop     () const;
    
    
    //
    // OBJECT MUTATORS
    // 
    void setVisited (bool);
    void setId      (int);
    void x          (int);
    void y          (int);

    
    
    //
    // BOOKKEEPERS
    //
    Node  ();
    Node  (int, int, int, int);   // x, y, value, id
    Node  (const Node &);
    ~Node ();
    
    
    
    
  protected:
    
    
    // Bookkeeper helpers
    void _zero          ();                    // zero's out values, pointers, etc 
    void _initialize    (int, int, int, int);  // initializes state to the passed-in values
    

    // say hello to my little friend
    friend std::ostream & operator << (std::ostream &, const Node &);
    
  
    
    
  private:
    
    // 
    // PRIVATE MEMBERS
    //
    int     myX;
    int     myY;
    Value   myValue;
    bool    myVisited;
    int     myId;

};



#endif
