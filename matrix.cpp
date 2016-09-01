//TODO: Several methods have excessive checks, and a few arent used. Optimize.
// Implement Eigenvalues and NulSpace/ColSpace as well as IMT Stuff.

 #include "matrix.hpp"

using namespace std;

matrix::matrix(void)
{
	rows = 0;
	columns = 0;
	inverting = false;
  totalflips = 0;
  totalpivotcols = 0;
}

// Main constructor used
matrix::matrix(string n, int r, int c, bool debugging, bool aug){
name = n;
  rows = r;
	columns = c;
	nums = new double*[rows];	// Rows of matrix
	debug = debugging;				// Debug msgs
	totalpivotcols = 0;
	solnrows = 0;					// No rows reduced yet
  augmented = aug;
  totalflips = 0;

  if (!augmented){
    columns++;  //allocate extra spot in case we ever become augmented and need it
  }
	// Allocates space for each column in every row.
	for (int i = 0; i < rows; i++){
		nums[i] = new double[columns];
	}

  if (!augmented){
    columns--;
  }
}


// Takes in user input to fill the matrix with numbers
void matrix::construct(void){
	for (double i =0; i < rows; i++){
		cout << "Enter values for row: " << i+1 << endl;
		for (double j=0; j < columns; j++){
			cin >> nums[(int)i][(int)j];
		}
	}
}


// Prints matrix in somewhat formatted way and checks for invertibility.
void matrix::printMatrix(void){

	if (debug){
		if (invertible){
			cout << "Matrix is invertible" << endl;
		}
	}


	for (int i =0; i < rows; i++){
		for (int j=0; j < columns; j++){
      if (augmented){
        if (j +1 == columns){
            cout << " | ";
        }
      }
			cout << nums[i][j] << " ";

		}
		cout << endl;
	}
	return;

}

void matrix::makeAugmented(){
  columns++;
  if (nums[0][columns -1] != 0 ){
    cout << "Use previous solution values for this matrix? [y/n]" << endl;
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y'){
        augmented = true;
        return;

    }
  }
  cout << "Enter values of solution " << endl;
  for (int i = 0; i < rows; i++){
    cin >> nums[i][columns-1];
  }
  augmented = true;
}

// Remove solution column
void matrix::unAugment(){
  // 1 less col
  columns--;
  augmented = false;
}

// Swaps two rows
void matrix::flipRow(double ** sub, double firstrow, double secrow){
  totalflips++;
	double  tempf[(int)columns];	// temp array for values of first row
	double temps[(int)columns]; 	// temp array for values of second row

	if (debug){
		cout << "Flipping rows: " << firstrow << " and " << secrow << endl;
	}

	// Set values of the temp row structures to their corresponding row values
	for (double i =0; i< columns; i++){
		tempf[(int)i] = sub[(int)firstrow][(int)i];
		temps[(int)i] = sub[(int)secrow][(int)i];
	}

	// To switch, the values of rows are set to equal the opposite temp row array.
	for (double i=0; i < columns; i++){
		sub[(int)firstrow][(int)i] = temps[(int)i];
		sub[(int)secrow][(int)i] = tempf[(int)i];
	}



}

// Pushes row to bottom, pushing others up. used for zero rows
// I THINK THIS ISNT USED AND DOESNT WORK
void matrix::pushtoBottom(int pushrow){

	for (int i = pushrow; i < rows-1; i++){
		flipRow(nums, i, i+1);
	}

}

// Adds a row to another to make its columns below the pivot column 0.
void matrix::addReplace(double ** sub, int tobereplaced, int tobeAdded, int pivotc ){

	// tobereplaced and tobeAdded are row numbers, we assume tobeAdded has a 1 in the pivot column and
	// add that row to tobereplaced until its values under the pivot column are 0.

	//Gets negative value of tobereplaced column since for any x it can be, we want to multiply 1 by -x so that
	// adding the rows gives a 0 under the pivot col.
	double coef = 0 -nums[tobereplaced][pivotc];

if (debug){
  cout << "Adding " << coef << "*row" << tobeAdded << " to " << tobereplaced << endl;
}
	// Starting at the pivot column (since the rest will be 0 behind it) to the last column we add the appropriate row values
	for (int i = pivotc; i < columns; i++){

		double sum = ( (coef * nums[tobeAdded][i] ) + ( nums[tobereplaced][i]) );

		nums[tobereplaced][i] = sum;
	}
}


// Is called for each row once in reduced form starting with last row bysolveCheck, once proven consistent.
// It then calls recursively up to the top. Makes sure value at pivot column
// is 1 and that the columns above it are 0.
bool matrix::reduced(int row){

	int pivotcol = -1;

	// Recursion is done we've reached the top
	if (row == -1){
    if  (debug){
      cout << "Reached the top, done reducing!" << endl;
    }
		return true;
	}

	// Finds pivot col. NOTE: this should be delegatable to findPivot
	for (int currentcol =0; currentcol <columns;currentcol++){
		if (nums[row][currentcol] != 0){
			pivotcol = currentcol;
		}

		// breaks once pivotcol is found.
		if (pivotcol != -1){
			break;
		}
	}

	// If no pivot col found and at the top we're done. Otherwise move up a row, this is a zero row.
	if (pivotcol == -1){
		if (row <=1){
			return true;
		}
		else{
			return reduced(row-1);
		}
	}

	// We want the pivotcol value to be 1 so we divide its entire row by itself if it isnt 1.
	if (nums[row][pivotcol] != 1 && nums[row][pivotcol] != 0){
		for (int i =0; i < columns; i++){
			nums[row][i] = nums[row][i] / nums[row][pivotcol];
		}
	}




	// Goes up from pivot col all the way to the top, making sure each column directly above it are 0, if not
	// calls addReplace to make it so.
	for (int i = row -1; i >= 0; i--){
		if (nums[i][pivotcol] !=0){
      if (debug){
        cout << "Value above pivot column is not 0!" << endl;
      }
			addReplace(nums, i, row, pivotcol);

			if (inverting){
				addReplace(inverse, i, row, pivotcol);
			}
		}

	}
	// If done
	if (row <= 1){
		return true;
	}

	// Otherwise keep going up.
	else{
		return reduced(row-1);
	}

}

//Checks if matrix is consistent, called by rowReduct after pivot columns are found.
// If consistent, calls reduced func to rref.
bool matrix::solveCheck(){
	//debug msg
	if (debug){
		cout << "Checking if" << endl;
		printMatrix();
		cout << "is consistent " << endl;
	}

	//Whether the row has been all zeroes
	//if last value isnt zero in augmented matrix inconsistent
	bool zerorow;


	//Loop through rows
	for (int i = rows -1; i >= 0; i--){

		// Each row is initially treated as a zero row.
		zerorow = true;

		// As you go through the columns of a row, if a nonzero is seen the row is marked
		for (int j =0; j < columns-1; j++){
			if (nums[i][j] != 0){
				zerorow = false;
			}
		}

		// If row was all zeroes but last value isnt, have 0 = nonzero: inconsistent.
		if (nums[i][columns-1] != 0){
			if (zerorow == true){
				cout << "Inconsistent" << endl;
				return false;
			}

		}
	}

	// This assumes the matrix is augmented, so all columns except the last should be a pivot column to be invertible
	if (totalpivotcols == columns - 1){
		invertible = true;
	}

	if (debug){
		cout << "Consistent, reducing..." << endl;
	}

	// I'm not sure why this is minus two. But it works atm
	return reduced(rows-1);
}

// Finds a pivot column in rows under Solnrow data value. Need to delegate to this more.
int matrix::findPivot(){
	int pivotcol;
	int pivotrow;

	// For each column
	for (double i =0; i < columns; i++){

		// Go down each row to see which is nonzero at the earliest column

		for (double j = solnrows; j < rows;j++){

			double current = nums[(int)j][(int)i];	// Value at current matrix spot

			// If nonzero we found a pivot column.
			if (current != 0){
				pivotcol = i;
				pivotrow = j;
				totalpivotcols++;
				if (debug){
					cout << "Pivot at column " << pivotcol << endl;
				}

				// Flip the row with the pivot column to the top of the rows not yet in solnrows.
				if ((pivotrow > solnrows) && solnrows >= 0){
					flipRow(nums, pivotrow, solnrows);
				}

				// Have to do the same to inverse if we're finding it. Instead of treating inverse like an augmented matrix, I just start it
				// as an identity matrix separate from the main matrix, but as I reduce the matrix to its reduced form (eventually ideally becoming the identity matrix)
				// I do the same to the identity matrix so that once the main matrix is the identity matrix, the inverse structure will correctly be the inverse of the matrix.

				if (inverting){
					flipRow(inverse, solnrows, pivotrow);


				}

				return pivotcol;
			}

		}

	}
	// If we reached here there are no mroe pivot columns?
	return solveCheck();
}

// Main fxn for reducing rows. Sub can be any subset of nums from the matrix or possibly for diff uses in the future.
bool matrix::rowReduct(double ** sub){

	// First get pivot column and its element.
	int pivotcol;
	pivotcol = -1;
	pivotcol = findPivot();
	double pivotelement;
	pivotelement = nums[solnrows][pivotcol];
pivotelements.push_back(pivotelement);

// If pivot column has nonzero and nonone number, divide the row by the pivot element so that its 1 at the pivot column.
	for (int i =0; i < columns; i++){
		if (nums[solnrows][i] != 0 && nums[solnrows][i] != 1){


			nums[solnrows][i] = nums[solnrows][i]/pivotelement;
			if (inverting){
					inverse[solnrows][i] = (inverse[solnrows][i])/pivotelement;

			}
		}
	}

	// Starting at the unsolved rows, everything above doesnt matter once we go down each row.
	for (int i = solnrows+1; i < rows; i++){

		if (debug){
			cout << " Now checking values after row " << solnrows << "on column " << pivotcol <<
			" to make them 0 " << endl;
		}


		// uses the pivot column which now has a 1 as its value, and add multiples of that row to get
		// zeroes in all columns under it.

		double temp = nums[i][pivotcol];
		if (temp != 0){
			if (debug){
				cout << temp<< " appears to be under pivot column! Zeroing it out." << endl;
			}

			addReplace(nums, i, solnrows, pivotcol);

			if (inverting){
				addReplace(inverse, i, solnrows, pivotcol);
			}
		}


	}

	// once that row is done we can ignore it and move down
	solnrows++;

	// Not done yet, solnrows is incremented so we call recursively, with each solved row being ignored in the next iteration.
	if (solnrows < rows){
		return rowReduct(nums);
	}

	// once down use solvecheck to ensure consistency before we try to make it rref.
	else{

		return solveCheck();


	}

}

// Multiplies nums of first and second (which are matrix structures) and sets this matrix's numbers equal to the product.
void matrix::matrixMult(double ** first, double ** sec){

	// For each row
	for (double srow =0;srow < rows; srow++){

		// Go to each column
		for (double scol =0; scol < columns; scol++){

				if (debug){
					cout << "Calculating row: " << srow << " column: " << scol << " of solution: " << endl;
				}
				// The number at this position in the product is the row of first * column of second.
				// Delegate to rowcolMult. So for row1 col1 of product its row1 of first times col1 of sec.

				nums[(int)srow][(int)scol] = rowcolMult(first, sec, srow, scol);

				if (debug){
					cout << "FOUND: "<< nums[(int)srow][(int)scol] << endl;
				}


		}


	}

}

// Called for each space row m col n in a product vector and solves for that space by multiplying
// row m of the first matrix with coln of the second.
double matrix::rowcolMult(double ** first, double ** sec, double currentrow, double currentcol){
		double sum = 0;

		// So move along the row of the first
		for (double srow =0;srow < columns; srow++){



			if (debug){
				cout << "(" << first[(int)currentrow][(int)srow] << " * " <<  sec[(int)srow][(int)currentcol] << ")";
				if (srow != columns){
					cout << " + ";
				}
			}


			// And multiply it by the corresponding column of second in that row. Sum for the whole row col addition
			sum += (first[(int)currentrow][(int)srow] * sec[(int)srow][(int)currentcol]);

		}
		if (debug){
			cout << " = " << sum << endl;
		}
		return sum;
}

//Establishes finding an inverse matrix. Sets up inverse as the identity matrix and sets inverting to true.
// For each operation we do to the main matrix to reduce it, we do the same to this identity matrix so that once the original
// matrix is completely reduced this will be the inverse matrix.
void matrix::createIdent(){

	// Allocate memory
	inverse = new double*[(int)rows];
	for (double i = 0; i < rows; i++){

		inverse[(int)i] = new double[(int)columns];
	}

	// Establishes identity matrix
	for (int i = 0; i < rows; i++){
		for (int j =0; j < columns; j++){
			if (i == j){
				inverse[i][j] = 1;
			}
			else {
				inverse[i][j] = 0;
			}
		}
	}

	// So we know to act on the inverse matrix structure while reducing as well
	inverting = true;
}

// Prints inverse
void matrix::printInverse(void){

	for (double i =0; i < rows; i++){
		for (double j=0; j < columns; j++){
			cout << inverse[(int)i][(int)j] << " ";
		}
		cout << endl;
	}

}

// Solves for the determinant
int matrix::findDeterminant(void){

  // Dont want to work with augmented matrix
  if (augmented){
    unAugment();
  }

  // Reduce the row, this function also fills up the vector for pivot elements, which are the diagonal
rowReduct(nums);

//Det is 0 if not invertible
if (pivotelements.size() != columns){
  return 0;
}
  double determinant;
      determinant = pivotelements[0];

      if (debug){
        cout << "Determinant is " << pivotelements[0];
      }

      // Multiply the diagonal values
      for (int i =1; i < pivotelements.size(); i++){
          determinant= determinant * pivotelements[i];
          if (debug){
            cout << "  *  " << pivotelements[i];
          }
      }
      cout << endl;

      // Flip signs for each pair of rows we intercanged
      double coefficient = pow(-1, totalflips);
      determinant = determinant * coefficient;
      return determinant;
  }
