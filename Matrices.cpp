// matlib24.cpp : This file contains the 'main' function and others to test matrix routines
//

// matlib24.cpp : A simple matrix library program.
// Template Written by Prof Richard Mitchell    6/12/23
// Adapted by:   << Hayden Scott >>

#include <string>
#include <iostream>
using namespace std;

const int maxM = 16;	// allows for matrices up to size 4*4

struct myMat {			// structure to store a matrix
	int numRows;		// number of rows
	int numCols;		// number of columns
	int data[maxM];		// data are stored in row order
};

myMat zeroMat(int r, int c) {
	// create a matrix with r rows and c columns, filled with zeros
	myMat m;			// define matrix
	m.numRows = r;		// set size
	m.numCols = c;
	for (int ct = 0; ct < maxM; ct++) m.data[ct] = 0;	// set elems to 0
	return m;			// return matrix
}

int getIndex(myMat m, int r, int c) {
	// returm index of element in row r, col c of matrix m
	return r * m.numCols + c;
}

myMat matError(string errstr) {
	// if this is called, an error has occured ... output errstr and return 0 size myMat
	cout << "Error : " << errstr << "\n";
	return zeroMat(0, 0);
}

int intError(string errstr) {
	// if this is called, an error has occured ... output errstr and return 0 
	cout << "Error : " << errstr << "\n";
	return 0;
}

myMat mFromStr(string s) {
	// create a matrix from string s
	// string of form "1,2;3,4;5,6"   ; separates rows and , separates columns ... No error check
	int ms;
	if (s.length() > 0) ms = 1; else ms = 0;
	myMat m = zeroMat(ms, ms);						// is s empty create 0*0 matrix, else start with 1*1 matrix
	int mndx = 0;									// used to index into array
	string sub = "";								// sub string - numbers between , or ; set empty
	for (int ct = 0; ct < s.length(); ct++) {		// each char in turn
		if ((s[ct] == ',') || (s[ct] == ';')) {	// if , or ; then sub contains number
			m.data[mndx++] = stoi(sub);				// convert number to integer, put in data array
			sub = "";								// clear sub string
			if (s[ct] == ';') m.numRows++;			// if found ; indicates an extra row
			else if (m.numRows == 1) m.numCols++;	// if , then (if in row 1) increase count of columns
		}
		else sub = sub + s[ct];						// add character to sub string
	}
	if (sub.length() > 0) m.data[mndx++] = stoi(sub);// add last sub string
	return m;
}

void printMat(const char* mess, myMat m) {
	// mess is string to be printed, followed by matrix m
	cout << mess << " = " << "\n";				// print message
	for (int r = 0; r < m.numRows; r++) {		// do each row
		for (int c = 0; c < m.numCols; c++)		// do each column
			cout << m.data[getIndex(m, r, c)] << "\t";	// outputing the element then tab
		cout << "\n";							// output new line at end of row
	}
	cout << "\n";								// and end of Matrix
}


myMat mGetRow(myMat m, int row) {
	// create a matrix from m, having one row
	myMat res = zeroMat(1, m.numCols);		// create a matrix of 1 row
	for (int col = 0; col < m.numCols; col++)		// for each element in row
		res.data[col] = m.data[getIndex(m, row, col)];		// copy col element to res
	return res;
}

myMat mGetCol(myMat m, int col) {
	// create a matrix from m, having one col
	myMat res = zeroMat(m.numCols, 1);	// adjust arguments so column vector
	for (int row = 0; row < m.numCols; row++)
		res.data[col] = m.data[getIndex(m, row, col)];
	// put in code
	return res;
}

myMat mSetCol(myMat m, int col, myMat v) {
	// insert v into given col in m
	if (m.numRows != v.numRows)
		return matError("Matrix/Vector should have same number of rows");
	else {
		myMat res = m;
		for (int row = 0; row < m.numRows; row++)
			res.data[getIndex(m, row, col)] = v.data[row];
		return res;
	}
}

int dotProd(myMat v1, myMat v2) {
	// calculate the dot product of two vectors v1 and v2, each of which could be eitherrow or column vectors
	myMat prod = zeroMat(0,0); // initialising a product variable
	int res{}; // initialising a variable for the result
	// I want to have a for loop that steps through each item in both arrays and multiplies them together and then places them in a new array called prod
	if (v1.numCols != v2.numRows || v1.numRows != v2.numCols) {		// Error catching.
		matError("Invalid vector layout");
		return 0;
	}
	for (int i = 0; i < v1.numRows; i++) { 
		for (int j = 0; j < v2.numCols; j++) {
			res += v1.data[i, j] * v2.data[i, j];
		}
	}
	/* then I want to have a for loop that steps through each item in the product array and increments the res variable by 
	this amount thus res will be the sum of each item in prod */
	/*for (int i = 0; i < prod.numRows; i++) {
		res += prod.data[i];
	}*/
	// Rewrote this part so that the calculation places directly into result which makes more sense.

	return res;
}

void testVecs(myMat m1, myMat m3) {
	// test vector routines ... get row from m1, col from m3, do dot product of these
	cout << "Testing Vector routines" << "\n";
	printMat("m1 row 0", mGetRow(m1, 0));	// display row 0 of m1
	printMat("m3 col 1", mGetCol(m3, 1));	// display col 1 of m3
	//	cout << "Dot prod of these is " << dotProd(mGetRow(m1, 0), mGetCol(m3, 1)) << "\n\n";
	//	cout << "Dot prod of m1 row 1 and m3 row 1 " << dotProd(mGetRow(m1, 0), mGetRow(m3, 1)) << "\n\n";
}


myMat mTranspose(myMat m) {
	// generate a new matrix which is the transpose of m
	myMat res = zeroMat(0, 0);		// change arguments
	// write code to do transpose
	/* If each item within a matrix is indexed as I, J then that means to make the transpose matrix, I need to 
	change each item to be J, I thus flipping the rows and columns. */
	
	for (int i = 0; i < m.numRows; i++) {
		for (int j = 0; j < m.numRows; j++) {
			int temp = res.data[i];		// Here I need to make a temp variable to store the i value of res so it is not overwritten.
			res.data[i] = m.data[j];
			res.data[j] = temp;
		}
	}

	return res;
}

myMat mAdd(myMat m1, myMat m2) {
	myMat res = zeroMat(0, 0);
	// create a new matrix whose elements are the sum of the equiv elements in m1 and m2
	// if time add code to check matrices of right size
	if (m1.numRows != m2.numRows || m1.numCols != m2.numCols) {				// An if statement that checks that both matrices are equal size rows.
		matError("Matrices size are not equal");	// Returns this error statement if they are not.
		return zeroMat(0,0);
	}
	// change arguments
	// write code to do add
	// I want to create a for loop that steps through each item in both matrices and adds them together.

	for (int i = 0; i < m1.numRows; i++) {
		for (int j = 0; j < m2.numRows; j++) {
				res.data[i, j] = m1.data[i, j] + m2.data[i, j];
		}
	}
	return res;
}

myMat mScalarMultDiv(myMat m, int s, int isMult) {
	// multiply or divide all elements in m by s
	myMat res = zeroMat(0, 0);		// change arguments
	// write code to do multiply or divide by scalar
	// Checking if user wishes to divide or multiply. This part might later be made redundant by the parameters or it might make one of the parameters redundant.
	cout << "Multiply or divide? M/D " << endl;
	string choice;
	while (true) {
		cin >> choice;
		if (choice != "M" || choice != "D") {
			cout << "Invalid please retry" << endl;
		}
		else {
			break;
		}
	}
	if (choice == "A") {
		cout << "Multiplying..." << endl;
		for (int i = 0; i < m.numCols; i++) {
			for (int j = 0; j < m.numRows; j++) {
				res.data[i, j] = m.data[i, j] * s;	// Stepping through each item of both matrices and multiplying them by s
			}
		}
	}
	else {
		cout << "Dividing..." << endl;
		for (int i = 0; i < m.numCols; i++) {
			for (int j = 0; j < m.numRows; j++) {
				res.data[i, j] = m.data[i, j] / s;	// Doing the same but with division.
			}
		}
	}
	return res;
}

myMat mMult(myMat m1, myMat m2) {
	// generate a matrix which is the product of m1 and m2
	// if time add code to check matrices of right size
	myMat res = zeroMat(0, 0);		// change arguments
	// write code to do multiply
	if (m1.numCols != m2.numRows || m1.numRows != m2.numCols) {
		matError("Matrices sizes are invalid");
		return zeroMat(0, 0);
	}

	return res;
}

void testMatOps(myMat m1, myMat m2, myMat m3) {
	// test matrix operations m1 + m2; m1 + m3 (not poss) m1 + m3'; m1 * m3; m3 * m2
	cout << "Testing Add, Transpose, Multiply routines" << "\n";
	printMat("m1+m2", mAdd(m1, m2));
	printMat("m1 + m3", mAdd(m1, m3));
	printMat("m1 + m3'", mAdd(m1, mTranspose(m3)));
	printMat("m1*m2", mMult(m1, m3));
	printMat("m2*m1", mMult(m3, m1));
	printMat("m1*m3", mMult(m1, m2));
}


/*   commented out code you will do as part of Summative Assessment later in term


myMat mSubMat(myMat m, int row, int col) {
	// return matrix m but omitting specified row and column
	// if time add code to check matrices of right size
	myMat res = zeroMat(0,0);		// change arguments
		// write code to do sub mat
	cout << zeroMat << endl;
	return res;
}

/*
int mDet(myMat m) {
	// compute determinant of matrix m
	return 0;		// change this ... initially handcode for 1*1 and 2*2 ... if brave do 3*3 or 4*4 recursively
}

myMat mAdj(myMat m) {
	// return adjoint of matrix m     assume 2*2 initially
	// if time add code to check matrices of right size
	myMat res = zeroMat(0,0);		// change arguments
		// write code to do adjoint initially handcode for 1*1 and 2*2 ... if brave do 3*3 or 4*4 recursivel
	return res;
}

void testMatEqn (myMat A, myMat b) {
	// solve Ax = b using Cramer  and using Adjoint
	// This is for assessment later in term
}

*/
int main()
{
	cout << "vl024813\n";	// change to your student number
	myMat m1, m2, m3;						// create  matrices

	m1 = mFromStr("9,6,8;7,8,10");			// change numbers to those in A from Q1 on web page, as specified on the sheet
	m2 = mFromStr("10,9,6;8,8,7");			// ditto but B
	m3 = mFromStr("7,7;2,8;7,8");			// ditto  but C
	printMat("m1", m1);						// display m1
	printMat("m2", m2);						// display m2
	printMat("m3", m3);						// display m3

	testVecs(m1, m3);						// test the vector routines
	testMatOps(m1, m2, m3);					// test the add, transpose and multiply

	return 0;
}