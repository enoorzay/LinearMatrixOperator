#include "matrix.cpp"

using namespace std;

class Menu{

	public: 

	bool debug; 

	Menu(bool debugging){
 		debug = debugging;
	}

	void prompt(){ 
		cout << "Matrix Operations: " << endl;

		cout << "Please select an option: " << endl;

		cout << "(1) Reduce a matrix to its echelon form." << endl;

		cout << "(2) Multiply two matrices together." << endl;

		cout << "(3) Find the inverse of a matrix. (Must be square)" << endl;

		cout << "(4) Exit" << endl;

		cout << "You can always enter 0 to see this prompt again.";

		cout << "(COMING SOON) - Determine linear dependence/indepence, All matrix mathematical basic operations between each other, mapping transformations, Finding solutions in vector/equation form, and determining span." << endl;

		cout << "Please select an option: " << endl;

	}

	void reduce(){
		int row;
		int col;
		cout << "Matrix Reduction: " << endl;

		cout << "Enter # of matrix rows: " << endl;
		cin >> row;
		cout << "Enter # of matrix columns: " << endl;
		cin >> col; 

		matrix * A = new matrix(row,col, debug); 
		A->construct();
		cout << "FINAL MATRIX: " << endl;
		A->rowReduct(A->nums);
		A->printMatrix();
		return;
		
	}

	void multiply(){
		int row;
		int col; 

		int secrow;
		int seccol; 

		cout << "Enter # of matrix rows: " << endl;
		cin >> row;
		cout << "Enter # of matrix columns: " << endl;
		cin >> col; 

		matrix * A = new matrix(row,col, debug); 
		A->construct();


		cout << "Enter # of matrix rows for matrix 2: " << endl;
		cin >> secrow;
		cout << "Enter # of matrix columns for matrix 2: " << endl;
		cin >> seccol; 

		if (col != secrow){
			cout << "Error incompatible matrices" << endl;
		} 





		matrix * B = new matrix(secrow,seccol, debug); 
		B->construct();

		matrix * C = new matrix(row, seccol, debug); 


		C->matrixMult(A->nums, B->nums);


		cout << "FINAL MATRIX: " << endl;
		C->printMatrix();
		return;

	}

	void inverse(){

		int size;
		cout << "Enter size of matrix dimension: " << endl;
		cin >> size;
		matrix * A = new matrix(size,size, debug); 
		A->construct();


		A->createIdent();
		A->rowReduct(A->nums);
		cout << "FINAL MATRIX: " << endl;
		A->printInverse();

	return;

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
			menu->reduce();
		}

		else if (input == 2){
			menu->multiply();
		}

		else if (input == 3){
			menu->inverse();

		}

		else if (input == 4){
			return 0;
		}

		else{
			cout << "Input not recognized.";

		}

		cout << "Keep going? (Y/N): ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y'){
			keepgoing = true;
		}

		else{
			keepgoing = false;
		}

	}
}

