#ifndef SGFILTER_H
#define SGFILTER_H

#include <stdio.h>
#include <iostream>

class SgFilter{
public:
	SgFilter() {}
	float filterData(std::vector<float> x, std::vector<float> y, int size, int order, int deriv);
	int factorial(int n);
	std::vector<float> sg_filter(std::vector<float> x, int order, int deriv);
};
#endif