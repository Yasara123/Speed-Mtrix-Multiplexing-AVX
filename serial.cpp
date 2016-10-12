#include<iostream>
#include<cstdlib>
#include<ctime>
#include <omp.h>

using namespace std;

double** matrixMultipication(int n, double** A, double** B);

int main(int argc, char** argv){
		int  n= atoi(argv[1]);  //get matrix size from user
		
		double** A = new double*[n];   //declare matrix A
		double** B = new double*[n];   //declare matrix B
		double** C = new double*[n];   //declare matrix C

		for(int i=0;i<n;i++){
			A[i]=new double[n];
		}
		for(int i=0;i<n;i++){
			B[i]=new double[n];
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				A[i][j]=rand()%10;  //initialize matrix A with random numbers
			}
		}
		
		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				B[i][j]=rand()%10;  //initialize matrix B with random numbers
			}
		}
		
		C = matrixMultipication(n,A,B);

		//delete the matrices
		free(A);
		free(B);
		free(C);

			
	
	return 0;
}

//function to perform matrix multiplication
double** matrixMultipication(int n, double** A, double** B){
	double** C = 0;
	C = new double*[n];
	for(int i=0;i<n;i++){
		C[i] = new double[n];
	}
	
	double t1, t2;
	
	t1 = omp_get_wtime();  

	for(int i=0;i<n;i++){  //outer for loop
		for(int j=0;j<n;j++){  //inner for loop
			C[i][j]=0;    //initialize the values of matrix C to zero

			for(int k=0;k<n;k++){
				C[i][j]+=A[i][k]*B[k][j]; // multiply corresponding values in matrix A and matrix B

			}
		}
	}

	t2 = omp_get_wtime(); 
	cout << fixed;
	cout.precision(12);
	cout <<"Execution time for multiplication: " << t2-t1<<endl;


	return C;
}

