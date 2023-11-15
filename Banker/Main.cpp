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
    ShowCur(0);
    v<int> Avail;
    v<v<int>> Allocation;
    v<v<int>> Max;
    v<v<int>> Request;
    v<v<int>> Need;
	string nd[6] = { "1. Nhap File","2. Nhap thu cong","3. Kiem tra an toan","4. Kiem tra DEADLOCK","5. Mo phong Banker","0. Dung chuong trinh" };
	int sl = 6;
    string file[3] = { "Safety.txt","Deadlock1.txt","Deadlock2.txt" };
	int h = 2, w = MaxLengthString(nd, sl) + 2;
	int x = 3, y = 5;
	int xptr = x, yptr = y;
    int n, m;
	int xpre = xptr, ypre = yptr;
	int b_color = 159, b_color_bright = 75;
    v<int>List;
    int tmp;
    Banker B = Banker(1, 1, Avail, Allocation, Max, Request, Need);
    Banker C = Banker(1, 1, Avail, Allocation, Max, Request, Need);
    int CheckEmpty = true;
    int CurPage = 0;
    int Nextpage = false;
    int Prepage = false;
    
loop:
    int checkUI = true;
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
        if (checkUI)
        {
            if (!CheckEmpty)
            {
                B.Print_One_Process(CurPage);
                checkUI = false;
            }
        }
        if (Nextpage)
        {
            CurPage++;
            if (CurPage >= B.GetN())
                CurPage = 0;
            Nextpage = false;
            checkUI = true;
        }
        if (Prepage)
        {
            CurPage--;
            if (CurPage <= -1)
                CurPage = B.GetN() - 1;
            Prepage = false;
            checkUI = true;
        }
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
                else if (c == 75&&!CheckEmpty)
                {
                    Prepage = true;
                }
                else if (c == 77 && !CheckEmpty)
                {
                    Nextpage = true;
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
                        CheckEmpty = !(B.UI_add_File(file, 3));
                        break;
                    case 1:
                        UI_Nhap(n, m, Avail, Allocation, Max, Request, Need);
                        B = Banker(n, m, Avail, Allocation, Max, Request, Need);
                        CheckEmpty = false;
                        break;
                    case 2:
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
                    case 3:
                        C = B;
                        tmp = C.DetectDeadLock(List);
                        Box(30, y, 50, 3, 159, " ");
                        gotoXY(32, y + 1);
                        C.Print_String_Of_DeadLock(tmp, List);
                        _getch();
                        break;
                    case 4:
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
	
	return 0;
}