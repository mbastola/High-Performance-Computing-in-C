#include <stdio.h>
#include <stdlib.h>

__global__ void add( int *a, int *b, int *c ) {
	int index = threadIdx.x + blockIdx.x * blockDim.x;
	c[index] = a[index] + b[index];
}

void random_ints(int* arr, int N)
{
	for(int i = 0; i < N; i++)
	{
		int x = rand() % 100;
		arr[i] = x;
	}
}

#define N (2048 * 2048)
#define THREADS_PER_BLOCK 512
int main( void ) {
	int *a, *b, *c; // host copies of a, b, c
	int *dev_a, *dev_b, *dev_c; // device copies of a, b, c
	int size = N * sizeof( int ); // we need space for 512 integers

	// allocate device copies of a, b, c
	cudaMalloc( (void**)&dev_a, size );
	cudaMalloc( (void**)&dev_b, size );
	cudaMalloc( (void**)&dev_c, size );

	a = (int*)malloc( size );
	b = (int*)malloc( size );
	c = (int*)malloc( size );

	random_ints( a, N );
	random_ints( b, N );

	// copy inputs to device
	cudaMemcpy( dev_a, a, size, cudaMemcpyHostToDevice );
	cudaMemcpy( dev_b, b, size, cudaMemcpyHostToDevice );

	// launch add() kernel with N threads
	add<<< N/THREADS_PER_BLOCK, THREADS_PER_BLOCK >>>( dev_a, dev_b, dev_c );

	// copy device result back to host copy of c
	cudaMemcpy( c, dev_c, size, cudaMemcpyDeviceToHost );

	for(int i = 0; i < N; i++)
	{
		printf("%d\n", c[i]);
	}

	free( a ); free( b ); free( c );
	cudaFree( dev_a );
	cudaFree( dev_b );
	cudaFree( dev_c );
	return 0;
}

