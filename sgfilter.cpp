#include "sgfilter.h"

std::vector<float> SgFilter::sg_filter(std::vector<float> x, int order, int deriv){
	int mid = x.size()/2;
	std::vector<float> a;
	for(std::vector<float> it = x.begin(); it != x.end() ; it++){
		a.push_back((*it) - x[mid]);
	}
	//gsl to be used from here
		

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
	std::vector<float> f = sg_filter(x, order, deriv);

	float result = 0;
	for(int i = 0 ; i < f.size() ; i++){
		result += f[i]*y[i];
	}

	if(deriv > 1)
		result *= factorial(deriv);

	return result;
}