#pragma once
#include"mywindow.h"
#include<fstream>
bool negNo(int n) {
	return (n < 0);
}

bool checkNegNo(int n) {
	if (negNo(n)) {
		cout << "Day la so am";
		return true;
	}
	return false;
}
class Banker
{
private:
	int n;
	int m;
	v<int> Avail;
	v<v<int>>Allocation;
	v<v<int>>Max;
	v<v<int>>Request;
	v<v<int>>Need;
	v<int>Work;
	v<bool>Finish;
public:
	Banker(int nn, int mm, v<int> avail, v<v<int>>allocation, v<v<int>>max, v<v<int>>request, v<v<int>>need)
	{
		n = nn;
		m = mm;
		Avail = avail;
		Allocation = allocation;
		Max = max;
		Request = request;
		Need = need;
		Work = Avail;
	}
	void Cal_Need()
	{
		Need.resize(n, v<int>(m, 0));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				Need[i][j] = Max[i][j] - Allocation[i][j];
	}
	void Plus_Work_Allo(int j)
	{
		for (int i = 0; i < m; i++)
		{
			Work[i] = Work[i] + Allocation[j][i];
		}
	}

	void Cal_Max()
	{
		Max.resize(n, v<int>(m, 0));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				Max[i][j] = Need[i][j] + Allocation[i][j];
	}
	bool Is_A_Smaller_Equal_B(int i, v<v<int>>a, v<int>b)
	{
		bool flag = true;
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] > b[j])
			{
				flag = false;
				break;
			}
		}
		return flag;
	}
	bool Is_A_Smaller_Equal_B(v<int>a, v<int>b)
	{
		bool flag = true;
		for (int j = 0; j < m; j++)
		{
			if (a[j] > b[j])
			{
				flag = false;
				break;
			}
		}
		return flag;
	}

	void Print_String_Of_Safety(v<int>List)
	{
		for (int i = 0; i < n - 1; i++)
			std::cout << " P" << List[i] << " ->";
		std::cout << " P" << List[n - 1] << std::endl;
	}
	void Subtract_Two_Vector(v<int>& A, v<int>B)
	{
		for (int i = 0; i < m; i++)
		{
			A[i] = A[i] - B[i];
		}
	}
	void Plus_Two_Vector(v<int>& A, v<int>B)
	{
		for (int i = 0; i < m; i++)
		{
			A[i] = A[i] + B[i];
		}
	}
	void Nhap_Request(v<int>& id, v<bool>Finish)
	{
		v<int>R;
		int size;
		std::string tmp;
		int j = 0;
		int number_id = id.size();
		int number_request = Request.size();
		std::cout << "Nhap so pid can request: ";
		while (1)
		{
			std::getline(std::cin, tmp);
			if (tmp != "")
				if (isDigit(tmp))
				{
					size = stoi(tmp);
					break;
				}
		}
		for (int i = number_request; i < number_request + size; i++)
		{
			while (1)
			{
				std::cout << "Nhap pid: ";
				std::getline(std::cin, tmp);
				if (tmp != "")
					if (isDigit(tmp) && stoi(tmp) >= 0 && stoi(tmp) < n && !Finish[stoi(tmp)])
					{
						id.push_back(stoi(tmp));
						break;
					}
			}
			std::cout << "Nhap: ";
			int y = whereY();
			int x = 4;
			for (j = 0; j < m; j++)
			{

				while (1)
				{
					gotoXY((x += 4), y);
					std::getline(std::cin, tmp);
					if (tmp != "")
						if (isDigit(tmp))
						{
							R.push_back(stoi(tmp));
							break;
						}
				}
			}
			Request.push_back(R);
			Request[i].push_back(id[number_id++]);
		}
	}

	bool isProcessFinished(int process) {
		for (int i = 0; i < m; i++) {
			if (Allocation[process][i] != 0) {
				return false;
			}
		}
		return true;
	}

	void Print_String_Of_DeadLock(int result, v<int>List)
	{
		if (result == 1)
		{
			std::cout << "Phat hien DEADLOCK!\n";
			gotoXY(32, 5 + 2);
			std::cout << "Danh sach tien trinh bi DEADLOCK: ";
			int size = List.size();
			for (int i = 0; i < size - 1; i++)
			{
				std::cout << List[i] << ", ";
			}
			std::cout << List[size - 1] << ".\n";
		}
		else
		{
			std::cout << "Khong bi DEADLOCK\n";
			gotoXY(32, 5 + 2);
			Need = Request;
			if (Safety(List))
			{
				Print_String_Of_Safety(List);
			}
		}
	}
	int Safety(v<int>& List)
	{
		List.clear();
		if ((Max.empty() && Need.empty()) || Allocation.empty() || Avail.empty())
			return false;
		if (Need.empty())
			Cal_Need();
		if (Max.empty())
			Cal_Max();
		Work = Avail;
		Finish.assign(n, false);
		int y = 0;
		int flag_safe = true;

		for (int i = 0; i < n; i++)
		{
			if (Finish[i])
				continue;
			if (Is_A_Smaller_Equal_B(i, Need, Work))
			{
				List.push_back(i);
				Plus_Work_Allo(i);
				Finish[i] = true;
				i = -1;
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (!Finish[i])
			{
				flag_safe = false;
				break;
			}
		}
		if (flag_safe)
		{
			return true;
		}
		return false;
	}
	int Resource_Request(int id, v<int>Request)
	{
		v<int>List;
		int Finish;
		if (Need.empty())
			Cal_Need();
		if (Is_A_Smaller_Equal_B(Request, Need[id]))
		{
			if (Is_A_Smaller_Equal_B(Request, Avail))
			{
				Subtract_Two_Vector(Avail, Request);
				Plus_Two_Vector(Allocation[id], Request);
				Subtract_Two_Vector(Need[id], Request);
				Finish = Safety(List);
				if (!Finish)
				{
					Plus_Two_Vector(Avail, Request);
					Subtract_Two_Vector(Allocation[id], Request);
					Plus_Two_Vector(Need[id], Request);
					return 0;
				}
				else
					return 1;
			}
			else
			{
				return 0; // wait
			}
		}
		else
		{
			return -1; //Deadlock
		}
	}
	int Is_AllProcess_Finish(v<bool>Finish)
	{
		for (int i = 0; i < Finish.size(); i++)
			if (!Finish[i])
				return 0;
		return 1;
	}

	int DetectDeadLock(v<int>& List)
	{
		List.clear();
		if (Allocation.empty() || Avail.empty())
			return false;
		if (Request.empty())
		{
			Request.resize(n, v<int>(m + 1, 0));
		}
		Work = Avail;
		Finish.assign(n, false);
		int flag = false;
		for (int i = 0; i < n; i++)
		{
			if (!Finish[i] && isProcessFinished(i))
				Finish[i] = true;
		}
		for (int i = 0; i < n; i++)
		{
			if (Finish[i])
				continue;
			if (Is_A_Smaller_Equal_B(i, Request, Work))
			{
				Plus_Work_Allo(i);
				Finish[i] = true;
				i = -1;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (!Finish[i])
			{
				flag = true;
				List.push_back(i);
			}
		}
		if (flag)
		{
			return true;
		}
		else return false;
	}
	void AddRequest()
	{

		v<bool>Finish(n, false);
		v<int>List;
		v<int>List_tmp;
		v<int>id;
		int tmp;
		char key;
		int number_request = Request.size();
		if (Need.empty())
		{
			if (!Max.empty())
				Cal_Need();
			else if (!Request.empty())
				Need = Request;
			else return;
		}
		for (int i = 0; i < number_request; i++) // Nếu có Request sẵn nxm thì add thêm id vào thành nx(m+1)
		{
			id.push_back(Request[i][m]);
		}

		
		while (!Is_AllProcess_Finish(Finish))// Hoàn thành tất cả tiến trình
		{
			int flag_Event = false;
			tmp = 0;
			std::cout << "Nhan Enter de nhap trong vong 2 giay !!" << std::endl;
			for (int i = 0; i < 2; i++)
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));

				if (_kbhit())
				{
					key = _getch();
					if (key == 13)
					{
						flag_Event = true;
						break;
					}
				}
			}
			if (flag_Event) // Nếu có Enter thì nhập request ( gồm id ) vào thêm vào vị trí cuối
			{
				Nhap_Request(id, Finish);
				number_request = Request.size();
			}
			for (int i = 0; i < number_request; i++)
			{
				int result = Resource_Request(id[i], Request[i]); // kiểm tra xem request được nhận không
				if (result == 1)//chấp nhận - đã cập nhật
				{
					std::cout << "\t\tRequest cua Process " << id[i] << " duoc phep\n";
					id.erase(id.begin() + i);
					Request.erase(Request.begin() + i); number_request--;
					i--;
				}
				else if (result == -1) // từ chối
				{
					std::cout << "\t\tRequest cua Process " << id[i] << " se gay deadlock\n";
					std::cout << "\t\tTien hanh block Request cua " << "Process " << id[i] << "\n";
					id.erase(id.begin() + i);
					Request.erase(Request.begin() + i); number_request--;
					i--;
				}
				else //request sẽ chờ
				{
					std::cout << "\t\tRequest cua Process " << id[i] << " dang cho\n";
				}
			}
			number_request = Request.size();

			for (int i = 0; i < n; i++)//Thuật toán Safety
			{
				if (Finish[i])
				{
					continue;
				}
				if (Is_A_Smaller_Equal_B(i, Need, Avail))
				{
					std::cout << "\tProcess " << i << " dang chay\n";
					List.push_back(i);
					Plus_Two_Vector(Avail, Allocation[i]);
					Finish[i] = true;
					Allocation[i] = v<int>(m, 0);
					std::cout << "\tProcess " << i << " da xong\n";
					break;
				}
			}
		}
		Print_String_Of_Safety(List);
	}
	bool readSafety(string address)
	{
		ifstream safety(address);
		if (!safety.is_open()) {
			cout << "File loi";
			return false;
		}
		safety >> n;
		safety >> m;
		Avail.clear();
		Avail.resize(m, 0);
		Allocation.clear();
		Allocation.resize(n, v<int>(m, 0));
		Max.clear();
		Request.clear();
		v<int>requestTmp = v<int>(n, -1);
		string check;
		string trash;
		do {
			int flag;
			getline(safety, trash);
			getline(safety, check, '\n');
			if (!check.compare("Avail:")) flag = 1;
			else if (!check.compare("Max:")) flag = 2;
			else if (!check.compare("Allo:")) flag = 3;
			else if (!check.compare("Request:")) flag = 4;
			else flag = 0;
			
			int tmp;
			switch (flag) {
			case 1:
				for (int j = 0; j < m; j++) {
					safety >> tmp;
					if (checkNegNo(tmp) == true)
						return false;
					Avail[j] = tmp;
				}
				break;
			case 2:
				Max.resize(n, v<int>(m, 0));
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						safety >> tmp;
						if (checkNegNo(tmp) == true)
							return false;
						Max[i][j] = tmp;
					}
				}
				break;
			case 3:
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						safety >> tmp;
						if (checkNegNo(tmp) == true)
							return false;
						if (!Max.empty())
						{
							if (tmp > Max[i][j] ) {
								cout << "Du lieu sai!";
								return false;
							}
						}
						Allocation[i][j] = tmp;
					}
				}
				if(Max.empty())
				Max = Allocation;
				break;
			case 4:
			{
				Request.resize(n, v<int>(m + 1, 0));
				for (int i = 0; i < n; i++) {
					for (int j = 0; j <= m; j++) {
						safety >> tmp;
						if (checkNegNo(tmp) == true)
							return false;
						if (j == m) {
							if (tmp >= n) {
								cout << "Luong proccess vuot qua muc cho phep!";
								return false;
							}
						}
						Request[i][j] = tmp;
					}
				}
				break;
			}
			default:
				cout << "Du lieu khong dung hoac khong co du lieu!";
				return false;
			}
		} while (!safety.eof());
		return true;
	}
	void UI_add_File(string address[], int sl)
	{

		Box(1, 4, 118, 21, 159, " ");
		int x = 3, y = 5;
		int h = 1;
		int xptr = x, yptr = y;
		int xpre = xptr, ypre = yptr;
		int b_color = 159;
		int checkLuaChon = 1;
		for (int i = 0; i < sl; i++)
		{
			gotoXY(x + 2, y + i);
			cout << address[i];
		}
		gotoXY(x + 2, y + sl);
		cout << "Tro ve";
		ShowCur(0);
		while (1)
		{
			if (checkLuaChon)
			{
				gotoXY(xpre, ypre);
				cout << " ";
				xpre = xptr;
				ypre = yptr;
				gotoXY(xptr, yptr);
				cout << ">";
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
							yptr = y + h * (sl);
						}
					}
					else if (c == 80)
					{
						checkLuaChon = true; // đã bấm
						if (yptr != y + h * (sl))
							yptr += h;
						else
						{
							yptr = y;
						}
					}
				}
				else if (c == 13)
				{
					if (yptr - y == sl)
					{
						return;
					}
					else
					{
						int choice = yptr - y;
						readSafety(address[choice]);
						break;
					}
				}
			}
		}
	}
	void Print_One_Process(int id)
	{
		int x = 50, y = 8;
		int i;
		gotoXY(x, y++);
		cout << "Avail: ";
		for (i = 0; i < m; i++)
			cout << Avail[i] << " ";
		gotoXY(x, y++);
		cout << "Tien trinh P"<<id<<": ";
		gotoXY(x, y++);
		cout << "Max cua P" << id << ": ";
		for (i = 0; i < m; i++)
			cout << Max[id][i] << " ";
		gotoXY(x, y++);
		cout << "Allocation cua P" << id << ": ";
		for (i = 0; i < m; i++)
			cout << Allocation[id][i] << " ";
		gotoXY(x, y++);
		gotoXY(x, y++);
		cout << "Nhan -> hoac <-  de xem cac tien trinh khac";
		gotoXY(x, y++);
		cout << "Nhan ENTER de tiep tuc";
	}
	void DanhSachProcess()
	{
		Box_E(35, 0, 50, 2, 159, "DANH SACH TIEN TRINH");
		int x = 3, y = 5;
		int CurPage = 0;
		int Nextpage = false;
		int Prepage = false;
		int checkUI = true;
		while (1)
		{
			if (checkUI)
			{
				Print_One_Process(CurPage);
				checkUI = false;
			}
			if (Nextpage)
			{
				CurPage++;
				Nextpage = false;
				checkUI = true;
			}
			if (Prepage)
			{
				CurPage--;
				Prepage = false;
				checkUI = true;
			}

			if (_kbhit())
			{
				char c = _getch();
				if (c == -32)
				{

					c = _getch();
					if (c == 75)
					{
						if (CurPage >0)
							Prepage = true;
					}
					if (c == 77)
					{
						if (CurPage < n-1)
							Nextpage = true;
					}
				}
			}
		}
	}
};
