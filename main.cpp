#include <stdio.h>
#include <iostream>
#include <vector>

#define size 5
#define deriv 1

using namespace std;

int main(){
	
	float a, b, x, y;
	int c = 0;
	vector<float> A;
	
	while ((scanf("%f %f %f %f", &a, &b, &x, &y)) != EOF) {
		A.push_back(a);
	}

	float Y, Y1;
	float h = 0.016;
	for (int i = size; i < c-size; i++) {
		
		//	Y = (-3*A[i-2] + 12*A[i-1] + 17*A[i] + 12*A[i+1] - 3*A[i+2]) / 35.;
		//	Y1 = (A[i-2] - 8*A[i-1] + 8*A[i+1] - A[i+2]) / (12.0 * h);
		cout << Y << " " << Y1 << endl;
	}
	return 0;
}
