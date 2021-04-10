////�ո�������
////3.3-4s
////fputs ������װ����һ�������ַ���

#include"generator.h"
#include<iostream>
using namespace std;
static int num = 0;
static int settle_flag = 0;


int check(int m, int n)
{
	int i, j, k;
	i = m;
	j = n;
	for (k = 0; k < 18; k += 2)
	{
		if (k != j)//�ж����Ƿ�����
		{
			if (ques_board[i][j] == ques_board[i][k])return 0;
		}
		if (k != i)//�ж����Ƿ�����
		{
			if (ques_board[i][j] == ques_board[k][j])return 0;
		}
	}
	if (m / 3 == 0)i = 0;
	else if (m / 3 == 1)i = 3;
	else i = 6;

	if (n / 6 == 0)j = 0;
	else if (n / 6 == 1)j = 6;
	else j = 12;

	//�ж�9��3*3�Ƿ�����
	for (int c = i; c < i + 3; c++)
		for (int d = j; d < j + 6; d += 2)
		{
			if (c != m && d != n && ques_board[m][n] == ques_board[c][d])return 0;
		}
	return 1;
}

void prune(int i, int j, bool point[10])
{
	for (int k = 0; k < 18; k += 2)//���ų�
	{
		if (ques_board[i][k] != '0' && k != j)point[ques_board[i][k] - '0'] = true;
	}
	for (int k = 0; k < 9; k++)//���ų�
	{
		if (ques_board[k][j] != '0' && k != i)point[ques_board[k][j] - '0'] = true;
	}
	int m = 0, n = 0;
	if (i / 3 == 0)m = 0;
	else if (i / 3 == 1)m = 3;
	else if (i / 3 == 2)m = 6;

	if (j / 6 == 0)n = 0;
	else if (j / 6 == 1)n = 6;
	else if (j / 6 == 2)n = 12;

	for (int c = m; c < m + 3; c++)
	{
		for (int d = n; d < n + 6; d += 2)
		{
			if (c != i && d != j && ques_board[c][d] != '0')point[ques_board[c][d] - '0'] = true;
		}
	}
}


void settle(int pos)
{
	if (pos == 162)
	{
		settle_flag = 1;
		return;
	}
	int i, j, k;
	i = pos / 18;
	j = pos % 18;

	bool point[10] = { false };

	if (ques_board[i][j] == '0')
	{
		prune(i, j, point);

		for (k = 1; k <= 9; k++)
		{
			if (point[k])continue;
			ques_board[i][j] = k + '0';
			//if (check(i, j))
			{
				settle(pos + 2);
			}
			if (settle_flag) { return; }
			ques_board[i][j] = '0';//??
		}
	}
	else
	{
		settle(pos + 2);
	}

	if (settle_flag) { return; }
}


int total = 0;
void settle_ques()
{

	int begin = 0, end = 0;
	FILE* fpQues, * fpSolution;
	char strSolution[200];
	int n = 0;
	//if(argv[2]==NULL)
	if (AbsolutePath[0] == 0)
		fpQues = fopen(QUESPATH, "r");
	else
		fpQues = fopen(AbsolutePath, "r");

	fpSolution = fopen(SUDOKUPATH, "w");
	int flag = 0;
	while (1)
	{
		n = 0;
		flag = 0;
		for (int i = 0; i < 9; i++)
		{
			fgets(ques_board[i], 20, fpQues);

		}
		flag = fgetc(fpQues);//��ȡ�м�Ŀ��У��ж��Ƿ��ļ�β

		begin = clock();
		settle_flag = 0;
		settle(0);
		end = clock();
		total += end - begin;
		//freopen(SOLUTIONPATH, "w", stdout);
		strSolution[0] = '\0';
		for (int i = 0; i < 9; i++)
		{
			strcat(strSolution, ques_board[i]);
		}
		if (flag == -1)strSolution[161] = '\0';
		else
		{
			strSolution[161] = '\n';
			strSolution[162] = '\n';
			strSolution[163] = '\0';
		}
		fputs(strSolution, fpSolution);
		if (flag == -1) break;
	}
	fclose(fpQues);
	fclose(fpSolution);
}

int main(int argc, char** argv)
{
	if (argc == 3) {
		if (strcmp(argv[1], "-c") && strcmp(argv[1], "-s") && strcmp(argv[1], "-n"))
		{
			cout << "Illegal paramater\n"
				<< "The first parameter should be -c or -s or -n\n"
				<< "-c means generating sudoku\n"
				<< "-s meas solve the problem read from the file\n"
				<< "-n means the number of sudo game\n";
			return 1;
		}

		if (!strcmp(argv[1], "-c"))//judge the second parameter when -c
		{
			int len = strlen(argv[2]);
			for (int i = 0; i < len; i++)
			{
				if (argv[2][i] > '9' || argv[2][i] < '0')
				{
					cout << "Illegal paramater\n";
					cout << "The second parameter should be a positive integer\n";
					return 1;
				}
			}

			int number = 0;
			for (int i = 0; i < len; i++)
			{
				number = number * 10 + argv[2][i] - '0';
			}

			sudoku_generate(number);
			cout << "The sudoku final generated is in the sudoku.txt\n"
				<< "Have a check\n";
			return 0;
		}

		if (!strcmp(argv[1], "-s"))
		{
			strcpy(AbsolutePath, argv[2]);
			settle_ques();

			cout << "The answer you need is in the sudoku.txt\n"
				<< "Have a check\n";
			return 0;
		}

		if (!strcmp(argv[1], "-n"))//default path ques.txt
		{
			int len = strlen(argv[2]);
			for (int i = 0; i < len; i++)
			{
				if (argv[2][i] > '9' || argv[2][i] < '0')
				{
					cout << "Illegal paramater\n";
					cout << "The second parameter should be a positive integer\n";
					return 1;
				}
			}

			int number = 0;
			for (int i = 0; i < len; i++)
			{
				number = number * 10 + argv[2][i] - '0';
			}

			ques_generate(number);
			cout << "The sudoku question generated is in the ques.txt\n"
				<< "Have a check\n";
			return 0;
		}
	}

	if (argc == 4) {
		if (strcmp(argv[1], "-n") && strcmp(argv[3], "-u"))
		{
			cout << "Illegal paramater\n"
				<< "The first parameter should be -n and the third parameter should be -u\n";
			return 1;
		}

		if (!strcmp(argv[1], "-n"))//default path ques.txt
		{
			//���ܻ�δʵ�� -u
			int len = strlen(argv[2]);
			for (int i = 0; i < len; i++)
			{
				if (argv[2][i] > '9' || argv[2][i] < '0')
				{
					cout << "Illegal paramater\n";
					cout << "The second parameter should be a positive integer\n";
					return 1;
				}
			}

			int number = 0;
			for (int i = 0; i < len; i++)
			{
				number = number * 10 + argv[2][i] - '0';
			}

			ques_generate(number);
			cout << "The sudoku question generated is in the ques.txt\n"
				<< "Have a check\n";
			return 0;
		}

	}

	if (argc == 5) {
		if (strcmp(argv[1], "-n") && (strcmp(argv[3], "-m")|| strcmp(argv[3], "-r")))
		{
			cout << "Illegal paramater\n"
				<< "The first parameter should be -n and the third parameter should be -r or -m\n";
			return 1;
		}

		if (!strcmp(argv[1], "-n"))//default path ques.txt
		{
			//���ܻ�δʵ�� -m -r
			int len = strlen(argv[2]);
			for (int i = 0; i < len; i++)
			{
				if (argv[2][i] > '9' || argv[2][i] < '0')
				{
					cout << "Illegal paramater\n";
					cout << "The second parameter should be a positive integer\n";
					return 1;
				}
			}

			int number = 0;
			for (int i = 0; i < len; i++)
			{
				number = number * 10 + argv[2][i] - '0';
			}

			ques_generate(number);
			cout << "The sudoku question generated is in the ques.txt\n"
				<< "Have a check\n";
			return 0;
		}
	}
	system("pause");
	return 0;
}
