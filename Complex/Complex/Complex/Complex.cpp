#include <iostream>
using namespace std;

class Complex    // ����� ���������� �����
{ 
	friend class Menu;
	double re_val; // ������������ �����
	double im_val;  // ������ �����
public:
	Complex() { re_val = 0; im_val = 0; } // ������������� �����������
	Complex(double x, double y) { re_val = x; im_val = y; }
	void Show()  // ������� ����������� �����, ��������� ���� ����� ���������
	{
		if (re_val != 0)
		{
			cout << re_val;
			if (im_val != 0)
			{
				cout << ((im_val < 0) ? " - " : " + ");
				if ((im_val != 1) && (im_val != -1))
					cout << abs(im_val) << "i";
				else
					cout << "i";
			}
		}
		else if (im_val != 0)
			if (im_val != 1)
				cout << im_val << "i";
			else
				cout << "i";
		else
			cout << 0;
			//cout << re_val << ((im_val < 0) ? " - " : " + ") << abs(im_val) << "i";
		
	}
	friend Complex operator+(Complex z1, Complex z2); // ���������� ������������� ��������, ������� ����� ������� ����� � ������ Operations
	friend Complex operator-(Complex z1, Complex z2); // � ������� ������������� �������
	friend Complex operator*(Complex z1, Complex z2);
	friend Complex operator/(Complex z1, Complex z2);
};

class Operations    // � ������ ������� ��� �������� �������� � ������������ �������
{
	friend Complex operator+(Complex z1, Complex z2)
	{
		Complex temp;
		temp.re_val = z1.re_val + z2.re_val;
		temp.im_val = z1.im_val + z2.im_val;
		return temp;
	}
	friend Complex operator-(Complex z1, Complex z2)
	{
		Complex temp;
		temp.re_val = z1.re_val - z2.re_val;
		temp.im_val = z1.im_val - z2.im_val;
		return temp;
	}
	friend Complex operator*(Complex z1, Complex z2)
	{
		Complex temp;
		temp.re_val = z2.re_val * z1.re_val - z2.im_val * z1.im_val;
		temp.im_val = z2.im_val * z1.re_val + z2.re_val * z1.im_val;
		return temp;
	}
	friend Complex operator/(Complex z1, Complex z2)
	{
		Complex temp;
		temp.re_val = (z1.re_val * z2.re_val + z1.im_val * z2.im_val) / (z2.re_val * z2.re_val + z2.im_val * z2.im_val);
		temp.im_val = (z2.re_val * z1.im_val - z2.im_val * z1.re_val) / (z2.re_val * z2.re_val + z2.im_val * z2.im_val);
		return temp;
	}
};

class Menu     // ������� ����, ����������� ���������� �����, ����� �� �����
{
	int ans = 0;
	double x, y;
	Complex z1, z2, z3;
public:
	void GetCom()  // ������ ����������� �����
	{
		
		cout << "������� ��� ����� ����� ������\n������ �����: ";
		cin >> x >> y;
		z1.re_val = x;
		z1.im_val = y;
		cout << "������ �����: ";
		cin >> x >> y;
		z2.re_val = x;
		z2.im_val = y;
		ShowMenu();
	}

	void ShowMenu() // ����� �������� ����
	{
		do
		{
			cout << endl << "                 ����" << endl;
			cout << "| 1. �������� ���� ����������� �����  |\n" <<
					"| 2. ��������� ���� ����������� ����� |\n" <<
					"| 3. ��������� ���� ����������� ����� |\n" <<
					"| 4. ������� ���� ����������� �����   |\n" <<
					"| 5. ������ ������ ���� �����         |\n" << 
					"| 6. �����                            |" << endl;
			cout << "������� ����� 1-6: ";
			cin >> ans; // �������� ��������� ������������� �����
			if ((ans == 1) || (ans == 2) || (ans == 3) || (ans == 4) || (ans == 6))
				break;
			else if (ans == 5)
			{
				GetCom();
				break;
			}

			else
			{
				cout << endl << "������� ����� �� 1 �� 6!" << endl;
				continue;
			}
		} while (true);
		if (ans != 6)
			Res();
	}

	void Res()  // � ����������� �� ���������� ����� ��������� �������� � ������� �� �� �����
	{
		cout << endl;
		switch (ans)
		{
		case 1:
			z1.Show();
			cout << " + ";
			if (z2.re_val < 0)
			{
				cout << "(";
				z2.Show();
				cout << ")";
			}
			else
				z2.Show();
			z3 = z1 + z2;
			break;
		case 2:
			z1.Show();
			cout << " - ";
			cout << "(";
			z2.Show();
			cout << ")";
			z3 = z1 - z2;
			break;
		case 3:
			cout << "(";
			z1.Show();
			cout << ")";
			cout << " * ";
			cout << "(";
			z2.Show();
			cout << ")";
			z3 = z1 * z2;
			break;
		case 4:
			cout << "(";
			z1.Show();
			cout << ")";
			cout << " / ";
			cout << "(";
			z2.Show();
			cout << ")";
			z3 = z1 / z2;
		}
		cout << " = ";
		z3.Show();
		cout << endl;
		ShowMenu();
	}
};

int main()
{
	setlocale(LC_ALL, "Rus"); // ����������� ������
	Menu menu;
	menu.GetCom();
	system("pause");
	return 0;
}