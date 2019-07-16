#include <iostream>
#include <Windows.h>
#include <string>
#include <cstdlib>
using namespace std;

class Student  // класс с данными о каждом студенте
{
	char fname[100]; // имя
	char sname[100]; // фамилия
	char tname[100]; // отчество
	char phone[100]; // мобильный телефон
	char stNum[100]; // личный номер st
	char sex[100]; // пол студента
public:
	char* GetNum()  // получение номера студента
	{
		return stNum;
	}
	char* GetName()  // Возвращает ФИО как одну строку
	{
		char line[100];
		strcpy_s(line, sname);
		strcat_s(line, " ");
		strcat_s(line, fname);
		strcat_s(line, " ");
		strcat_s(line, tname);
		return line;
	}
	friend ostream &operator << (ostream &stream, Student &ob); // вывод данных о студенте
	friend istream &operator >> (istream &stream, Student &ob); // получение данных о студенте
};  

ostream &operator << (ostream &stream, Student &z) // перегрузка оператора вывода класса Student
{
	stream << "\n-----------------------------------";
	stream << "\nПолное имя студента: " << z.sname << " " << z.fname << " " << z.tname << endl;
	stream << "Пол: " << z.sex << endl;
	stream << "Мобильный телефон: " << z.phone << endl;
	stream << "Личный номер студента: st" << z.stNum << endl;
	stream << "-----------------------------------\n";
	return stream;
}

istream &operator >> (istream &stream, Student &z) // перегрузка оператора ввода класса Student
{
	cout << "\nВведите ФИО студента через пробел: ";
	stream >> z.sname >> z.fname >> z.tname;
	stream.clear(); // используется для очистки потока от воозможных лишних данных
	while (stream.get() != '\n');
	cout << "Пол: ";
	stream >> z.sex;
	stream.clear();
	while (cin.get() != '\n');
	cout << "Мобильный телефон: ";
	stream >> z.phone;
	stream.clear();
	while (cin.get() != '\n');
	cout << "Личный номер студента:(без st) ";
	stream >> z.stNum;
	return stream;
}

class Data // главное меню, поиск по номеру, по ФИО, заполнение БД
{
	int n, n1, ans; // количество студентов, количество добавляемых студентов и ответ для меню
	char user[100]; // запрос пользователя
	bool checking; // отвечает за повторения цикла поиска
	Student *spbu; // массив объектов (все студенты базы данных)
public:
	void ShowMenu() // вывод меню
	{
		do
		{
			cout << "\n---------------Меню----------------\n"
				 << "1. Поиск студента по его st номеру\n"
				 << "2. Поиск студента по ФИО\n"
				 << "3. Добавить новых студентов\n"
				 << "4. Выход \n\n";
			cout << "Введите число 1-4: ";
			cin >> ans; // Получает введенное пользователем число
			cin.clear();
			while (cin.get() != '\n');
			if ((ans == 1) || (ans == 2) || (ans == 3) || (ans == 4))
				break;
			else
			{
				cout << endl << "Введите число от 1 до 4!" << endl;
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

	void GetBase()   // получаем базу данных
	{
		cout << "Введите количество студентов: ";
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
						cout << "Студент с таким номером уже задан! Используйте другие данные!" << endl;
						checking = true;
						break;
					}
				}
			} while (checking);
		}
		ShowMenu();
		delete[] spbu;
	}

	void CheckBySt()  // Поиск по номеру студента
	{
		bool checking = true;
		while (checking)
		{
			cout << "Номер искомого студента (без st): ";
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
				cout << "Студента с таким номером не существует! Попробуйте еще раз (Нажмите \"0\" для выхода в главное меню)" << endl;
		}
		ShowMenu();
	}

	void CheckByName()  // поиск по ФИО студента, при обнаружении нескольких ищется по номеру
	{
		char user1[100], user2[100], user3[100];
		bool checking = true;
		while (checking)
		{
			cout << "ФИО искомого студента через пробел: ";
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
			int temp = 0; // количество студентов с одинаковым именем
			int pool; // индекс студента в массиве (нужен если нашелся только 1 студент)
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
				cout << "По вашему запросу найдено " << temp << " человек, пожалуйста, уточните st номер студента" << endl;
				CheckBySt();
				checking = false;
				break;
			}
			else if (checking)
				cout << "Студента с таким именем не существует! Попробуйте еще раз! (Нажмите \"0\" для выхода в главное меню)" << endl;
		}
		if (checking)
			ShowMenu();
	}

	void AddNew()  // добавление новых ячеек в БД
	{
		cout << "Введите количество ячеек, которое хотите добавить (Введите \"0\" для возвращения в главное меню) : ";
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
						cout << "Студент с таким номером уже задан! Используйте другие данные!" << endl;
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
	SetConsoleCP(1251); // локализация
	SetConsoleOutputCP(1251);
	Data mainAction;
	mainAction.GetBase();
	system("pause");
	return 0;
}