#include<iostream>
#include<vector>
#include"SFML/Window.hpp"
#include<conio.h>
#include<string>
#include<thread>
#include"mywindow.h"
#include"UI.h"
#include"Banker.h"


#define v std::vector
#define pause system("pause")
#define cls system("cls")
int main()
{
    v<int> Avail = {0,0,0};
    v<v<int>> Allocation = 
    {
        {0,1,0},
        {2,0,0},
        {3,0,3},
        {2,1,1},
        {0,0,2}
    };
    v<v<int>> Max;
    v<v<int>> Request = 
    {
        {0,0,0,0},
        {2,0,2,1},
        {0,0,0,2},
        {1,0,0,3},
        {0,0,2,4}
    };
    v<v<int>> Need;
	string nd[7] = { "1. Nhap File","2. Nhap thu cong","3. Check thong tin","4. Kiem tra an toan","5. Kiem tra DEADLOCK","6. Mo phong Banker","0. Dung chuong trinh" };
	int sl = 7;
    int n, m;
	int h = 2, w = MaxLengthString(nd, sl) + 2;
	int x = 3, y = 5;
	int xptr = x, yptr = y;
	int xpre = xptr, ypre = yptr;
	int b_color = 159, b_color_bright = 75;
    v<int>List;
    int tmp;
    Banker B = Banker(5, 3, Avail, Allocation, Max, Request, Need);
    Banker C = Banker(5, 3, Avail, Allocation, Max, Request, Need);
loop:
    textcolor(7);
    cls;
    ShowCur(0);
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
                        UI_Nhap(n, m, Avail, Allocation, Max, Request, Need);
                        B = Banker(n, m, Avail, Allocation, Max, Request, Need);
                        break;
                    case 2:
                        break;
                    case 3:
                        C = B;
                        if (C.Safety(List))
                        {
                            Box(30, y, 7*List.size(), 3, 159, " ");
                            gotoXY(32, y + 1);
                            C.Print_String_Of_Safety(List);
                        }
                        else
                        {
                            Box(30, y, 50, 3, 159, " ");
                            gotoXY(32, y + 1);
                            cout << "Trang thai KHONG AN TOAN UNSAFE!!";
                        }
                        _getch();
                        break;
                    case 4:
                        C = B;
                        tmp = C.DetectDeadLock(List);
                        Box(30, y, 50, 3, 159, " ");
                        gotoXY(32, y + 1);
                        C.Print_String_Of_DeadLock(tmp, List);
                        _getch();
                        break;
                    case 5:
                        textcolor(7);
                        C = B;
                        tmp = C.DetectDeadLock(List);
                        C = B;
                        if(!tmp)
                        {
                            cls;
                            C.AddRequest();
                        }
                        else
                        {
                            Box(30, y, 50, 3, 159, " ");
                            gotoXY(32, y + 1);
                            cout << "Cac Tien Trinh dang DEADLOCK!!";
                        }
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