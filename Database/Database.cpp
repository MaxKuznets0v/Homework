#include <iostream>
#include <Windows.h>
#include <string>
#include <cstdlib>
using namespace std;

class Student  // ����� � ������� � ������ ��������
{
	char fname[100]; // ���
	char sname[100]; // �������
	char tname[100]; // ��������
	char phone[100]; // ��������� �������
	char stNum[100]; // ������ ����� st
	char sex[100]; // ��� ��������
public:
	char* GetNum()  // ��������� ������ ��������
	{
		return stNum;
	}
	char* GetName()  // ���������� ��� ��� ���� ������
	{
		char line[100];
		strcpy_s(line, sname);
		strcat_s(line, " ");
		strcat_s(line, fname);
		strcat_s(line, " ");
		strcat_s(line, tname);
		return line;
	}
	friend ostream &operator << (ostream &stream, Student &ob); // ����� ������ � ��������
	friend istream &operator >> (istream &stream, Student &ob); // ��������� ������ � ��������
};  

ostream &operator << (ostream &stream, Student &z) // ���������� ��������� ������ ������ Student
{
	stream << "\n-----------------------------------";
	stream << "\n������ ��� ��������: " << z.sname << " " << z.fname << " " << z.tname << endl;
	stream << "���: " << z.sex << endl;
	stream << "��������� �������: " << z.phone << endl;
	stream << "������ ����� ��������: st" << z.stNum << endl;
	stream << "-----------------------------------\n";
	return stream;
}

istream &operator >> (istream &stream, Student &z) // ���������� ��������� ����� ������ Student
{
	cout << "\n������� ��� �������� ����� ������: ";
	stream >> z.sname >> z.fname >> z.tname;
	stream.clear(); // ������������ ��� ������� ������ �� ���������� ������ ������
	while (stream.get() != '\n');
	cout << "���: ";
	stream >> z.sex;
	stream.clear();
	while (cin.get() != '\n');
	cout << "��������� �������: ";
	stream >> z.phone;
	stream.clear();
	while (cin.get() != '\n');
	cout << "������ ����� ��������:(��� st) ";
	stream >> z.stNum;
	return stream;
}

class Data // ������� ����, ����� �� ������, �� ���, ���������� ��
{
	int n, n1, ans; // ���������� ���������, ���������� ����������� ��������� � ����� ��� ����
	char user[100]; // ������ ������������
	bool checking; // �������� �� ���������� ����� ������
	Student *spbu; // ������ �������� (��� �������� ���� ������)
public:
	void ShowMenu() // ����� ����
	{
		do
		{
			cout << "\n---------------����----------------\n"
				 << "1. ����� �������� �� ��� st ������\n"
				 << "2. ����� �������� �� ���\n"
				 << "3. �������� ����� ���������\n"
				 << "4. ����� \n\n";
			cout << "������� ����� 1-4: ";
			cin >> ans; // �������� ��������� ������������� �����
			cin.clear();
			while (cin.get() != '\n');
			if ((ans == 1) || (ans == 2) || (ans == 3) || (ans == 4))
				break;
			else
			{
				cout << endl << "������� ����� �� 1 �� 4!" << endl;
				continue;
			}
		} while (true);
		if (ans != 4)
		{
			switch (ans)
			{
			case 1:
				CheckBySt();
				break;
			case 2:
				CheckByName();
				break;
			case 3:
				AddNew();
				break;
			}
		}
	}

	void GetBase()   // �������� ���� ������
	{
		cout << "������� ���������� ���������: ";
		cin >> n;
		spbu = new Student[n];
		cin >> spbu[0];
		for (int i = 1; i < n; i++)
		{
			do
			{
				checking = false;
				cin >> spbu[i];
				for (int j = 0; j < i; j++)
				{
					if (strcmp(spbu[j].GetNum(), spbu[i].GetNum()) == 0)
					{
						cout << "������� � ����� ������� ��� �����! ����������� ������ ������!" << endl;
						checking = true;
						break;
					}
				}
			} while (checking);
		}
		ShowMenu();
		delete[] spbu;
	}

	void CheckBySt()  // ����� �� ������ ��������
	{
		bool checking = true;
		while (checking)
		{
			cout << "����� �������� �������� (��� st): ";
			cin >> user;
			cin.clear();
			while (cin.get() != '\n');
			if (atoi(user) == 0)
				break;
			for (int i = 0; i < n; i++)
			{
				if (atoi(spbu[i].GetNum()) == atoi(user))
				{
					cout << spbu[i];
					checking = false;
					break;
				}
			}
			if (checking)
				cout << "�������� � ����� ������� �� ����������! ���������� ��� ��� (������� \"0\" ��� ������ � ������� ����)" << endl;
		}
		ShowMenu();
	}

	void CheckByName()  // ����� �� ��� ��������, ��� ����������� ���������� ������ �� ������
	{
		char user1[100], user2[100], user3[100];
		bool checking = true;
		while (checking)
		{
			cout << "��� �������� �������� ����� ������: ";
			cin >> user1;
			if (strcmp(user1, "0") == 0)
				break;
			cin >> user2 >> user3;
			cin.clear();
			while (cin.get() != '\n');
			if (user1 != "0")
			{
				strcpy_s(user, user1);
				strcat_s(user, " ");
				strcat_s(user, user2);
				strcat_s(user, " ");
				strcat_s(user, user3);
			}
			int temp = 0; // ���������� ��������� � ���������� ������
			int pool; // ������ �������� � ������� (����� ���� ������� ������ 1 �������)
			for (int i = 0; i < n; i++)
			{
				if (strcmp(spbu[i].GetName(), user) == 0)
				{
					temp++;
					pool = i;
				}
			}
			if (temp == 1)
			{
					cout << spbu[pool];
					break;
			}
			else if (temp > 1)
			{
				cout << "�� ������ ������� ������� " << temp << " �������, ����������, �������� st ����� ��������" << endl;
				CheckBySt();
				checking = false;
				break;
			}
			else if (checking)
				cout << "�������� � ����� ������ �� ����������! ���������� ��� ���! (������� \"0\" ��� ������ � ������� ����)" << endl;
		}
		if (checking)
			ShowMenu();
	}

	void AddNew()  // ���������� ����� ����� � ��
	{
		cout << "������� ���������� �����, ������� ������ �������� (������� \"0\" ��� ����������� � ������� ����) : ";
		cin >> n1;
		cin.clear();
		while (cin.get() != '\n');
		n += n1;
		spbu = (Student*)realloc(spbu, sizeof(spbu[0]) * n);
		for (int i = n - n1; i < n; i++)
		{
			do
			{
				checking = false;
				cin >> spbu[i];
				for (int j = 0; j < i; j++)
				{
					if (strcmp(spbu[j].GetNum(), spbu[i].GetNum()) == 0)
					{
						cout << "������� � ����� ������� ��� �����! ����������� ������ ������!" << endl;
						checking = true;
						break;
					}
				}
			} while (checking);
		}
		ShowMenu();
	}
};

int main()
{
	SetConsoleCP(1251); // �����������
	SetConsoleOutputCP(1251);
	Data mainAction;
	mainAction.GetBase();
	system("pause");
	return 0;
}