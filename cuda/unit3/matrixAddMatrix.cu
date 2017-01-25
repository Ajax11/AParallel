#include <iostream>
#include <stdio.h>
#include <cuda.h>
#define SIZEM 100

__global__ 
void matrixAddKernel(float* A, float* B, float* C, int n){
	/* the  input is A the output matrix, B matrix, c matrix, n size */
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	if(i < (n*n)){
		A[i] = B[i] + C[i];
	}
}

__global__ 
void matrixAddKernelRow(float* A, float* B, float* C, int n){
	/* the  input is A the output matrix, B matrix, c matrix, n size */
	int j = threadIdx.x + blockDim.x * blockIdx.x;
	if(j < n)
		for (int i = 0; i < n; ++i){
			A[ ( j * n ) + i ] = B[ ( j * n ) + i ] + C[ ( j * n ) + i ];
		}
}

__global__ 
void matrixAddKernelColumn(float* A, float* B, float* C, int n){
	/* the  input is A the output matrix, B matrix, c matrix, n size */
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	if(i < n)
		for (int j = 0; j < n; ++j){
			A[ ( j * n ) + i ] = B[ ( j * n ) + i ] + C[ ( j * n ) + i ];
		}
}

__host__
void matrixAdd(float* A, float* B, float* C, int n){
	int size = n * n * sizeof(float);
	
	float* d_A;
	float* d_B;
	float* d_C;
	
	cudaMalloc((void **) &d_B, size);
	cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

	cudaMalloc((void **) &d_C, size);
	cudaMemcpy(d_C, C, size, cudaMemcpyHostToDevice);

	cudaMalloc((void **) &d_A, size);
	cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);

	matrixAddKernelColumn<<<ceil((n*n)/256.0), 256>>>(d_A, d_B, d_C, n);
	cudaMemcpy(A, d_A, size, cudaMemcpyDeviceToHost);


	// Free device memory for A, B, C
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
}


__host__
int main(int argc, char const *argv[]){
	/*
	float a[SIZEM];
	float b[SIZEM*SIZEM];
	float c[SIZEM];
	*/
	float* a;
	float* b;
	float* c;

	a = (float*) malloc(SIZEM*SIZEM*sizeof(float));
	b = (float*) malloc(SIZEM*SIZEM*sizeof(float));
	c = (float*) malloc(SIZEM*SIZEM*sizeof(float));


	for (long int i = 0; i < SIZEM*SIZEM; ++i){
		a[i] = 0;
	}

	for (long int i = 0; i < SIZEM*SIZEM; ++i){
		b[i] = 1;
	}

	for (long int i = 0; i < SIZEM*SIZEM; ++i){
		c[i] = 1;
	}

	matrixAdd(a, b, c, SIZEM);

	for (int i = 0; i < SIZEM*SIZEM; ++i){
		if (i % SIZEM == 0){
			std::cout << '\n';
		}
		std::cout << a[i] << '\t';
	}
			std::cout << '\n';

	return 0;
}

/*

	

*/

