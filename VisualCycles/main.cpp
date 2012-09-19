 /*
 *  Created on: Aug 25, 2012
 *      Author: ivan
 */

#include "Chamber.h"
#include <iostream>
using namespace tron;
int main(void)
{
	std::vector<std::vector< int> > matrix;
	/*int width = 10;
	for(int i = 0 ;i<width;i++){
		std::vector<int> temp;
		for(int j =0;j<width;j++)
		{
			if(i == 0 ){
				temp.push_back(-2);
				
			}
			
			else if(i  == 7)
				temp.push_back(-3);
			else if(i== 9)
				temp.push_back(1);
			else
				temp.push_back(0);
		}
		matrix.push_back(temp);
	}*/
/*
	matrix[7][3] = -1;
	matrix[3][2] = -1;
	matrix[3][3] = -1;
	matrix[4][3] = -1;
	matrix[4][4] = -1;
	matrix[5][4] = -1;
	matrix[6][4] = -1;
	matrix[3][4] = -1;
	matrix[4][5] = -1;
	matrix[5][5] = -1;
	matrix[5][6] = -1;
	matrix[5][7] = -1;
	matrix[5][8] = -1;
	matrix[4][8] = -1;
	matrix[4][7] = -1;
	matrix[1][6] = -1;
	matrix[2][4] = -1;
	matrix[2][5] = -1;
	matrix[2][6] = -1;
	matrix[1][9] = -1;
	matrix[1][7] = -1;
	matrix[1][8] = -1;
	matrix[1][2] = -1;

*/
	



/*		TEST GRID 1
	-2	-2	-2	-2	-2	-2	-2	-2	-2	-2
	-2	-3	-4	-3	-2	-2	-1	0	-1	-2
	0	0	0	-5	-4	0	0	2	1	0
	0	-10	-11	0	0	0	0	4	0	0
	-7	-8	-9	0	6	6	6	4	0	-6
	-5	-6	-7	0	6	6	6	4	0	-4
	-3	-4	-5	0	5	6	6	4	0	-2
	-1	-2	-3	0	3	4	5	4	0	0
	1	0	-1	0	1	2	3	2	0	1
	1	1	1	1	1	1	1	1	1	1	*/
	/*matrix[0][0] = -2;
	matrix[0][1] = -2;
	matrix[0][2] = -2;	
	matrix[0][3] = -2;
	matrix[0][4] = -2;	
	matrix[0][5] = -2;	
	matrix[0][6] = -2;	
	matrix[0][7] = -2;
	matrix[0][8] = -2;	
	matrix[0][9] = -2;
	matrix[1][0] = -2;
	matrix[1][1] = -3;
	matrix[1][2] = -4;
	matrix[1][3] = -3;
	matrix[1][4] = -2;
	matrix[1][5] = -2;
	matrix[1][6] = -1;
	matrix[1][7] = 0;
	matrix[1][8] = -1;
	matrix[1][9] = -2;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 0;
	matrix[2][3] = 5;
	matrix[2][4] = 4;
	matrix[2][5] = 0;
	matrix[2][6] = 0;
	matrix[2][7] = 2;
	matrix[2][8] = 1;
	matrix[2][9] = 0;
	matrix[3][0] = 0;
	matrix[3][1] = -10;
	matrix[3][2] = -11;
	matrix[3][3] = -5;
	matrix[3][4] = 0;
	matrix[3][5] = 0;
	matrix[3][6] = 0;
	matrix[3][7] = 4;
	matrix[3][8] = 0;
	matrix[3][9] = 0;
	matrix[4][0] = -7;
	matrix[4][1] = -8;
	matrix[4][2] = -9;
	matrix[4][3] = 0;
	matrix[4][4] = 6;
	matrix[4][5] = 6;
	matrix[4][6] = 6;
	matrix[4][7] = 4;
	matrix[4][8] = 0;
	matrix[4][9] = -6;
	matrix[5][0] = -5;
	matrix[5][1] = -6;
	matrix[5][2] = -7;
	matrix[5][3] = -1;
	matrix[5][4] = -16;
	matrix[5][5] = -6;
	matrix[5][6] = -6;
	matrix[5][7] = -4;
	matrix[5][8] = 0;
	matrix[5][9] = 4;
	matrix[6][0] = 3;
	matrix[6][1] = 1;
	matrix[6][2] = 1;
	matrix[6][3] = 1;
	matrix[6][4] = 1;
	matrix[6][5] = 1;
	matrix[6][6] = 1;
	matrix[6][7] = 1;
	matrix[6][8] = 1;
	matrix[6][9] = 2;
	matrix[7][0] = 1;	
	matrix[7][1] = 2;
	matrix[7][2] = 3;	
	matrix[7][3] = 0;
	matrix[7][4] = 3;	
	matrix[7][5] = 4;
	matrix[7][6] = 5;	
	matrix[7][7] = 4;
	matrix[7][8] = 0;	
	matrix[7][9] = 0;
	matrix[8][0] = 1;	
	matrix[8][1] = 0;
	matrix[8][2] = 1;	
	matrix[8][3] = 0;
	matrix[8][4] = 1;	
	matrix[8][5] = 2;
	matrix[8][6] = 3;	
	matrix[8][7] = 2;
	matrix[8][8] = 0;	
	matrix[8][9] = 1;
	matrix[9][0] = 1;	
	matrix[9][1] = 1;	
	matrix[9][2] = 1;
	matrix[9][3] = 1;	
	matrix[9][4] = 1;
	matrix[9][5] = 1;	
	matrix[9][6] = 1;	
	matrix[9][7] = 1;	
	matrix[9][8] = 1;
	matrix[9][9] = 1;*/
	int width = 6;

	for(int i= 0;i<width;i++){
		std::vector<int>temp;
		for(int j = 0;j<width;j++)
		{
			temp.push_back(0);
		}
		matrix.push_back(temp);
	}
	matrix[0][0] = 2;
	matrix[0][1] = 2;
	matrix[0][2] = 2;
	matrix[0][3] = 2;
	matrix[0][4] = 2;
	matrix[0][5] = 2;
	matrix[1][0] = 1;
	matrix[1][1] = 0;
	matrix[1][2] = 0;
	matrix[1][3] = 1;
	matrix[1][4] = 0;
	matrix[1][5] = 0;
	matrix[2][0] = -1;
	matrix[2][1] = 1;
	matrix[2][2] = 1;
	matrix[2][3] = -5;
	matrix[2][4] = 0;
	matrix[2][5] = -2;
	matrix[3][0] = -1;
	matrix[3][1] = 1;
	matrix[3][2] = 1;
	matrix[3][3] = -1;
	matrix[3][4] = -1;
	matrix[3][5] = -1;
	matrix[4][0] = 2;
	matrix[4][1] = 1;
	matrix[4][2] = 9;
	matrix[4][3] = -1;
	matrix[4][4] = -6;
	matrix[4][5] = -6;
	matrix[5][0] = -5;
	matrix[5][1] = -6;
	matrix[5][2] = -7;
	matrix[5][3] = -1;
	matrix[5][4] = -16;
	matrix[5][5] = -6;

	for(int i = 0;i<width;i++)
	{
		for(int j = 0;j<width;j++)
		{
			std::cout<<matrix[i][j]<<"\t";
		}
		std::cout<<std::endl;
	}

	Chamber a(&matrix,width,3,2,1);
	std::cout<<a.getValue()<<std::endl;

	Chamber b(&matrix,width,1,4,2);
	std::cout<<b.getValue()<<std::endl;
	return 0;
}
