#include<iostream>
#include<vector>
#include<conio.h>
#include<string>
#include<thread>
#include"mywindow.h"
#define v std::vector
#define pause system("pause")
#define cls system("cls")
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
	bool Is_A_Smaller_Equal_B(int i,v<v<int>>a,v<int>b)
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
			A[i] = A[i] +B[i];
		}
	}
	
	int isDigit(std::string a)
	{
		for (char c : a)
			if (!isdigit(c))
				return false;
		return true;
	}
	void Nhap_Request(v<int> &id,v<bool>Finish)
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
					size=stoi(tmp);
					break;
				}
		}
		
		for (int i = number_request; i < number_request +size; i++)
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
	
	void Print_String_Of_DeadLock(int result,v<int>List)
	{
		if (result==1)
		{
			std::cout << "Phat hien deadlock!\n";
			std::cout << "Danh sach tien trinh bi deadlock: ";
			int size = List.size();
			for (int i = 0; i < size - 1; i++)
			{
				std::cout << List[i] << ", ";
			}
			std::cout << List[size-1] << ".\n";
		}
		else
		{
			std::cout << "Khong\n";
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
	int Resource_Allocation(int id, v<int>Request)
	{
		v<int>List;
		int Finish;
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
			Request.assign(n, v<int>(m, 0));
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
	}
	int Number_UnFinish(v<bool>Finish)
	{
		int c=0;
		for (int i = 0; i < Finish.size(); i++)
			if (!Finish[i])
				c++;
		return c;
	}
	int Find_Index_Of_Id(int id,v<v<int>>R)
	{
		int i=-1;
		for (int j = 0; j < R.size(); j++)
			if (id == R[j][m])
				return j;
		return i;
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
		for (int i = 0; i < number_request; i++)
		{
			id.push_back(i);
			Request[i].push_back(i);
		}
	loop:
		int flag_Event = false;
		tmp = 0;
		std::cout << "Nhan Enter de nhap trong vong 5 giay !!" << std::endl;
		for (int i = 0; i < 5; i++)
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
		if (flag_Event)
		{
			Nhap_Request(id, Finish);
			number_request = Request.size();
		}
		for (int i = 0; i < Request.size(); i++)
		{
			int result = Resource_Allocation(id[i], Request[i]);
			if (result==1)
			{
				std::cout << "\t\tRequest cua Process "<<id[i]<<" duoc phep\n";
				id.erase(id.begin() + i);
				Request.erase(Request.begin() + i);
				i = -1;
			}
			else if (result == -1)
			{
				std::cout << "\t\tRequest cua Process " << id[i] << " se gay deadlock\n";
				std::cout << "\t\tTien hanh block Request cua " << "Process " << id[i]<<"\n";
				id.erase(id.begin() + i);
				Request.erase(Request.begin() + i);
				i = -1;
			}
			else
			{
				std::cout << "\t\tRequest cua Process " << id[i] << " dang cho\n";
			}
		}
		number_request = Request.size();


		Banker class_check(Number_UnFinish(Finish), m, Avail, Allocation, Max, Request, Need);
		if (!Request.empty())
			for (int i = 0; i < n; i++)
			{
				if (!Finish[i])
				{
					class_check.Allocation[tmp] = Allocation[i];
					class_check.Max[tmp] = Max[i];
					int k = Find_Index_Of_Id(i, Request);
					if (k != -1)
						class_check.Request[tmp] = Request[k];
					class_check.Need[tmp] = Need[i];
					tmp++;
				}
				
			}
		if (!class_check.Safety(List_tmp))
		{
			std::cout << "Da xay ra DEADLOCK\n";
			_getch();
			return;
		}
		


		for (int i = 0; i < n; i++)
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
				std::cout << "\tProcess " << i << " da xong\n";
				break;
			}
		}
		if (!Is_AllProcess_Finish(Finish))
			goto loop;
		Print_String_Of_Safety(List);
	}
};
v<int> Avail = { 1,5,2,0}; 
v<v<int>> Allocation = { { 0, 0,1, 2 },
						{ 1,0, 0,0 },
						{ 1,3, 5, 4 },
						{ 0, 6, 3,2 },
						{ 0, 0, 1,4 } };
v<v<int>> Max =
{ { 0, 0,1, 2 },
						{ 1,7, 5,0 },
						{ 2,3, 5, 6 },
						{ 0, 6, 5,2 },
						{ 0, 6, 5,6 }
};
v<v<int>> Request;
v<v<int>> Need;

int main()
{
	Banker m = Banker(5, 4,Avail,Allocation,Max,Request,Need);
	m.AddRequest();
	pause;
	return 0;
}
