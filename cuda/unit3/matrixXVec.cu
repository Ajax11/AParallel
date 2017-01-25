
#include <iostream>
#include <stdio.h>
#include <cuda.h>
#define SIZEM 1000

__global__ 
void matrixXvecKernel(float* A, float* B, float* C, int n){
	/* the  input is A the output matrix, B matrix, c vector, n size */
	//int size = n * sizeof(float);

	int j = threadIdx.x + blockDim.x * blockIdx.x;
	if( j < n ){
		A[j] = 0;
		for (int i = 0; i < n; ++i){
			A[j] += B[ ( j * n ) + i ] * C[i];
		}
	}
}

__host__
void product(float* A, float* B, float* C, int n){
	int size = n * sizeof(float);
	
	float* d_A;
	float* d_B;
	float* d_C;

	cudaMalloc((void **) &d_B, size * n);
	cudaMemcpy(d_B, B, size*n, cudaMemcpyHostToDevice);

	cudaMalloc((void **) &d_C, size);
	cudaMemcpy(d_C, C, size, cudaMemcpyHostToDevice);

	cudaMalloc((void **) &d_A, size);
	cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);

	matrixXvecKernel<<<ceil(n/256.0), 256>>>(d_A, d_B, d_C, n);
	cudaMemcpy(A, d_A, size, cudaMemcpyDeviceToHost);

	// Free device memory for A, B, C
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
}


__host__
int main(int argc, char const *argv[]){

	float* a;
	float* b;
	float* c;

	a = (float*) malloc(SIZEM*sizeof(float));
	b = (float*) malloc(SIZEM*SIZEM*sizeof(float));
	c = (float*) malloc(SIZEM*sizeof(float));

	for (int i = 0; i < SIZEM; ++i){
		a[i] = 0;
	}

	for (int i = 0; i < SIZEM*SIZEM; ++i){
		b[i] = 1;
	}

	for (int i = 0; i < SIZEM; ++i){
		c[i] = 1;
	}

	product(a, b, c, SIZEM);
	for (int i = 0; i < SIZEM; ++i){
		if (i % SIZEM == 0){
			std::cout << '\n';
		}
		std::cout << a[i] << '\t';
	}
			std::cout << '\n';

	return 0;
}

