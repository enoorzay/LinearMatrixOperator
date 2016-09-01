#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <stack>
#include <math.h>
using namespace std;


class matrix {



public:
      bool debug; // whether debug messages are on
	    int rows;
	    int columns;
      int totalpivotcols;
      double ** nums; // Matrix structure
      int solnrows;   // Keeps track of reduced rows
      double ** inverse;  // Structure for inverse
      bool inverting;     // Whether we are looking for an inverse
      bool invertible;  // Whether its invertible
      bool augmented; // Whether its currently augmented or not
      int totalflips;   //  Helps calculate the sign of the determinant
      string name;    // used to identify
      vector<double> pivotelements; // Stores the pivot elements, used for corner calculations
      matrix(void);

// Constructor, n = names r= rows c = columns.. Debugging = choice of debug messages
    matrix(string n, int r, int c, bool debugging, bool aug);

// Function that takes user input for matrix numbers and establishes the structure.
    void construct(void);

// Adds solution column to the matrix, making it augmented.
    void makeAugmented(void);

// Removes the solution column
    void unAugment(void);

    // Public debug access
    void setDebug(bool c);

    // Prints matrix in a semi formatted way
    void printMatrix(void);

    // Swap two rows. Sub is usually the "nums" data value but occasionally we use subsets of it
	void flipRow(double ** sub, double firstrow, double secrow);

    // Push a row to the bottom and pull the other ones up. Usually used for zero rows.
    void pushtoBottom(int pushrow);

    // Row combinations. Sub is the set of nums we work with.
	void addReplace(double ** sub, int tobereplaced, int tobeAdded, int pivotc);

    // Fully reduces matrix to echelon form recursively by starting at the bottom and going up each row.
	bool reduced(int row);

    // Checks for consistency. Is called by rowReduct. If is consistent, this calls reduced () to find the rref.
    bool solveCheck();

    // Finds next pivot column under solnrows. So if solnrows = 2 it ignores rows 1 and 2 to find the next pivot column.
    int findPivot();

    // Main matrix reducer method, delegates to flipRow, pushtoBottom, findPivot, solveCheck etc.
    bool rowReduct(double ** sub);

    // Multiplies two matrices and sets the matrix equal to the product. NOTE: If allocated dimensions dont fit i dont know if this works.
    void  matrixMult(double ** first, double ** sec);

    // Delegation function for matrixMult. For AB it multiplies row of A by column of B, so each call gives one position of product vector
    double rowcolMult(double ** first, double ** sec , double currentrow, double currentcol);

    // Creates Identity matrix used for inverting. Also sets inverting to true.
    void createIdent(void);

    // Prints inverse
    void printInverse(void);

    // Checks if a full row is zero so that consistency can be checked by solveCheck.
    void zeroRowCheck(void);

    //Finds and returns the determinant
    int  findDeterminant(void);

    // Uses diagonal values to find eigenvalues
    void findEigenValues(void);
};


#endif // MATRIX_HPP
