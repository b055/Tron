/*
 * Network.cpp
 *
 *  Created on: Aug 3, 2012
 *      Author: ivan
 */

#include "Network.h"
namespace tron{
	Network::Network(int input, int hidden1,int hidden2,int output, double alpha,double lambda)
	:input_count(input+1), hidden1_count(hidden1+1),hidden2_count(hidden2+1),output_count(output),alpha(alpha),lambda(lambda)
	{
		oldvalue = 0;
		this->input = new double[input_count];
		//initialize random weights and elegibility traces
		firstWeight = new double*[hidden1_count];
		firstE = new double* [hidden1_count];
		for(int i =0;i<hidden1_count;i++)
		{
			firstE[i] = new double[input_count];
			firstWeight[i] = new double[input_count];
		}

		secondWeight = new double*[hidden2_count];
		secondE = new double* [hidden2_count];
		for(int i = 0; i<hidden2_count;i++)
		{
			secondE[i] = new double[hidden1_count];
			secondWeight[i] = new double[hidden1_count];
		}

		thirdE = new double*[output];
		thirdWeight = new double*[output];
		for(int i = 0;i<output;i++)
		{
			thirdE[i] = new double[hidden2_count];
			thirdWeight[i] = new double[hidden2_count];
		}
		randomWeights();
	}

	Network::~Network() {
		// Auto-generated destructor stub
	}

	//initialize random weights and eligibility traces
	void Network::randomWeights()
	{
		srand(time(NULL));
	#pragma omp parallel for
		for(int i = 0 ;i<hidden1_count;i++)
			for(int j = 0;j<input_count;j++){
				firstWeight[i][j] = rand() / double(RAND_MAX); // number between 0 and 1
				firstE[i][j] = 0;
			}

#pragma omp parallel for
		for(int j = 0 ;j<hidden2_count;j++)
			for(int i = 0 ;i<hidden1_count;i++){
				secondWeight[j][i] = rand() / double(RAND_MAX);
				secondE[i][j] = 0;
			}

#pragma omp parallel for
		for(int j = 0 ;j<output_count;j++)
			for(int i = 0 ;i<hidden2_count;i++)
			{
				thirdWeight[j][i] = rand() / double(RAND_MAX);
				thirdE[j][i] = 0;
			}
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

	double Network::hyperbolic(double node,double stretch)
	{
		return (exp(stretch*node) -exp(stretch*node))/(exp(stretch*node) + exp(-stretch*node));
	}
	double Network::hyperbolicGradient(double node,double stretch)
	{
		return stretch*(1-pow(hyperbolic(node,stretch),2));
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
	double Network::feedForward(double * in)
	{
		double stretch = 1;
		input[0] = 1; // bias
		for(int i = 1;i<input_count;i++)
		{
			input[i] = in[i-1];
		}
		//std::cout<<"inside feed forward\n";
		inter1 = new double[hidden1_count];
		inter1[0] = 1; //bias in the hidden layer
#pragma omp parallel
		for(int j = 1 ;j<hidden1_count;j++)//skips the bias
		{
			inter1[j] = 0;
			for(int i = 0;i<input_count;i++)
			{
				inter1[j] += input[i]*firstWeight[j][i];
			}
			//std::cout<<inter1[j]<<" "<<hyperbolic(inter1[j],stretch)<<std::endl;
			inter1[j] = hyperbolic(inter1[j],stretch);
		}


		//std::cout<<"finished first intersection "<<std::endl;
		inter2 = new double[hidden2_count];
		inter2[0] = 1; //bias in the hidden layer
#pragma omp parallel
		for(int j = 1 ;j<hidden2_count;j++)//skips the bias
		{

			inter2[j] = 0;
			for(int i = 0;i<hidden1_count;i++)
			{
				if(i == 0)
					inter2[j] += secondWeight[j][i];//behaves like the input layer had a bias as well
				else
					inter2[j] += inter1[i-1]*secondWeight[j][i];
			}
			//std::cout<<inter2[j]<<" "<<hyperbolic(inter2[j],stretch)<<std::endl;
			inter2[j] = hyperbolic(inter2[j],stretch);
		}
		//std::cout<<"finished second intersection "<<std::endl;
		out = new double[output_count];

#pragma omp parallel for
		for(int j = 0 ;j<output_count;j++)
		{
			out[j] = 0;
			for(int i = 0; i <hidden2_count;i++)
			{
				out[j] += inter2[i] * thirdWeight[j][i];
			}
		//	std::cout<<out[j]<<" "<<hyperbolic(out[j],stretch)<<std::endl;
			out[j] = hyperbolic(out[j],stretch);
		}

		return out[0];
	}

	/*
	 * update the parameters of the neural network with the reward
	 */
	void Network::update(int reward)
	{
		// error signal for gradient descent
		double *delta4 = new double[output_count];
		delta4[0]= reward + out[0]-oldvalue;
		//calculate current eligibility traces while back propagating
		double ** delta3 = new double*[output_count];

		double ** delta2 = new double*[hidden2_count];

		double stretch = 0.2;
#pragma omp parallel for
		for(int j = 0;j<output_count;j++)
		{
			delta3[j]= new double[hidden2_count];
			for(int i = 0 ;i<hidden2_count;i++){
				delta3[j][i] = 0;
			}
		}

#pragma omp parallel for
		for(int i = 0;i<hidden2_count;i++)
		{
			delta2[i] = new double[hidden1_count];
			for(int j=0;j<hidden1_count;j++)
				delta2[i][j] = 0;
		}


		for(int k = 0;k<output_count;k++ )
		{
			for(int j = 0;j<hidden2_count;j++)
			{
				thirdE[k][j] = lambda * thirdE[k][j] + out[k]*(1-out[k])*inter2[j];
				delta3[k][j] += thirdWeight[k][j] * delta4[k] * hyperbolicGradient(inter2[j],stretch) ;
				thirdWeight[k][j] += alpha * delta3[k][j]*thirdE[k][j];
				//std::cout<<delta3[k][j]<<" delta3 "<<j<<std::endl;
				for(int i = 0; i<hidden1_count;i++)
				{
					secondE[j][i] = lambda*secondE[j][i] + out[k]*(1-out[k]) * secondWeight[j][i] *inter2[j]*(1-inter2[j]) * inter1[i];
					delta2[j][i]  += secondWeight[j][i] * delta3[k][j]* hyperbolicGradient(inter1[i],stretch);
					secondWeight[j][i] += alpha * delta2[j][i]*secondE[j][i];
				//	std::cout<<delta2[j][i]<<" delta2 "<<j<<" "<<i<<std::endl;
					for(int h = 0;h<input_count;h++)
					{
						firstE[i][h] = lambda* firstE[i][h] +  out[k]*(1-out[k])*firstWeight[i][h]*inter1[i]*(1-inter1[i]) * input[i];
						firstWeight[i][h] += alpha * firstE[i][h];
					}
				}
			}
		}

		/*
		for(int j = 0;j<output_count;j++)
		{
			for(int i = 0;i<hidden2_count;i++)
			{
				thirdE[j][i] = lambda * thirdE[j][i] + out[j]*(1-out[j])*inter2[i];
				delta3[i] += thirdWeight[j][i] * delta4[j] * hyperbolicGradient(inter2[i],stretch) ;
				std::cout<<delta3[i]<<" delta3 "<<i<<std::endl;
			}
		}

		for(int j = 0;j<hidden2_count;j++)
		{
			for(int i = 0 ; i<hidden1_count;i++)
			{
				secondE[j][i] = lambda*secondE[j][i] + out[0]*(1-out[0]) * secondWeight[j][i] *inter2[j]*(1-inter2[j]) * inter1[i];
				delta2[i]  += secondWeight[j][i] * delta3[j]* hyperbolicGradient(inter1[i],stretch);
				std::cout<<delta2[i]<<" delta2 "<<i<<std::endl;
			}
		}

		for(int j = 0;j<hidden1_count;j++)
		{
			for(int i = 0 ;i<input_count;i++)
			{
				firstE[j][i] = lambda* firstE[j][i] +  out[0]*(1-out[0])*firstWeight[j][i]*inter1[j]*(1-inter1[j]) * input[i];
			}
		}*/

		//update the weights with the update rule


		//set old value
		oldvalue = out[0];
		std::cout<<delta4[0]<<" delta4"<<std::endl;
	}
	std::string Network::getWeights()
	{
		std::stringstream ss;
		std::cout<<"getting third"<<std::endl;
		for(int j = 0;j<output_count;j++)
		{
			for(int i = 0;i<hidden2_count-1;i++)
			{
				ss<<thirdWeight[j][i]<<" ";
			}
			ss<<std::endl;
		}
		std::cout<<"getting second\n";
		for(int j = 0;j<hidden2_count;j++)
		{
			for(int i = 0 ; i<hidden1_count;i++)
			{
				ss<<secondWeight[j][i]<<" ";
			}
			ss<<std::endl;
		}
		std::cout<<"getting first\n";
		for(int j = 0;j<hidden1_count;j++)
		{
			for(int i = 0; i<input_count;i++)
			{
				ss<<firstWeight[j][i]<<" ";
			}
			ss<<std::endl;
		}
		return ss.str();
	}
}
