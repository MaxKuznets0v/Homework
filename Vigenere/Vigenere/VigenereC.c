#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char *str;
char *code;

void BuildUp(char A[], char B[])
{
	int mod = strlen(A);
	for (int i = 0; i < strlen(B); i++)
		code[i] = code[i % mod];
	code[strlen(B)] = '\0';
}


int Menu()
{
	int choose;
	while (1)
	{
		char str1[] = "----------Ãëàâíîå ìåíþ----------\n";
		char str2[] = "|      Âûáåðèòå ïóíêò 1-3      |\n";
		char str3[] = "|     1. Çàøèôðîâàòü ñòðîêó    |\n|     2. Äåøèôðîâàòü ñòðîêó    |\n|     3. Âûõîä                 |\n";
		char str4[] = "--------------------------------\n";
		printf("%s%s%s%s", str1, str2, str3, str4);
		scanf_s("%d", &choose);
		if (choose == 1 || choose == 2 || choose == 3)
			break;
		else
			printf("Ââåäèòå 1-3\n\n");
	}

	return choose;
}


void Start()
{
	int strNum;
	char Str1[] = "\nÂâåäèòå ìàêñèìàëüíîå êîëè÷åñòâî ñèìâîëîâ: ";
	char Str2[] = "Ââåäèòå âàøó ñòðîêó: ";
	char Str3[] = "Ââåäèòå êîäîâîå ñëîâî: ";
	printf("%s", Str1);
	scanf_s("%d", &strNum);
	getchar();
	printf("%s\n", Str2);
	str = (char *)malloc(strNum * sizeof(char));
	gets_s(str, strNum);
	code = (char *)malloc(strNum * sizeof(char));
	puts(Str3);
	gets_s(code, strNum);
	BuildUp(code, str);
}


void Cypher(char A[], char B[])
{
	int c, M = 67;
	char alp[] = "àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß";

	for (int i = 0; i < strlen(A); i++)
	{
		char tempCur = A[i];
		char tempCode = B[i];

		for (c = 0; c < strlen(alp); c++)
		{
			if (alp[c] == tempCode)
				break;
		}

		for (int j = 0; j < strlen(alp); j++)
		{
			if (alp[j] == tempCur)
			{
				A[i] = alp[(j + c + 1) % M];
				break;
			}
		}
	}
	printf("\nÇàøèôðîâàííàÿ ñòðîêà: %s\n\n", str);
}


void Decypher(char A[], char B[])
{
	int c, M = 67;
	char alp[] = "àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß";

	for (int i = 0; i < strlen(A); i++)
	{
		char tempCur = A[i];
		char tempCode = B[i];

		for (c = 0; c < strlen(alp); c++)
		{
			if (alp[c] == tempCode)
				break;
		}

		for (int j = 0; j < strlen(alp); j++)
		{
			if (alp[j] == tempCur)
			{
				int s = j - c - 1;
				if (s < 0)
					s += M;
				A[i] = alp[s % M];
				break;
			}
		}
	}
	printf("\nÈñõîäíàÿ ñòðîêà: %s\n\n", str);
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (1)
	{
		switch (Menu())
		{
		case 1:
			Start();
			Cypher(str, code);
			break;
		case 2:
			Start();
			Decypher(str, code);
			break;
		case 3:
			free(str);
			free(code);
			return 0;
		}
	}
}