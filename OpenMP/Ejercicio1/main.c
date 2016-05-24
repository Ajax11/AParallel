#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Histo(int* vectorNum, int vectorNumSize, int numPerProcs, int* vectorHis, int vectorHisSize, int* vectorResutl);
void Hello(void);

int main(int argc, char const *argv[]){

//	int thread_count = strtol(argv[1], NULL, 10);
	
	int thread_count = 5;

	//int* vecNum, vecHisto, vecResult;
	int vecNum[20];
	int vecHisto[5];
	int vecResult[5];
	int vecNumSize;
	int vecHistoSize;

	vecNumSize = 20;
	vecHistoSize = 5;

	for (int i = 0; i < vecNumSize; ++i){
		*(vecNum + i) = (i+3)%vecHistoSize;
	}
	
	*(vecNum) = 0;
	*(vecNum+1) = 0;
	*(vecNum+2) = 0;

//lenado del vector a comparar

	for (int i = 0; i < vecHistoSize; ++i){
		*(vecHisto + i) = i;
	}

	for (int i = 0; i < vecHistoSize; ++i){
		*(vecResult + i) = 0;
	}

	for (int i = 0; i < vecNumSize; ++i){
		printf("%d \t", *(vecNum+i));
		if ( ((i+1)%5) == 0){
			printf("\n");
		}
	}

	//vecNum = (int*) malloc((numbHisto+1)*sizeof(double));

	int numPerProcss;
	numPerProcss = vecNumSize/vecHistoSize;

	#pragma omp parallel num_threads(thread_count)
	Histo(vecNum, vecNumSize, numPerProcss, vecHisto, vecHistoSize, vecResult);

	printf("Result vector \n\n\n");

	for (int i = 0; i < vecHistoSize; ++i){
		printf("%d \t", *(vecResult + i));
	}
	printf("\n");

	return 0;
}


void Hello(void){
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	printf("Hello from thread %d of %d\n", my_rank, thread_count);
	return;
}


void Histo(int* vectorNum, int vectorNumSize, int numPerProcs, int* vectorHis, int vectorHisSize, int* vectorResutl){
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	

// cota Inferior = my_rank*numPerProcs
// cota Superior = (my_rank+1)*numPerProcs

	int cotaSup;
	int cotaInf;

	if ( my_rank == 0 )
		cotaInf = 0;
	else
		cotaInf = my_rank*numPerProcs;


	if ( my_rank == (thread_count-1) )
		cotaSup = vectorNumSize;
	else
		cotaSup = (my_rank+1)*numPerProcs;
/*
	printf("las cotas son %d - %d \n", cotaInf,cotaSup);
*/

	int i;
	for (i = cotaInf; i < cotaSup; ++i){
		for (int j = 0; j < vectorHisSize; ++j){
			if( *(vectorNum + i) == *(vectorHis + j) ){
				#pragma omp critical
				*(vectorResutl + j)+=1;
			}
		}
	}

	//printf("Hello from thread %d of %d \n", my_rank, thread_count);
/*
	printf("state of the result vector\n");
	for (int i = 0; i < vectorHisSize; ++i){
		#pragma omp critical
		printf("%d \t", *(vectorResutl + i));
	}
	#pragma omp critical
	printf("\n");	
*/

	return;
}
