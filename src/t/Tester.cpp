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

	Network* net = new Network(10,100,100, 1, 0.4,0.2);
	double in[] = {-1,+1,-0.5,-0.4,+1,3,1,-2,2,1};
	std::cout<<"hello world\n";
	double * out = net->feedForward(in);
	net->update(0);
	std::cout<<out[0]<<std::endl;
	return 0;
}
