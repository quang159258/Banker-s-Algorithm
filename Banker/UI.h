#pragma once

void menu()
{
	sf::Window window;
	window.create(sf::VideoMode(800, 600), "Banker's Algorithm", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(30);
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}
int isDigit(std::string a)
{
    for (char c : a)
        if (!isdigit(c))
            return false;
    return true;
}
void Cal_Need(int n,int m, v<v<int>>&Need,v<v<int>>Max, v<v<int>>Allocation)
{
    Need.resize(n, v<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
}
int Confirm_UI_add()
{
    int check = false;
    textcolor(0);
    Box_E(40, 10, 40, 3, 75, "Xac Nhan Lua Chon");
    Box_E(43, 20, 7, 2, 75, "Y");
    Box_E(70, 20, 7, 2, 75, "N");
    while (1)
    {
        if (_kbhit())
        {

            char c = _getch();
            if (c == 'y' || c == 'Y')
            {
                check = true;
                break;
            }
            else if (c == 'n' || c == 'N')
            {
                check = false;
                break;
            }
        }
    }
    return check;
}
void UI_Nhap(int &n,int &m,v<int>& Avail, v<v<int>>& Allocation, v<v<int>>& Max, v<v<int>>& Request, v<v<int>>& Need)
{
    ShowCur(1);
    Box(1, 4, 118, 21, 159, " ");
    string n_str;
    int n_i;
    int x = 3, y = 8;
    while (1)
    {
        gotoXY(x, y-3);
        cout << "Nhap so tien trinh:(1-10)                            ";
        gotoXY(x, y-3);
        cout << "Nhap so tien trinh:(1-10) ";
        getline(cin, n_str);
        if (n_str != "")
            if (isDigit(n_str) && stoi(n_str) > 0 && stoi(n_str) < 11)
            {
                n = stoi(n_str);
                break;
            }
    }
    while (1)
    {
        gotoXY(x, y-3);
        cout << "Nhap so tai nguyen:(1-5)                                       ";
        gotoXY(x, y-3);
        cout << "Nhap so tai nguyen:(1-5) ";
        getline(cin, n_str);
        if (n_str != "")
            if (isDigit(n_str) && stoi(n_str) > 0 && stoi(n_str) < 6)
            {
                m = stoi(n_str);
                break;
            }
    }
    Avail.clear();
    Avail.resize(m,0);
    Allocation.clear();
    Allocation.resize(n, v<int>(m,0));
    Max.clear();
    Max.resize(n, v<int>(m, 0));
    Request.clear();
    Request.resize(n, v<int>(m+1, 0));
    Need.clear();
    Need.resize(n, v<int>(m, 0));
    Box(1, 4, 118, 21, 159, " ");
    gotoXY(x, y-3);
    cout << "Nhap Avail:";
    int xpre = x+5;
    for (int i = 0; i < m; i++)
    {
        while (1)
        {
            gotoXY(xpre, y);
            getline(cin, n_str);
            if (n_str != "")
            {
                if (isDigit(n_str))
                {
                    Avail[i] = stoi(n_str);
                    xpre += n_str.length() + 3;
                    break;
                }
                else
                {
                    for (int j = 0; j <= n_str.length(); j++)
                    {
                        gotoXY(xpre + j, y);
                        cout << " ";
                    }
                }
            }
        }
    }
    Box(1, 4, 118, 21, 159, " ");
    gotoXY(x, y - 3);
    cout << "Nhap Max:";
    xpre = x + 5;
    for (int i = 0; i < n; i++)
    {
        xpre = x + 5;
        gotoXY(x + 2, y - 1);
        cout << "Tien trinh " << i;
        for (int j = 0; j < m; j++)
        {
            while (1)
            {
                gotoXY(xpre, y + i);
                getline(cin, n_str);
                if (n_str != "")
                {
                    if (isDigit(n_str))
                    {
                        Max[i][j] = stoi(n_str);
                        xpre += n_str.length() + 3;
                        break;
                    }
                    else
                    {
                        for (int k = 0; k <= n_str.length(); k++)
                        {
                            gotoXY(xpre + k, y + i);
                            cout << " ";
                        }
                    }
                }
            }
        }
    }
    Box(1, 4, 118, 21, 159, " ");
    gotoXY(x, y - 3);
    cout << "Nhap Allocation:";
    xpre = x+5;
    for (int i = 0; i < n; i++)
    {
        xpre = x+5;
        gotoXY(x+2, y - 1);
        cout << "Tien trinh " << i;
        for (int j = 0; j < m; j++)
        {
            while (1)
            {
                gotoXY(xpre, y+i);
                getline(cin, n_str);
                if (n_str != "")
                {
                    if (isDigit(n_str)&& stoi(n_str)<=Max[i][j])
                    {
                        Allocation[i][j] = stoi(n_str);
                        xpre += n_str.length() + 3;
                        break;
                    }
                    else
                    {
                        for (int k = 0; k <= n_str.length(); k++)
                        {
                            gotoXY(xpre + k, y+i);
                            cout << " ";
                        }
                    }
                }
            }
        }
        
    }
    
    Box(1, 4, 118, 21, 159, " ");
    gotoXY(x, y - 3);
    cout << "Ban co muon nhap request khong? ";
    int k = 0;
    if (Confirm_UI_add())
    {
        Box(1, 4, 118, 21, 159, " ");
        xpre = x + 5;
        while (1)
        {
            gotoXY(x, y - 3);
            cout << "Nhap so Request:(1-20)                                    ";
            gotoXY(x, y - 3);
            cout << "Nhap so Request:(1-20) ";
            getline(cin, n_str);
            if (n_str != "")
                if (isDigit(n_str) && stoi(n_str) > 0 && stoi(n_str) < 21)
                {
                    k = stoi(n_str);
                    break;
                }
        }
        Request.clear();
        Request.resize(k, v<int>(m + 1, 0));
        for (int i = 0; i < k; i++)
        {
            xpre = x + 5;
            gotoXY(xpre - 3, y - 1);
            cout << "Request thu " << i+1;
            while (1)
            {
                gotoXY(xpre - 3, y);
                cout << "Nhap id cua Process:(0-" << n - 1 <<")" << "                          ";
                gotoXY(xpre - 3, y);
                cout << "Nhap id cua Process:(0-"<<n-1<<") ";
                getline(cin, n_str);
                if (n_str != "")
                {
                    if (isDigit(n_str) && stoi(n_str) >=0&& stoi(n_str) <=n)
                    {
                        Request[i][m] = stoi(n_str);
                        xpre += n_str.length() + 3;
                        break;
                    }
                    else
                    {
                        for (int l = 0; l <= n_str.length(); l++)
                        {
                            gotoXY(xpre + l, y + i);
                            cout << " ";
                        }
                    }
                }
            }
            for (int j = 0; j < m; j++)
            {
                while (1)
                {
                    gotoXY(xpre, y +1);
                    getline(cin, n_str);
                    if (n_str != "")
                    {
                        if (isDigit(n_str))
                        {
                            Request[i][j] = stoi(n_str);
                            xpre += n_str.length() + 3;
                            break;
                        }
                        else
                        {
                            for (int l = 0; l <= n_str.length(); l++)
                            {
                                gotoXY(xpre + l, y +1);
                                cout << " ";
                            }
                        }
                    }
                }
            }
            gotoXY(5, y + 1);
            cout << "                                         ";

        }
    }
    Cal_Need(n,m,Need,Max, Allocation);
}