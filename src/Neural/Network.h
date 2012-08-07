/*
 * Network.h
 *
 *  Created on: Aug 3, 2012
 *      Author: ivan
 */

#ifndef NETWORK_H_
#define NETWORK_H_
#include "omp.h"
#include "math.h"
#include "omp.h"
#include <cstdlib>
#include <ctime>
#include <string>
//#include <sstream>
#include <iostream>
#include <time.h>
namespace tron{
class Network {
public:
	Network(int input, int hidden,int output, double alpha,double lambda);
	double* sigmoid(double* nodes);
	double* sigmoidGradient(double *nodes);
	virtual ~Network();
	double * feedForward(double * );
	double sigmoid(double);
	double sigmoidGradient(double);
	double hyperbolic(double);
	double hyperbolicGradient(double);
private:
	double** firstWeight;
	double** secondWeight;
	int input_count;
	int hidden_count;
	double lambda;
	double alpha;
	int output_count;
	void randomWeights();
};
}
#endif /* NETWORK_H_ */
