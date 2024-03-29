/*
 * Network.cpp
 *
 *  Created on: Aug 3, 2012
 *      Author: ivan
 */

#include "Network.h"
namespace tron{
	Network::Network(int input, int hidden1,int hidden2,int output, double alpha,double beta,double gam,double lambda)
	:input_count(input+1), hidden1_count(hidden1+1),beta(beta),gam(gam),hidden2_count(hidden2+1),output_count(output),alpha(alpha),lambda(lambda)
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
		inter2 = new double[hidden2_count];
		inter1 = new double[hidden1_count];
		out = new double[output_count];
		randomWeights();
	}

	Network::Network(std::string old)
	{
		std::ifstream stream;
		stream.open(old.c_str());
		std::string alp;
		getline(stream,alp,'=');getline(stream,alp,'\n');
		std::string bet;
		getline(stream,bet,'=');getline(stream,bet,'\n');
		std::string gamma;
		getline(stream,gamma,'=');getline(stream,gamma,'\n');
		std::string lam;
		getline(stream,lam,'=');getline(stream,lam,'\n');
		std::string in;
		getline(stream,in,'=');getline(stream,in,'\n');
		std::string hid1;
		getline(stream,hid1,'=');getline(stream,hid1,'\n');
		std::string hid2;
		getline(stream,hid2,'=');getline(stream,hid2,'\n');
		std::string out;
		getline(stream,out,'=');getline(stream,out,'\n');


		alpha = strtof(alp.c_str(),0);
		beta = strtof(bet.c_str(),0);
		gam = strtof(gamma.c_str(),0);
		lambda = strtof(lam.c_str(),0);
		input_count = strtold(in.c_str(),0);
		hidden1_count = strtold(hid1.c_str(),0);
		hidden2_count = strtold(hid2.c_str(),0);
		output_count = strtold(out.c_str(),0);


		this->input = new double[input_count];
		inter2 = new double[hidden2_count];
		inter1 = new double[hidden1_count];
		this->out = new double[output_count];

		std::string row;
		std::string col;

		firstWeight = new double*[hidden1_count];
		for(int i =0;i<hidden1_count;i++)
		{
			getline(stream,row);
			std::stringstream colstream(row);
			firstWeight[i] = new double[input_count];
			for(int j = 0;j<input_count;j++)
			{
				getline(colstream,col,' ');
				firstWeight[i][j]= strtof(col.c_str(),0);
			}
		}

		secondWeight = new double*[hidden2_count];
		for(int i = 0; i<hidden2_count;i++)
		{
			getline(stream,row);
			std::stringstream colstream(row);
			secondWeight[i] = new double[hidden1_count];
			for(int j = 0;j<hidden1_count;j++)
			{
				getline(colstream,col,' ');
				secondWeight[i][j] = strtof(col.c_str(),0);
			}
		}

		thirdWeight = new double*[output_count];
		for(int i = 0;i<output_count;i++)
		{
			getline(stream,row);
			std::stringstream colstream(row);
			thirdWeight[i] = new double[hidden2_count];
			for(int j = 0;j<hidden2_count;j++)
			{
				getline(colstream,col,' ');
				thirdWeight[i][j]= strtof(col.c_str(),0);
			}
		}
		firstE = new double*[input_count];
		for(int i =0;i<hidden1_count;i++)
		{
			getline(stream,row);
			std::stringstream colstream(row);
			firstE[i] = new double[input_count];
			for(int j = 0;j<input_count;j++)
			{
				getline(colstream,col,' ');
				firstE[i][j]= strtof(col.c_str(),0);
			}
		}

		secondE = new double* [hidden2_count];
		for(int i = 0; i<hidden2_count;i++)
		{
			getline(stream,row);
			std::stringstream colstream(row);
			secondE[i] = new double[hidden1_count];
			for(int j = 0;j<hidden1_count;j++)
			{
				getline(colstream,col,' ');
				secondE[i][j]= strtof(col.c_str(),0);
			}
		}

		thirdE = new double*[output_count];
		for(int i = 0;i<output_count;i++)
		{
			getline(stream,row);
			std::stringstream colstream(row);
			thirdE[i] = new double[hidden2_count];
			for(int j = 0;j<hidden2_count;j++)
			{
				getline(colstream,col,' ');
				thirdE[i][j]= strtof(col.c_str(),0);
			}
		}
		stream.close();
	}
	Network::~Network() {
		// Auto-generated destructor stub
		for(int i = 0;i<output_count;i++)
			delete [] thirdE[i];
		delete []thirdE;
		for(int i = 0; i<hidden2_count;i++)
			delete [] secondE[i];
		delete []secondE;
		for(int i = 0;i<hidden1_count;i++)
			delete [] firstE[i];
		delete []firstE;
		for(int i = 0;i<output_count;i++)
			delete [] thirdWeight[i];
		delete thirdWeight;
		for(int i = 0; i<hidden2_count;i++)
			delete [] secondWeight[i];
		delete []secondWeight;
		for(int i = 0;i<hidden1_count;i++)
			delete [] firstWeight[i];
		delete []firstWeight;
		delete [] inter1;
		delete [] inter2;
		delete [] input;
		delete [] out;
	}

	//initialize random weights and eligibility traces
	void Network::randomWeights()
	{
		srand(time(NULL));
	#pragma omp parallel for
 		for(int i = 0 ;i<hidden1_count;i++)
			for(int j = 0;j<input_count;j++){
				firstWeight[i][j] = rand() / (1000*double(RAND_MAX)); // number between 0 and 1
				firstE[i][j] = 0;
			}

#pragma omp parallel for
		for(int j = 0 ;j<hidden2_count;j++)
			for(int i = 0 ;i<hidden1_count;i++){
				secondWeight[j][i] = rand() / (1000*double(RAND_MAX));
				secondE[i][j] = 0;
			}

#pragma omp parallel for
		for(int j = 0 ;j<output_count;j++)
			for(int i = 0 ;i<hidden2_count;i++)
			{
				thirdWeight[j][i] = rand() / (1000*double(RAND_MAX));
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
		return (exp(stretch*node) -exp(-stretch*node))/(exp(stretch*node) + exp(-stretch*node));
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
		double * Network::feedForward(double * in)
		{
			input[0] = 1; // bias
			for(int i = 1;i<input_count;i++)
			{
				input[i] = in[i-1];
			}
			double inter1[hidden1_count];
			//std::cout<<"inside feed forward\n";
	#pragma omp parallel for
			for(int j = 1 ;j<hidden1_count;j++)//skips the bias
			{
				inter1[j] = 0;
				for(int i = 0;i<input_count;i++)
				{
					inter1[j] += input[i]*firstWeight[j][i];
				}
				//std::cout<<inter1[j]<<" "<<sigmoid(inter1[j])<<std::endl;
				inter1[j] = sigmoid(inter1[j]);
			}

			inter1[0] = 1; //bias in the hidden layer

			//std::cout<<"finished first intersection "<<std::endl;

			 //bias in the hidden layer
			double inter2[hidden2_count];
	#pragma omp parallel for
			for(int j = 1 ;j<hidden2_count;j++)//skips the bias
			{

				inter2[j] = 0;
				for(int i = 0;i<hidden1_count;i++)
				{
					inter2[j] += inter1[i]*secondWeight[j][i];
				}
				//std::cout<<inter2[j]<<" "<<hyperbolic(inter2[j],stretch)<<std::endl;
				inter2[j] = sigmoid(inter2[j]);
			}
			inter2[0] = 1;
			//std::cout<<"finished second intersection "<<std::endl;

			double out[output_count];
	#pragma omp parallel for
			for(int j = 0 ;j<output_count;j++)
			{
				out[j] = 0;
				for(int i = 0; i <hidden2_count;i++)
				{
					out[j] += inter2[i] * thirdWeight[j][i];
				}
				//std::cout<<out[j]<<" "<<sigmoid(out[j])<<std::endl;
				out[j] = sigmoid(out[j]);
			}
			return out;
		}

	//run the feed forward
	double*  Network::feedForwardSave(double * in)
	{		
		input[0] = 1; // bias
		for(int i = 1;i<input_count;i++)
		{
			input[i] = in[i-1];
		}
		//std::cout<<"inside feed forward\n";
#pragma omp parallel for
		for(int j = 1 ;j<hidden1_count;j++)//skips the bias
		{
			inter1[j] = 0;
			for(int i = 0;i<input_count;i++)
			{
				inter1[j] += input[i]*firstWeight[j][i];
			}
			//std::cout<<inter1[j]<<" "<<sigmoid(inter1[j])<<std::endl;
			inter1[j] = sigmoid(inter1[j]);
		}
		
		inter1[0] = 1; //bias in the hidden layer

		//std::cout<<"finished first intersection "<<std::endl;
		
		 //bias in the hidden layer
#pragma omp parallel for
		for(int j = 1 ;j<hidden2_count;j++)//skips the bias
		{

			inter2[j] = 0;
			for(int i = 0;i<hidden1_count;i++)
			{
				inter2[j] += inter1[i]*secondWeight[j][i];
			}
			//std::cout<<inter2[j]<<" "<<hyperbolic(inter2[j],stretch)<<std::endl;
			inter2[j] = sigmoid(inter2[j]);
		}
		inter2[0] = 1;
		//std::cout<<"finished second intersection "<<std::endl;
		

#pragma omp parallel for
		for(int j = 0 ;j<output_count;j++)
		{
			out[j] = 0;
			for(int i = 0; i <hidden2_count;i++)
			{
				out[j] += inter2[i] * thirdWeight[j][i];
			}
			//std::cout<<out[j]<<" "<<sigmoid(out[j])<<std::endl;
			out[j] = sigmoid(out[j]);
		}
		return out;
	}

	/*
	 * update the parameters of the neural network with the reward
	 */
	void Network::update(int reward)
	{
		
//std::cout<<"updating\n";
		// error signal for gradient descent
		double delta4 = reward + out[0]-oldvalue;
		
		//calculate current eligibility traces while back propagating
		
		for(int k = 0;k<output_count;k++ )
		{
//std::cout<<k<<" k\n";
#pragma omp parallel for
			for(int j = 0;j<hidden2_count;j++)
			{
//std::cout<<j<<" j\n";	
				double firsttemp = out[k]*(1-out[k])*inter2[j];
				thirdE[k][j] = lambda * thirdE[k][j] + firsttemp;
				thirdWeight[k][j] += gam * delta4*thirdE[k][j];
				for(int i = 0; i<hidden1_count;i++)
				{
//std::cout<<"i\n";
					double secondtemp = firsttemp* thirdWeight[k][j] * inter1[i]*(1-inter2[j]);
					secondE[j][i] = lambda*secondE[j][i] + secondtemp  ;
					secondWeight[j][i] += beta * delta4*secondE[j][i];
					for(int h = 0;h<input_count;h++)
					{
//std::cout<<"h\n";
						firstE[i][h] = lambda* firstE[i][h] + secondtemp						 
							*secondWeight[j][i]*(1-inter1[i])*
							input[h];
						firstWeight[i][h] += alpha * delta4*firstE[i][h];
					}
				}
			}
		}
		//std::cout<<getWeights()<<std::endl;
		
		//update the weights with the update rule


		//set old value
		//if(reward == 0 )
			//std::cout<<delta4<<": delta4, out :"<<out[0]<<", old: "<<oldvalue <<std::endl;
	}
	std::string Network::getWeights()
	{
		std::stringstream ss;
		std::cout<<"getting third"<<std::endl;
		std::cout<<"getting first\n";
		ss<<"alpha="<<alpha<<std::endl;
		ss<<"beta="<<beta<<std::endl;
		ss<<"gamma="<<gam<<std::endl;
		ss<<"lambda="<<lambda<<std::endl;
		ss<<"input="<<input_count<<std::endl;
		ss<<"hidden1="<<hidden1_count<<std::endl;
		ss<<"hidden2="<<hidden2_count<<std::endl;
		ss<<"output="<<output_count<<std::endl;

		for(int j = 0;j<hidden1_count;j++)
		{
			for(int i = 0; i<input_count;i++)
			{
				ss<<firstWeight[j][i]<<" ";
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
		for(int j = 0;j<output_count;j++)
		{
			for(int i = 0;i<hidden2_count-1;i++)
			{
				ss<<thirdWeight[j][i]<<" ";
			}
			ss<<std::endl;
		}

		for(int j = 0;j<hidden1_count;j++)
		{
			for(int i = 0; i<input_count;i++)
			{
				ss<<firstE[j][i]<<" ";
			}
			ss<<std::endl;
		}
		for(int j = 0;j<hidden2_count;j++)
		{
			for(int i = 0 ; i<hidden1_count;i++)
			{
				ss<<secondE[j][i]<<" ";
			}
			ss<<std::endl;
		}
		for(int j = 0;j<output_count;j++)
		{
			for(int i = 0;i<hidden2_count-1;i++)
			{
				ss<<thirdE[j][i]<<" ";
			}
			ss<<std::endl;
		}

		return ss.str();
	}
}
