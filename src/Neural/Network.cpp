/*
 * Network.cpp
 *
 *  Created on: Aug 3, 2012
 *      Author: ivan
 */

#include "Network.h"
namespace tron{
	Network::Network(int input, int hidden,int output, double alpha,double lambda)
	:input_count(input), hidden_count(hidden),output_count(output),alpha(alpha),lambda(lambda)
	{
		//initialize random weights
		firstWeight = new double*[hidden];
		for(int i =0;i<hidden;i++)
		{
			firstWeight[i] = new double[input];
		}
		secondWeight = new double*[output];
		for(int i = 0;i<output;i++)
		{
			secondWeight[i] = new double[hidden];
		}
		randomWeights();
	}

	Network::~Network() {
		// Auto-generated destructor stub
	}

	//initialize random weights
	void Network::randomWeights()
	{
		srand(time(NULL));
	#pragma omp parallel for
		for(int i = 0 ;i<hidden_count;i++)
			for(int j = 0;j<input_count;j++)
				firstWeight[i][j] = rand() / double(RAND_MAX); // number between 0 and 1

#pragma omp parallel for
		for(int j = 0 ;j<output_count;j++)
			for(int i = 0 ;i<hidden_count;i++)
				secondWeight[j][i] = rand() / double(RAND_MAX);
	}

	//sigmoid function of an array
	double* Network::sigmoid(double* nodes){
		int count = sizeof(nodes)/sizeof(nodes[0]);
		double *result = new double[count];
#pragma omp parallel for
		for(int i = 0; i<count;i++)
		{
			result[i] =1.0/(1.0+exp(-nodes[i]));
		}
		return result;
	}

	//sigmoid of a single node
	double Network::sigmoid(double node)
	{
		return 1.0/(1.0+exp(-node));
	}
	double Network::hyperbolic(double node)
	{
		return (exp(node) -exp(node))/(exp(node) + exp(-node));
	}
	double Network::hyperbolicGradient(double node)
	{
		return (pow((exp(node)+exp(-node)),2)-pow(exp(node)-exp(-node),2))/pow(exp(node)+exp(-node),2);
	}
	//calculate the sigmoid gradient of an array
	double * Network::sigmoidGradient(double* nodes)
	{
		int count = sizeof(nodes)/sizeof(nodes[0]);
		double *result = new double[count];
		double * sigmoids = sigmoid(nodes);
	#pragma omp parallel for
		for(int i = 0;i<count;i++)
		{
			result[i] = sigmoids[i]*(1-sigmoids[i]);
		}
		return result;
	}
	//sigmoid gradient of a single node
	double Network::sigmoidGradient(double node)
	{
		double sig = sigmoid(node);
		return sig * (1-sig);
	}


	//run the feed forward
	double * Network::feedForward(double * input)
	{
		std::cout<<"inside feed forward\n";

		double* output = new double[output_count];
		double * inter = new double[hidden_count];
		std::cout<<"correct sized\n";
#pragma omp parallel
		for(int j = 0 ;j<hidden_count;j++)
		{

			inter[j] = 0;
			for(int i = 0;i<input_count;i++)
			{
				inter[j] += input[i]*firstWeight[j][i];
			}
			std::cout<<inter[j]<<" "<<sigmoid(inter[j])<<std::endl;
			inter[j] = sigmoid(inter[j]);
		}
		std::cout<<std::endl;
		double * out = new double[output_count];

#pragma omp parallel for
		for(int j = 0 ;j<output_count;j++)
		{
			out[j] = 0;
			for(int i = 0; i <hidden_count;i++)
			{
				out[j] += inter[i] * secondWeight[j][i];
			}
			std::cout<<out[j]<<" "<<sigmoid(out[j])<<std::endl;
			out[j] = sigmoid(out[j]);
		}
		return out;
	}
}
