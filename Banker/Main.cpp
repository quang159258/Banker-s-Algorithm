#include<iostream>
#include<vector>
#include<conio.h>
#include<string>
#include<thread>
#include"mywindow.h"
#include"Banker.h"

#define v std::vector
#define pause system("pause")
#define cls system("cls")
int main()
{
	v<int> Avail = {3,3,2 };
	v<v<int>> Allocation = { {  0,1, 0},
							{ 2,0, 0},
							{  3,0, 2 },
							{ 2,1,1 },
							{ 0, 0, 2 } };
	v<v<int>> Max;
	v<v<int>> Request;
	v<v<int>> Need = {
		{7,4,3},
		{1,2,2},
		{6,0,0},
		{0,1,1},
		{4,3,1} };
	Banker m = Banker(5, 3, Avail, Allocation, Max, Request, Need);
	m.AddRequest();
	pause;
	return 0;
}
