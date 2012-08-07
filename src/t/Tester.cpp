//============================================================================
// Name        : Cycles.cpp
// Author      : Ivan Nelson Togboa Cadri
// Version     :
// Copyright   : Your copyright notice
// Description : Tron in C++, Ansi-style
//============================================================================

#include <iostream>
#include "../Neural/Network.h"
#include <iostream>
using namespace tron;

int main(){

	Network* net = new Network(5,20, 1, 0.4,0.2);
	double * in = new double[5];
	in[0] = 2;
	in[1] = 1;
	in[2] = 0.5;
	in[3] = 0.4;
	in[4] = 1;
	std::cout<<"hello world\n";
	double * out = net->feedForward(in);
	std::cout<<out[0]<<std::endl;
	return 0;
}
