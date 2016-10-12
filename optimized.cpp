
#include <iostream>
#include <random>
#include <omp.h>

using namespace std;

double** getTranspose(double** A, int n);
void matrixMultiplication(int n, double **A, double **B);

int main(int argc, const char* argv[]) {
    	int n = atoi(argv[1]); //get matrix size from user

		double** A = new double*[n];  //declare matrix A
		double** B = new double*[n];  //declare matrix B
		double** C = new double*[n];  //declare matrix C

		for(int i=0;i<n;i++){
			A[i]=new double[n]; 
		}
		for(int i=0;i<n;i++){
			B[i]=new double[n]; 
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				A[i][j]=rand()%10;   //initialize matrix A with random numbers
			}
		}

		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				B[i][j]=rand()%10;   //initialize matrix B with random numbers 
			}
		}

		matrixMultiplication(n,A,B);
		return 0;
}

//function to get the transpose of a given matrix
double** getTranspose(double** A, int n){
	double** M = new double*[n]; 
	for(int i=0; i<n; i++){  
		M[i]=new double[n];
		for(int j=0; j<n; j++){
			M[i][j] = A[j][i];
		}
	}
	return M;
}

//function to perform matrix multiplication
void matrixMultiplication(int n, double **A, double **B) {
    double** C = 0;
	C = new double*[n];
	for(int i=0;i<n;i++){
		C[i] = new double[n];
	}

    double t1, t2;

    t1 = omp_get_wtime();

    double** BTrans = getTranspose(B, n);

#pragma omp parallel for 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            __m256d vec = _mm256_setzero_pd(); //initialize all elements of float64 vector to zero          
            double tmpArr[4]; //temorary array to store results

            for (int k = 0; k < n; k += 4) {
                vec = __builtin_ia32_addpd256(vec, __builtin_ia32_mulpd256(__builtin_ia32_loadupd256(&A[i][k]), __builtin_ia32_loadupd256(&BTrans[j][k]))); //multiply and add vectors with high performance AVX instructions
            }
            __builtin_ia32_storeupd256(tmpArr, vec); //store results in temporary array
            C[i][j] = tmpArr[0] + tmpArr[1] + tmpArr[2] + tmpArr[3]; // store the sum in matrix C 
        }
    }

    t2 = omp_get_wtime(); 
    cout << fixed;
    cout.precision(12);
    cout << "Execution time for multiplication: " << t2-t1 << endl;

		//delete the matrices
		free(A);
		free(B);
		free(C);

}

