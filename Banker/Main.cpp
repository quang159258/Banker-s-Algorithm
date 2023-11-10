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
    v<int> Avail = { 6,4,4,2 };
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
	string nd[6] = { "1. Nhap File","2. Nhap thu cong","3. Kiem tra an toan","4. Kiem tra DEADLOCK","5. Mo phong Banker","0. Dung chuong trinh" };
	int sl = 6;
	int h = 2, w = MaxLengthString(nd, sl) + 2;
	int x = 3, y = 5;
	int xptr = x, yptr = y;
	int xpre = xptr, ypre = yptr;
	int b_color = 159, b_color_bright = 75;
    Banker m = Banker(4, 4, Avail, Allocation, Max, Request, Need);

loop:
    textcolor(7);
    cls;
	xptr = x, yptr = y;
	xpre = xptr, ypre = yptr;
	int checkLuaChon = 1;
	ShowCur(0);
	Box(1, 4, 118, 21, b_color, " ");
	Box_E(45, 0, 31, 2, b_color, "Thuat Toan Banker's");
	n_Box_divide(x, y, w, h, b_color, nd, sl);
    while (1)
    {
        if (checkLuaChon)
        {
            gotoXY(xpre, ypre);
            highlight(xpre, ypre, w, h, b_color, nd[Cal(y, ypre, h)]);
            xpre = xptr;
            ypre = yptr;
            highlight(xptr, yptr, w, h, b_color_bright, nd[Cal(y, yptr, h)]);
            checkLuaChon = false;
        }
        if (_kbhit())
        {
            char c = _getch();
            if (c == -32)
            {

                c = _getch();
                if (c == 72)
                {
                    checkLuaChon = true; // đã bấm
                    if (yptr != y)
                        yptr -= h;
                    else
                    {
                        yptr = y + h * (sl - 1);
                    }
                }
                else if (c == 80)
                {
                    checkLuaChon = true; // đã bấm
                    if (yptr != y + h * (sl - 1))
                        yptr += h;
                    else
                    {
                        yptr = y;
                    }
                }
            }
            else if (c == 13)
            {
                int choice = Cal(y, yptr, h);
                if (choice >= 0 && choice < sl - 1)
                {
                    switch (choice)
                    {
                    case 0:
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        textcolor(7);
                        cls;
                        m.AddRequest();
                        _getch();
                        break;
                    default:
                        break;
                    }
                }
                else
                    break;
                checkLuaChon = true;
                goto loop;
            }
        }
    }
	
	pause;
	
	return 0;
}