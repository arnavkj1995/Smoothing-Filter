#include "sgfilter.h"

gsl_matrix * SgFilter::pseudoInverse(gsl_matrix *A, int n_row, int n_col){
	gsl_matrix * A_t = gsl_matrix_alloc (n_col, n_row); 	//A_t is transpose
	gsl_matrix_transpose_memcpy (A_t, A);	

	gsl_matrix * U = gsl_matrix_alloc (n_col, n_row);
	gsl_matrix * V= gsl_matrix_alloc (n_row, n_row);
	gsl_vector * S = gsl_vector_alloc (n_row);

	// Computing the SVD of the transpose of A
	gsl_vector * work = gsl_vector_alloc (n_row);
	gsl_linalg_SV_decomp (A_t, V, S, work);
	gsl_vector_free(work);

	gsl_matrix_memcpy (U, A_t);

	//Inverting S
	gsl_matrix * Sp = gsl_matrix_alloc (n_row, n_row);
	gsl_matrix_set_zero (Sp);
	for (int i = 0; i < n_row; i++)
		gsl_matrix_set (Sp, i, i, gsl_vector_get(S, i));	// Vector 'S' to matrix 'Sp'
	
	gsl_permutation * p = gsl_permutation_alloc (n_row);
	int signum;
	gsl_linalg_LU_decomp (Sp, p, &signum);				// Computing the LU decomposition

	// Compute the inverse
	gsl_matrix * SI = gsl_matrix_calloc (n_row, n_row);

	for (int i = 0; i < n_row; i++) {
		if (gsl_vector_get (S, i) > 0.0000000001)
	  		gsl_matrix_set (SI, i, i, 1.0 / gsl_vector_get (S, i));
	}		
	
	gsl_matrix * VT = gsl_matrix_alloc (n_row, n_row);
	gsl_matrix_transpose_memcpy (VT, V);					// Tranpose of V

	//THE PSEUDOINVERSE
	//Computation of the pseudoinverse of trans(A) as pinv(A) = U·inv(S).trans(V)   with trans(A) = U.S.trans(V)	
	gsl_matrix * SIpVT = gsl_matrix_alloc (n_row, n_row);
	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,				// Calculating  inv(S).trans(V)
                	1.0, SI, VT,
                	0.0, SIpVT);

			
	gsl_matrix * pinv = gsl_matrix_alloc (n_col, n_row);	// Calculating  U·inv(S).trans(V)
	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
                	1.0, U, SIpVT,
                	0.0, pinv);

	gsl_matrix_free(VT);
	gsl_matrix_free(SI);
	gsl_matrix_free(SIpVT);
	gsl_matrix_free(A_t);
	gsl_matrix_free(U);
	gsl_matrix_free(A);
	gsl_matrix_free(V);
	gsl_vector_free(S);

	return pinv;
}

std::vector<float> SgFilter::sg_filter(std::vector<float> x, int order, int deriv){
	int xMid = x.size()/2;
	int xSize = x.size();
	//gsl to be used from here for calculating pseudo inverse
	// matrix to be initialised
	gsl_matrix * m = gsl_matrix_alloc (xSize, xSize);
	for(int i = 0 ; i < xSize ; i++){
		float val = 1;
		for(int j = 0 ; j < xSize ; j++){
			gsl_matrix_set (m, i, j, val);
			val *= (x[i] - x[xMid]);
		}
	}

	// making the transpose matrix
	gsl_matrix * a = gsl_matrix_alloc (xSize, xSize);
	//calculating pseudo inverse of a
	

	gsl_matrix * b = pseudoInverse(a, xSize, xSize);
	/*
	for(int i = 0 ; i < xSize ; i++){
		for(int j = 0 ; j < xSize ; j++){
			gsl_matrix_set (b, j , i, gsl_matrix_get (a, i, j));
		}
	}

	gsl_matrix * c = gsl_matrix_alloc (xSize, xSize);
	for(int i = 0 ; i < xSize ; i++){
		for(int j = 0 ; j < xSize ; j++){
			float val = 0;
			for(int k = 0 ; k < xSize ; k++){
				val += gsl_matrix_get(b, i , k)*gsl_matrix_get(a, k, j);
			}
			gsl_matrix_set (c, i, j, val);
		}
	}

	//int x =  gsl_linalg_LU_invert (const gsl_matrix * LU, const gsl_permutation * p, gsl_matrix * inverse)
//using armadillo	
	// using namespace arma;
	// double *matrix = new double [xSize*xSize];
	// arma::mat arma_matrix( matrix, xSize, xSize, true, true );
*/
		

}

int SgFilter::factorial(int n){
	int ans = 1;
	for(int i = 2 ; i <= n ; i++)
		ans *= i;
	return ans;
}

float SgFilter::smooth(std::vector<float> x, std::vector<float> y, int size, int order, int deriv){
	assert(deriv <= order);
	int start = 0;
	int end = 2*size + 1;
	// std::vector<float> f = sg_filter(x, order, deriv);

	 float result = 0;
	// for(int i = 0 ; i < f.size() ; i++){
	// 	result += f[i]*y[i];
	// }

	// if(deriv > 1)
	// 	result *= factorial(deriv);

	return result;
}