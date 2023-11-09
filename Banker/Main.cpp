#include<iostream>
#include<vector>
#include<conio.h>
#include<string>
#include<thread>
#include"mywindow.h"
#include"Banker.h"
#include"SFML/Window.hpp"
#include"UI.h"
#define v std::vector
#define pause system("pause")
#define cls system("cls")
int main()
{
	v<int> Avail = {6,4,4,2};
	v<v<int>> Allocation = { {2,0,1,1},
		{1,1,0,0},
		{1,0,1,0},
		{0,1,0,1} };
	v<v<int>> Max = { {3,2,1,1},
		{1,2,0,2},
		{3,2,1,0},
		{2,1,0,1} };
	v<v<int>> Request = { {2,1,0,0,3},{2,1,0,0,1} };
	v<v<int>> Need;
	Banker m = Banker(4, 4, Avail, Allocation, Max, Request, Need);
	m.AddRequest();
	pause;
	
	return 0;
}