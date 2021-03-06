This program will (eventually) be able to operate on and solve systems of linear equations given in matrix form. It is slowly gaining functionality, and can currently reduce a matrix to reduced echelon form and check for consistency, invert a matrix (if its invertible), find a matrices determinant, and do matrix multiplication.

*USAGE:*
The program has prompts when run, initially bringing up a menu where an input of '1' allows declaration of a matrix, '2' brings up a menu for matrix operations, and '3' searches for a matrix by its name.
Can also add x to program execution (eg ./main x) to get debug messages showing work.
*RECENT ADDITIONS:*
- JUST ADDED: eigenvalues, still very unstable. 
- Storage of multiple matrices at once, so that any can be called for a certain operation.
- Quality of life changes like remembering last matrix altered and offering to use that initially for the next operation.
- Converting between augmented and nonaugmented matrices.
- Determinant calculation.

*NEXT ON LIST TO ADD*
- Eigenvalues and Eigenvectors
- Diagonalization
- Stability
- Clean up code, some functions and variables are never used.
