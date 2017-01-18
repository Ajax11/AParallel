#include <iostream>
#include <vector>

#define type int

typedef std::vector< std::vector<type> > matrix;

void setMatrix(matrix & a, type row, type column, type constant = 0){
	a.resize(row);
	for (int i = 0; i < a.size(); ++i){
		a[i].resize(column, constant);
	}
}

void printMatrix(matrix a){
	for (int i = 0; i < a.size(); ++i){
		for (int j = 0; j < a[i].size(); ++j){
			std::cout << a[i][j] << '\t';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void product(matrix a, matrix b, matrix & c){
	for (int i = 0; i < a.size(); ++i){ // the number of row from a
		for (int j = 0; j < b[0].size(); ++j){ // the number of columnfrom b
			for (int k = 0; k < b.size(); ++k){ // the number of column from a - the number of row from b
				c[i][j] += ( a[i][k] * b[k][j] );
			}
		}
	}
}

void productBlock(matrix a, matrix b, matrix & c){

}

#define A 10
#define B 10
#define C 10

int main(int argc, char const *argv[])
{
	matrix mA;
	matrix mB;
	matrix mC;


	setMatrix(mA, A, B, 2);
	setMatrix(mB, B, C, 6);
	setMatrix(mC, A, C);

//	printMatrix(mA);
//	printMatrix(mB);
//	printMatrix(mC);

	product(mA, mB, mC);
	
	printMatrix(mC);

	return 0;
}


/*

https://www.mathsisfun.com/algebra/matrix-multiplying.html
http://mescal.imag.fr/membres/arnaud.legrand/teaching/2012/M2R_PC.php#orgheadline6
http://mescal.imag.fr/membres/arnaud.legrand/#orgheadline4
http://mescal.imag.fr/membres/arnaud.legrand/research.php
http://mescal.imag.fr/membres/arnaud.legrand/research/internships.php


valgrind: REVIZAR

http://baptiste-wicht.com/posts/2011/09/profile-c-application-with-callgrind-kcachegrind.html


http://kcachegrind.sourceforge.net/html/Usage.html
	see example 1 - For me is the easiest way to resolve the tas

http://kcachegrind.sourceforge.net/html/Documentation.html
https://apps.ubuntu.com/cat/applications/kcachegrind/
http://valgrind.org/


Command to run kcachegrind
$kcachegrind callgrind.out.(the number of the file)

*/