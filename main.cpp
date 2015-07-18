#include <stdio.h>
#include <iostream>
#include <vector>
#include "sgfilter.h"

#define size 9
#define deriv 1
#define order 2

using namespace std;

int main(){
	//cout << "here" << endl;	
	float a, b, x, y;
	int c = 0;
	vector<float> X;
	vector<float> Y;
	
	while ((scanf("%f %f %f %f", &a, &b, &x, &y)) != EOF) {
		Y.push_back(a);
		X.push_back(y);
		c++;
	}

	// float h = 0.016;
	SgFilter filter;
	//cout << "here" << endl;
	for (int i = size; i < c - size - 1; i++) {
		vector<float> Xdata(X.begin() + i - size, X.begin() + i + size + 1);
		vector<float> Ydata(Y.begin() + i - size, Y.begin() + i + size + 1);
		cout << Y[i] << " " << filter.smooth(Xdata, Ydata, 2*size + 1, order, deriv)  << " " << X[i] << endl;
		//	Y = (-3*A[i-2] + 12*A[i-1] + 17*A[i] + 12*A[i+1] - 3*A[i+2]) / 35.;
		//	Y1 = (A[i-2] - 8*A[i-1] + 8*A[i+1] - A[i+2]) / (12.0 * h);
		//cout << Y << endl;
	}
	return 0;
}
