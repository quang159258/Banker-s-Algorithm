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
	v<int> Avail = { 1,5,2,0 };
	v<v<int>> Allocation = { { 0, 0,1, 2 },
							{ 1,0, 0,0 },
							{ 1,3, 5, 4 },
							{ 0, 6, 3,2 },
							{ 0, 0, 1,4 } };
	v<v<int>> Max = { { 0, 0,1, 2 },
							{ 1,7, 5,0 },
							{ 2,3, 5, 6 },
							{ 0, 6, 5,2 },
							{ 0, 6, 5,6 } };
	v<v<int>> Request;
	v<v<int>> Need;
	Banker m = Banker(5, 4, Avail, Allocation, Max, Request, Need);
	m.AddRequest();
	pause;
	return 0;
}
