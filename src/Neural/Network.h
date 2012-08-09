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
	Network(int input, int hidden,int,int output, double alpha,double lambda);
	double* sigmoid(double* nodes);
	double* sigmoidGradient(double *nodes);
	virtual ~Network();
	double * feedForward(double * );
	double sigmoid(double);
	double sigmoidGradient(double);
	double hyperbolic(double,double);
	double hyperbolicGradient(double,double);
	void update(int);
private:
	double** firstWeight;
	double** firstE;
	double** secondWeight;
	double** secondE;
	double ** thirdWeight;
	double ** thirdE;
	double* input;
	double* inter1;
	double * inter2;
	double* out;
	int input_count;
	int hidden1_count;
	int hidden2_count;
	double lambda;
	double alpha;
	int output_count;
	void randomWeights();
	double oldvalue;
};
}
#endif /* NETWORK_H_ */
