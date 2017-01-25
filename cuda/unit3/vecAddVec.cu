

__global__ 
void vecAddKernel(float* A, float* B, float* C, int n){
	/* the  input is A the output matrix, B vector, c vector, n size */
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	if(i < n*n)
		A[i] = B[i] + C[i];
}


__host__
void vecAdd(float* A, float* B, float* C, int n)
{
	int size = n * sizeof(float);
	float *d_A, *d_B, *d_C;
	cudaMalloc((void **) &d_A, size);
	cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
	cudaMalloc((void **) &B_d, size);
	cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);
	cudaMalloc((void **) &d_C, size);
	vecAddKernel<<<ceil(n/256.0), 256>>>(d_A, d_B, d_C, n);
	cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
	// Free device memory for A, B, C
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
}
