#include "matrix.cpp"
#include <unordered_map>
using namespace std;

// Used for UI
class Menu{

	public:

// debug msgs. activated by ./main x
	bool debug;

// stores all the matrices
	unordered_map<string, matrix * >matrices;

// stores last one worked with for convenience
  matrix * lastMatrix;

	Menu(bool debugging){
 		debug = debugging;
	}

// main prompt
	void prompt(){

		cout << "Please select an option: " << endl;

		cout << "(1) Declare new matrix." << endl;

		cout << "(2) Act on existing matrix." << endl;

		cout << "(3) Search matrices." << endl;

		cout << "(4) Exit." << endl;


		cout << "Please select an option: " << endl;

	}

// Prompt if actions is chosen from the main one
	void actions(){
		cout << "Matrix Operations: " << endl;

		cout << "(1) Reduce a matrix." << endl;

		cout << "(2) Multiply two matrices." << endl;

		cout << "(3) Invert a matrix." << endl;

		cout << "(4) Find the determinant of a matrix." << endl;

		cout << "(0) Go Back." << endl;

		cout << "Please select an option: " << endl;

		// Reads the decision and calls appropriate fxn
		char decision;
		cin >> decision;
		if (decision == '1'){
		reduce();
	 }

	 else if (decision == '2'){
	 multiply();
   }

	 else if (decision == '3'){
		 inverse();
	 }

	 else if (decision == '4'){
		 det();
	 }
	 else if (decision == '0'){
		 prompt();
	 }

// if unexpected input
	 else{
		 cout << " Unexpected input " << endl;
		 actions();
	 }

	}

// Declares a new matrix
	void declare(){
		string name;
		cout <<" Please enter the name of the matrix" << endl;
		cin >> name;
		int row;
		int col;

		// If augmented matrix, the last column is the solution column
		bool augmented;
		cout << "Is this an augmented matrix? [y/n]"  << endl;
		char choice;
		cin >> choice;

		if (choice == 'y' || choice == 'Y'){
			augmented = true;
		}
		else{
			augmented = false;
		}

// size
		cout << "Enter # of matrix rows: " << endl;
		cin >> row;
		cout << "Enter # of matrix columns: " << endl;
		cin >> col;
		matrix * A = new matrix(name, row,col, debug, augmented);

		// Fill in with numbers
		A->construct();

		//store in hash table with its name as its key
		matrices[name] = A;

		// for convenience
		lastMatrix = A;
	}

// Searches for a matrix by its name in the hash table
matrix * searchMatrices(){
	string matname;
	cout << "Enter name of matrix" << endl;
	cin >> matname;

	// If something stored there print it
	if (matrices[matname] != NULL){
		matrix * temp  = matrices[matname];
		temp->printMatrix();
		lastMatrix = temp;
		return temp;
	}

// if nothing there
	else {
		cout << "Matrix not found." << endl;
		return NULL;
	}
}

// Used by operation methods, offers to use the last matrix altered, if not, allows for a search
// for desired matrix to operate on
matrix * lastMatrixCheck(){
	matrix * mat;
	if (lastMatrix){
		cout << "Use last matrix? (" << lastMatrix->name << ") [y/n]" << endl;
		char choice;
		cin >> choice;

		if (choice == 'y' || choice == 'Y'){
			mat = lastMatrix;
			return mat;
		}
	}
	else{
		mat = searchMatrices();
	}
}

// Called when reducing is selected. Augments matrix if its not already.
	void reduce(){
		matrix * A;
		A = lastMatrixCheck();

		if (!(A->augmented)){
			if (debug){
				cout << "Not an augmented matrix, augmenting.. " << endl;
			}
			A->makeAugmented();
		}
		A->rowReduct(A->nums);
		A->printMatrix();
		return;

	}


// Called if multiply is selected. Gets two matrices and multiplies them.
	void multiply(){

	matrix * A = lastMatrixCheck();
cout << "Second matrix:" << endl;

// Reset lastmatrix so doesnt offer it again
	lastMatrix = NULL;

	matrix * B = lastMatrixCheck();

// Dont want augmented matrices in multiplication
if (A->augmented){
	A->unAugment();
}

if (B->augmented){
	B->unAugment();
}

		if (A->columns != B->rows){
			cout << "Error incompatible matrices" << endl;
			return;
		}


		matrix * C = new matrix("temp", A->rows,B->columns, debug, false);

		C->matrixMult(A->nums, B->nums);

		cout << "FINAL MATRIX: " << endl;
		C->printMatrix();
		return;

	}

// Finds inverse
	void inverse(){

		// to select a matrix
		matrix * A = lastMatrixCheck();

		// Dont want augmented matrix
		if (A->augmented){
			A->unAugment();
		}

		if ((A->rows) != (A->columns)){
			cout << "Must be a square matrix!" << endl;
			return;
		}

		// Uses another object to store identity matrix which is altered to find inverse
		A->createIdent();

		//By reducing the matrix to its identity, and doing the same operations on what was originally
		// the identity matrix, we can find the inverse.
		A->rowReduct(A->nums);
		cout << "FINAL MATRIX: " << endl;
		A->printInverse();
	return;

	}

// Finds determinate
	void det(){
		matrix * A = lastMatrixCheck();
		if (A->augmented){
			A->unAugment();
		}

		if ((A->rows) != (A->columns)){
			cout << "Must be a square matrix!" << endl;
			return;
		}
		cout << "Determinant is  " << A->findDeterminant() << endl;

	}

};


int main(int argc, char* argv[])
{

	bool debugging;
	char choice;
	bool keepgoing;

// reads for debug arg
	debugging = false;
	if(argc == 2){
		choice = *(argv[1]);

		if (choice == 'x'){
			debugging = true;
			cout << "Debug: ON!" << endl;

		}
	}


	Menu * menu = new Menu(debugging);

// loop for user input
	keepgoing = true;
	while (keepgoing){
		menu->prompt();

		char input;
		cin >> input;

		// read primary input and call appropriate menu fxns
		if (input == '0'){
			menu->prompt();
		}

		else if (input == '1'){
			menu->declare();
		}

		else if (input == '2'){
			menu->actions();
		}

		else if (input == '3'){
			menu->searchMatrices();

		}

		else if (input == '4'){
			return 0;
		}

		else{
			cout << endl;
			cout << "Input not recognized." << endl;
		}


	}
}
