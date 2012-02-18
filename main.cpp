//
// This is main.
//
// Zo Obradovic
//

#include "Matrix.h"




//
// der main
//
int main (int argc, const char * argv[])
{
    // fred
    Matrix fred;
    
    // just in case
    try 
    {
        
        // reads the input from stdin
        fred.read();
        
        // prints the matrix. Only useful for debugging
        fred.printMatrix();
        
        // does most of the work here
        fred.findHamiltonianPath();
        
        // print the results
        fred.printResults();
        
    } 
    
    // woops
    catch ( ... ) 
    {
        return 1;
    }
    
    // and return. happy happy
    return 0;
}

