// matlib24.cpp : This file contains the 'main' function and others to test matrix routines
//

// matlib24.cpp : A simple matrix library program.
// Template Written by Prof Richard Mitchell    6/12/23
// Adapted by:   << Hayden Scott >>

#include <string>
#include <iostream>

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

myMat matError(std::string errstr) {
	// if this is called, an error has occured ... output errstr and return 0 size myMat
	std::cout << "Error : " << errstr << "\n";
	return zeroMat(0, 0);
}

int intError(std::string errstr) {
	// if this is called, an error has occured ... output errstr and return 0 
	std::cout << "Error : " << errstr << "\n";
	return 0;
}

myMat mFromStr(std::string s) {
	// create a matrix from string s
	// string of form "1,2;3,4;5,6"   ; separates rows and , separates columns ... No error check
	int ms;
	if (s.length() > 0) ms = 1; else ms = 0;
	myMat m = zeroMat(ms, ms);						// is s empty create 0*0 matrix, else start with 1*1 matrix
	int mndx = 0;									// used to index into array
	std::string sub = "";								// sub string - numbers between , or ; set empty
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
	std::cout << mess << " = " << "\n";				// print message
	for (int r = 0; r < m.numRows; r++) {		// do each row
		for (int c = 0; c < m.numCols; c++)		// do each column
			std::cout << m.data[getIndex(m, r, c)] << "\t";	// outputing the element then tab
		std::cout << "\n";							// output new line at end of row
	}
	std::cout << "\n";								// and end of Matrix
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
	int res = 0; // initialising a variable for the result
	
	for (int i = 0; i < v2.numCols*v2.numRows; i++) {
		res += v1.data[i] * v2.data[i];
	}

	return res;
}

void testVecs(myMat m1, myMat m3) {
	// test vector routines ... get row from m1, col from m3, do dot product of these
	std::cout << "Testing Vector routines" << "\n";
	printMat("m1 row 0", mGetRow(m1, 0));	// display row 0 of m1
	printMat("m3 col 1", mGetCol(m3, 1));	// display col 1 of m3
	std::cout << "Dot prod of these is " << dotProd(mGetRow(m1, 0), mGetCol(m3, 1)) << "\n\n";
	std::cout << "Dot prod of m1 row 1 and m3 row 1 " << dotProd(mGetRow(m1, 0), mGetRow(m3, 1)) << "\n\n";
}


myMat mTranspose(myMat m) {
	// generate a new matrix which is the transpose of m
	myMat res = zeroMat(m.numCols, m.numRows);		// change arguments
	// write code to do transpose
	/* If each item within a matrix is indexed as I, J then that means to make the transpose matrix, I need to 
	change each item to be J, I thus flipping the rows and columns. */
	
	for (int i = 0; i < m.numCols; i++) {
		for (int j = 0; j < m.numRows; j++) {
			int temp = res.data[i];		// Here I need to make a temp variable to store the i value of res so it is not overwritten.
			res.data[i] = m.data[j];
			res.data[j] = temp;
		}
	}

	return res;
}

myMat mAdd(myMat m1, myMat m2) {
	myMat res = zeroMat(m1.numRows, m2.numCols);
	// create a new matrix whose elements are the sum of the equiv elements in m1 and m2
	// if time add code to check matrices of right size
	// change arguments
	// write code to do add
	// need a for loop that steps through each item in both matrices and adds them together.

	if (m1.numCols == m2.numCols && m1.numRows == m2.numRows) { 
		for (int i = 0; i < m1.numRows*m1.numCols; i++) {
			res.data[i] = m1.data[i] + m2.data[i];
		}
		return res;
	}
	else {
		matError("Matrices are not of equal size");
	}
}

myMat mScalarMultDiv(myMat m, int s, int choice) {
	// multiply or divide all elements in m by s
	myMat res = zeroMat(m.numRows, m.numCols);		// change arguments
	// write code to do multiply or divide by scalar
	// Checking if user wishes to divide or multiply. This part might later be made redundant by the parameters or it might make one of the parameters redundant.
	// The choice parameter I have added. It is set so that 0 = multiply and 1 = divide.
	if (choice == 0) {
		for (int i = 0; i < m.numCols; i++) {
			for (int j = 0; j < m.numRows; j++) {
				res.data[getIndex(m, i, j)] = m.data[getIndex(m, i, j)] * s;	// Stepping through each item of both matrices and multiplying them by s
			}
		}
	}
	else if (choice == 1) {
		if (s == 0) {
			std::cout << "Error: cannot divide by zero";
			return zeroMat(0,0);
		}
		else {
			for (int i = 0; i < m.numCols; i++) {
				for (int j = 0; j < m.numRows; j++) {
					res.data[getIndex(m, i, j)] = m.data[getIndex(m, i, j)] / s;	// Doing the same but with division.
				}
			}
		}
	}
	else {
		std::cout << "Error: Invalid argument for choice";
	}
	
	return res;
}

myMat mMult(myMat m1, myMat m2) {
	// generate a matrix which is the product of m1 and m2
	// if time add code to check matrices of right size
	// write code to do multiply
	
	if (m1.numCols != m2.numRows) {
		return matError("Matrices sizes are invalid for multiplication");;
	}
	myMat res = zeroMat(m1.numRows, m2.numCols);		// change arguments
	for (int i = 0; i < m1.numRows; i++) {
		for (int j = 0; j < m2.numCols; j++) {
			for (int k = 0; k < m1.numCols; k++) {
				res.data[getIndex(res, i, j)] += m1.data[getIndex(m1, i, k)] * m2.data[getIndex(m2, k, j)];
			}
		}
	}
	return res;
}

void testMatOps(myMat m1, myMat m2, myMat m3) {
	// test matrix operations m1 + m2; m1 + m3 (not poss) m1 + m3'; m1 * m3; m3 * m2
	std::cout << "Testing Add, Transpose, Multiply routines" << "\n";
	printMat("m1+m2", mAdd(m1, m2));
	printMat("m1 + m3", mAdd(m1, m3));
	printMat("m1 + m3'", mAdd(m1, mTranspose(m3)));
	printMat("m1*m2", mMult(m1, m2));
	printMat("m3*m2", mMult(m3, m2));
	printMat("m1*m3", mMult(m1, m2));
	printMat("m1*m3", mScalarMultDiv(m1, 3, 0));
}


/*   commented out code you will do as part of Summative Assessment later in term */


myMat mSubMat(myMat m, int row, int col) {
	// return matrix m but omitting specified row and column
	// if time add code to check matrices of right size
	myMat mSub = zeroMat(m.numRows-1,m.numCols-1);		// change arguments
	//mSub.numRows = m.numRows - 1;
	//mSub.numCols = m.numCols - 1;
	// Created a matrix with one fewer row and column than the matrix parsed in.
	int subRow = 0;
	for (int i = 0; i < m.numRows; i++) {
		if (i == row) {
			continue;
		}
		int subCol = 0;
		for (int j = 0; j < m.numCols; j++) {
			if (j == col) {
				continue;
			}
			// if i or j matches the row or column parsed into this function it skips over that data value thus omitting it from the submatrix
			//mSub.data[getIndex(mSub, subRow, subCol)] = m.data[getIndex(m, i, j)];
			mSub.data[subRow * mSub.numCols + subCol] = m.data[i * m.numCols + j];
			subCol++;
		}
		subRow++;
	}
		// write code to do sub mat
	return mSub;
}

int mDet(myMat m) {
	// compute determinant of matrix m
	if (m.numRows == 1 && m.numCols == 1) {
		// A 1x1 matrix is just a number so the determinant is just that number.
		return m.data[0];
	}
	if (m.numCols == 2 && m.numRows == 2) {
		// recursion is not needed here as the 2x2 matrix calculation does not require submatrices.
		return m.data[getIndex(m, 0, 0)] * m.data[getIndex(m, 1, 1)] - m.data[getIndex(m, 0, 1)] * m.data[getIndex(m, 1, 0)];
	}

	if (m.numRows == 3 && m.numCols == 3) {
		int det = 0;
		// Recursive case: Calculate the determinant using the expansion along the first row
		for (int j = 0; j < 3; j++) {
			// Calculate the minor of element (0, j)
			myMat subMat = mSubMat(m, 0, j);
			// Calculate the determinant of the submatrix
			int minorDet = mDet(subMat);
			// Add the product of the element and its minor determinant, with appropriate sign
			det += ((0 + j) % 2 == 0 ? 1 : -1) * m.data[j] * minorDet;
			
		}
		return det;
	}

	matError("invalid size of matrix");
}


myMat mAdj(myMat m) {
	// return adjoint of matrix m     assume 2*2 initially
	// if time add code to check matrices of right size
	myMat Cofactor = zeroMat(m.numRows, m.numCols);
	if (m.numCols == 2 && m.numRows == 2) {
		int detM = mDet(m);
		for (int i = 0; i < m.numRows; i++) {
			for (int j = 0; j < m.numCols; j++) {
				int Cofactor_sign = pow(-1, (i + j)) * detM;
				Cofactor.data[getIndex(Cofactor, i, j)] = Cofactor_sign;
			}
		}
		return Cofactor;
	}
	matError("Invalid size of matrix.");
}


void testMatEqn (myMat A, myMat b) {
	// solve Ax = b using Cramer rule and using Adjoint
	// This is for assessment later in term

	int detA = mDet(A);

	if (detA == 0) {
		std::cout << "Error: determinant of matrix A is zero and thus cramers rule cannot be used";
		return;
	}

	//myMat adjA = mAdj(A);
	//myMat x = zeroMat(b.numRows, 1);
	myMat x;
	x.numRows = A.numCols;
	x.numCols = 1;
	x = zeroMat(x.numRows, x.numCols);

	for (int i = 0; i < A.numRows; i++) {
		myMat tempA = A;
		for (int j = 0; j < A.numRows; j++) {
			tempA.data[j * A.numCols + i] = b.data[j];
		}
		int detTempA = mDet(tempA);
		x.data[i] = detTempA / detA;
		// Steps through each element in matrix A setting the i-th column in tempA to the corresponding element of vector b
		// thus replacing the i-th column with matrix b giving the augment matrix.
	}

	printMat("Solution vector x ", x);

}

int question2(myMat A, myMat b) {
	int x0, x1;
	double det = mDet(A);
	if (det == 0) {
		std::cout << "Determinant of A is 0 and thus cannot be used a divisor" << std::endl;
		return 0;
	}
	myMat adjA = mAdj(A);
	myMat adjAb = mMult(adjA, b);
	printMat("adjA", adjA);
	printMat("adjAb", adjAb);
	x0 = adjAb.data[getIndex(adjAb, 0, 0)] / det;
	x1 = adjAb.data[getIndex(adjAb, 0, 1)] / det;
	std::cout << "determinant of A: " << mDet(A) << "\n" << std::endl;
	std::cout << "x solutions are:\n" << x0 << "\n" << x1 << "\n" << std::endl;
	return x0, x1;
}

int main()
{
	std::cout << "32024813\n";				// change to your student number
	myMat m1, m2, m3, A, b, C, d, E, f;			// create  matrices

	m1 = mFromStr("9,6,8;7,8,10");			// change numbers to those in A from Q1 on web page, as specified on the sheet
	m2 = mFromStr("10,9,6;8,8,7");			// ditto but B
	m3 = mFromStr("7,7;2,8;7,8");			// ditto  but C
	A = mFromStr("6,8;8,7");
	b = mFromStr("76;72");
	C = mFromStr("9,6,2;8,8,10;9,7,7");
	d = mFromStr("130;200;177");
	E = mFromStr("8,10;9,6");
	f = mFromStr("134;114");
	
	printMat("m1", m1);						// display m1
	printMat("m2", m2);						// display m2
	printMat("m3", m3);						// display m3

	testVecs(m1, m3);						// test the vector routines
	testMatOps(m1, m2, m3);					// test the add, transpose and multiply

	question2(E, f);
	testMatEqn(A, b);
    testMatEqn(C, d);

	return 0;

}