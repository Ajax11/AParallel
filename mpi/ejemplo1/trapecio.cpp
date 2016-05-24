
#include <stdio.h>
#include <string.h>
#include <mpi.h>

double f(double x){
	double result = 0;
	result = x;
	return result;
}

double area(double a, double b){
	double result = 0;
	result = (f(a)+f(b))/2.0;
	result *= (b-a);
	return result;
}

const int MAX_STRING = 100;

int main(void){
	char greeting[MAX_STRING];
	double localArea = 0;
	int comm_sz;
	int my_rank;

/*
	Defining the areas to evalueat
*/
	double a,b;
	a = 0;
	b = 200;

	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	double localA, localB, localH;
	localH = (b-a)/double(comm_sz-1);


	if(my_rank != 0){
		localA = a + (my_rank - 1)*localH;
		localB = a + (my_rank)*localH;
		localArea = area(localA, localB);
		/*
			std::cout << "In process " << my_rank << " : " << localA << " <->" << localB << " <-> " << localArea << std::endl;
		*/ 
		MPI_Send(&localArea, 1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}
	else{
		double areaT = 0;
		for(int q = 1; q < comm_sz; q++){
			MPI_Recv(&localArea, 1, MPI_DOUBLE, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			areaT += localArea;	
		}
		std::cout << areaT << std::endl;
	}

	MPI_Finalize();
	return 0;

}
