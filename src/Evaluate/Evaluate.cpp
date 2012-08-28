/*
 * Evaluate.cpp
 *
 *  Created on: Aug 9, 2012
 *      Author: ivan
 *      class to evaluate the players of tron
 */

#include "Evaluate.h"

namespace tron {

	Evaluate::Evaluate(Player * one, Player * two):one_count(0),two_count(0),one(one),gap(10),two(two) {
	   // "C" locale

		 std::time_t t = std::time(0);   // get time now
		    struct tm * now = localtime( & t );
		    std::stringstream ss;
		   ss << (now->tm_year + 1900) << '-'
		         << (now->tm_mon + 1) << '-'
		         <<  now->tm_mday<< '-'<<now->tm_hour<<now->tm_min<<now->tm_sec;
		   date = ss.str();
	}

	Evaluate::~Evaluate() {
		// cleaning up
		delete one;
		delete two;
	}
	void Evaluate::progress(int winner)
	{
		if(winner == 0)
		{
			one_count++;
		}
		else if(winner ==1)
		{
			two_count++;
		}
		if((one_count+two_count) %gap == 0)//played gap number of games
		{
			std::cout<<"Processing";
			std::stringstream oness;
			oness<<"Result/one/"<<date<<"."<<one_count+two_count<<".txt";
			std::string out(oness.str());
			std::ofstream onestream(out.c_str());
			onestream<<one->getNet()->getWeights();
			onestream.close();

			std::stringstream twoss;
			twoss<<"Result/two/"<<date<<"."<<two_count+one_count<<".txt";
			std::string twoout(twoss.str());
			std::ofstream twostream(twoout.c_str());
			twostream<<two->getNet()->getWeights();
			twostream.close();

			std::stringstream rate;
			rate<<"Result/"<<date<<".rating.txt";
			std::string rateout(rate.str());
			std::ofstream rating(rateout.c_str(),std::fstream::app);
			rating<<"Number of games "<<one_count+two_count<<std::endl;
			rating<<"one - "<< (one_count*100.0) / (one_count+two_count)<< "% wins"<<std::endl;
			rating<<"two - "<<(two_count*100.0)/(one_count+two_count)<<"% wins"<<std::endl<<std::endl;
			rating<<two->printGrid()<<std::endl;
			rating.close();

		}
	}

}
