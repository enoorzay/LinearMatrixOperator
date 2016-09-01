#include "matrix.cpp"
#include <unordered_map>
using namespace std;

class Menu{

	public:

	bool debug;
	unordered_map<string, matrix * >matrices;
  matrix * lastMatrix;
	Menu(bool debugging){
 		debug = debugging;
	}

	void prompt(){

		cout << "Please select an option: " << endl;

		cout << "(1) Declare new matrix." << endl;

		cout << "(2) Act on existing matrix." << endl;

		cout << "(3) Search matrices." << endl;

		cout << "(4) Exit." << endl;


		cout << "Please select an option: " << endl;

	}

	void actions(){
		cout << "Matrix Operations: " << endl;

		cout << "(1) Reduce a matrix." << endl;

		cout << "(2) Multiply two matrices." << endl;

		cout << "(3) Invert a matrix." << endl;

		cout << "(4) Find the determinant of a matrix." << endl;

		cout << "(0) Go Back." << endl;

		cout << "Please select an option: " << endl;

		int decision;
		cin >> decision;
		if (decision == 1){
		reduce();
	 }

	 else if (decision == 2){
	 multiply();
   }

	 else if (decision == 3){
		 inverse();
	 }

	 else if (decision == 4){
		 det();
	 }
	 else if (decision == 0){
		 prompt();
	 }

	 else{
		 cout << " Unexpected input " << endl;
		 actions();
	 }

	}

	void declare(){
		string name;
		cout <<" Please enter the name of the matrix" << endl;
		cin >> name;
		int row;
		int col;
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

		cout << "Enter # of matrix rows: " << endl;
		cin >> row;
		cout << "Enter # of matrix columns: " << endl;
		cin >> col;
		matrix * A = new matrix(name, row,col, debug, augmented);
		A->construct();
		matrices[name] = A;
		lastMatrix = A;
	}

matrix * searchMatrices(){
	string matname;
	cout << "Enter name of matrix" << endl;
	cin >> matname;
	if (matrices[matname] != NULL){
		matrix * temp  = matrices[matname];
		temp->printMatrix();
		lastMatrix = temp;
		return temp;
	}

	else {
		cout << "Matrix not found." << endl;
		return NULL;
	}
}

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

	void multiply(){

	matrix * A = lastMatrixCheck();
cout << "Second matrix:" << endl;

	lastMatrix = NULL;
	matrix * B = lastMatrixCheck();

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

	void inverse(){

		matrix * A = lastMatrixCheck();
		if (A->augmented){
			A->unAugment();
		}
		A->createIdent();
		A->rowReduct(A->nums);
		cout << "FINAL MATRIX: " << endl;
		A->printInverse();
	return;

	}

	void det(){
		matrix * A = lastMatrixCheck();
		if (A->augmented){
			A->unAugment();
		}
		cout << "Determinant is  " << A->findDeterminant() << endl;

	}

};


int main(int argc, char* argv[])
{

	bool debugging;
	char choice;
	bool keepgoing;

	debugging = false;
	if(argc == 2){
		choice = *(argv[1]);

		if (choice == 'x'){
			debugging = true;
			cout << "Debug: ON!" << endl;

		}
	}


	Menu * menu = new Menu(debugging);

	keepgoing = true;
	while (keepgoing){
		menu->prompt();

		int input;
		cin >> input;

		if (input == 0){
			menu->prompt();
		}

		else if (input == 1){
			menu->declare();
		}

		else if (input == 2){
			menu->actions();
		}

		else if (input == 3){
			menu->searchMatrices();

		}

		else if (input == 4){
			return 0;
		}

		else{
			cout << "Input not recognized.";

		}


	}
}
