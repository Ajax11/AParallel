

#include <iostream>
#include <vector>

/*
	Revizar, la metodologia empleada, mejorar y arreglar de acuerdo a las especificaciones del trabajo
		El trabajo esta descargado en la carpeta de trabajo, es un archivo pdf
*/

void productBlock(matrix a, matrix b, matrix c, int n, int bsize){

	int i, j, k, kk, jj;
	double sum;
	int en = bsize * (n/bsize); /* Amount that fits evently into blocks */

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			c[i][j] = 0.0;
		}
	}

	for (kk = 0; kk < en; kk+=bsize){
		for (jj = 0; jj < en; ++jj){
			for (i = 0; i < n; ++i){
				for (j = jj; j < jj+bsize; ++j){
					sum = c[i][j];
					for (k = kk; k < kk + bsize; ++k){
						sum += a[i][k] * b[k][j];
					}
					c[i][j] = sum;
				}
			}
		}
	}


}

int main(int argc, char const *argv[])
{

	return 0;
}