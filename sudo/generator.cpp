

#include"generator.h"
static char buf[MAX];


void sudoku_generate(int n)
{
	int cot = n;
	buf[0] = '\0';
	int bit = 0;
	//char str[30];
	char line[9] = { '5','1','2','3','4','6','7','8','9' };
	char line1[19] = { '5',' ','1', ' ' ,'2', ' ','3',' ','4', ' ','6',' ','7',' ','8',' ','9','\n','\0' };
	int shift[9] = { 0,6,12,2,8,14,4,10,16 };

	int pos1[6][3] = { { 3,4,5 },{ 3,5,4 },{ 4,5,3 },{ 4,3,5 },{ 5,4,3 },{ 5,3,4 } };
	int pos2[6][3] = { { 6,7,8 },{ 6,8,7 },{ 7,6,8 },{ 7,8,6 },{ 8,6,7 },{ 8,7,6 } };


	char final[10][19];
	int i, j, k;
	int flag = 0;
	char str[200];

	for (int i = 0; i < 9; i++)//��ʼֵ�ÿո��\0
	{
		for (int j = 0; j < 17; j++)
		{
			final[i][j] = ' ';
		}
		final[i][17] = '\n';
		final[i][18] = '\0';
	}
	final[9][0] = '\n';//��10��ֻ��һ������
	final[9][1] = '\0';


	//freopen(SUDOKUPATH, "w", stdout);
	FILE* fp = fopen(SUDOKUPATH, "w");

	do//���ɵ�һ��
	{
		for (int i = 0; i < 9; i++)
		{
			line1[2 * i] = line[i];
		}
		memcpy(final[0], line1, sizeof(line1));
		for (i = 1; i < 9; i++)//�Ե�һ��Ϊ����������һ���վ�
		{
			for (j = 0; j < 18; j += 2)
			{
				final[i][j] = line1[(j + shift[i]) % 18];
			}
		}

		//��һ���վֵĻ����ϸı�4-6,7-9�е����˳�򼴿�
		for (i = 0; i < 6; i++)
		{
			for (j = 0; j < 6; j++)
			{
				str[0] = '\0';
				flag++;
				for (k = 0; k < 3; k++)//ǰ����
				{
					//fputs(final[k], fp);
					//strcat(str, final[k]);
					strcpy(buf + bit, final[k]);
					bit += 18;

				}

				for (k = 0; k < 3; k++)//3 4 5��
				{
					//fputs(final[pos1[i][k]], fp);
					//strcat(str, final[pos1[i][k]]);
					strcpy(buf + bit, final[pos1[i][k]]);
					bit += 18;
				}
				//if (n > 1)
				//{
				for (k = 0; k < 3; k++)//6 7 8��
				{
					//fputs(final[pos2[j][k]], fp);
					//strcat(str, final[pos2[j][k]]);
					strcpy(buf + bit, final[pos2[j][k]]);
					bit += 18;
				}
				//fputs(final[9], fp);//����س�
				//strcat(str, final[9]);
				strcpy(buf + bit, "\n");
				bit++;

				//if (n == 1)str[161] = '\0';
				//fputs(str, fp);

				if (n == 1)
				{
					buf[163 * (cot - 1) + 161] = '\0';
					fputs(buf, fp);
				}

				n--;
				if (!n) { fclose(fp); return; }
			}
		}

	} while (next_permutation(line + 1, line + 9));
}
void ques_generate1(int ques_num)
{

	FILE* fpQues1;
	FILE* fpBase1;
	char str[200];

	fpBase1 = fopen(SUDOKUPATH, "r");
	fpQues1 = fopen(QUESPATH, "w");
	ques_board[9][0] = '\n';
	ques_board[9][1] = '\0';
	while (ques_num--)
	{
		str[0] = '\0';
		for (int i = 0; i < 9; i++)
		{
			fgets(ques_board[i], 20, fpBase1);
		}fgetc(fpBase1);

		//int base[9] = { 0,3,6,27,30,33,54,57,60 };
		int base[9] = { 0,6,12,54,60,66,108,114,120 };
		//int plus[9] = { 0,1,2,9,10,11,18,19,20 };
		int plus[9] = { 0,2,4,18,20,22,36,38,40 };

		for (int k = 0; k < 9; k++)//ÿ��3*3����Ϳ�2��
		{

			int i, j,
				hole[2];//3*3�����͵�λ��
			hole[0] = rand() % 9;
			//hole[1] *= 2;
			hole[1] = rand() % 9;
			//hole[2] *= 2;
			while (hole[0] == hole[1])//��ֹ�ظ�
			{
				hole[1] = rand() % 9;
			}
			for (int t = 0; t < 2; t++)
			{
				int dot;
				dot = base[k] + plus[hole[t]];
				i = dot / 18;
				j = dot % 18;
				ques_board[i][j] = '0';
			}
		}

		//�Ѿ��Ϳ���18��
		int others;
		others = 12 + rand() % 31;//����12-41���Ϳ�����
		while (others--)
		{
			int k = rand() % 81;
			int i = k / 9;
			int j = k % 9;

			j *= 2;
			if (ques_board[i][j] != '0')ques_board[i][j] = '0';
			else others++;
		}

		//freopen(QUESPATH, "w", stdout);
		for (int i = 0; i < 10; i++)
		{
			strcat(str, ques_board[i]);
		}if (!ques_num) str[161] = '\0';
		fputs(str, fpQues1);
	}
	fclose(fpBase1);
	fclose(fpQues1);
}
void ques_generate2(int ques_num, int diff)
{

	FILE* fpQues1;
	FILE* fpBase1;
	char str[200];

	fpBase1 = fopen(SUDOKUPATH, "r");
	fpQues1 = fopen(QUESPATH, "w");
	ques_board[9][0] = '\n';
	ques_board[9][1] = '\0';
	while (ques_num--)
	{
		str[0] = '\0';
		for (int i = 0; i < 9; i++)
		{
			fgets(ques_board[i], 20, fpBase1);
		}fgetc(fpBase1);

		//int base[9] = { 0,3,6,27,30,33,54,57,60 };
		int base[9] = { 0,6,12,54,60,66,108,114,120 };
		//int plus[9] = { 0,1,2,9,10,11,18,19,20 };
		int plus[9] = { 0,2,4,18,20,22,36,38,40 };

		for (int k = 0; k < 9; k++)//ÿ��3*3����Ϳ�2��
		{

			int i, j,
				hole[2];//3*3�����͵�λ��
			hole[0] = rand() % 9;
			//hole[1] *= 2;
			hole[1] = rand() % 9;
			//hole[2] *= 2;
			while (hole[0] == hole[1])//��ֹ�ظ�
			{
				hole[1] = rand() % 9;
			}
			for (int t = 0; t < 2; t++)
			{
				int dot;
				dot = base[k] + plus[hole[t]];
				i = dot / 18;
				j = dot % 18;
				ques_board[i][j] = '0';
			}
		}

		//�Ѿ��Ϳ���18��
		int others = 0;//2-42 
		//2-22
		if (diff == 1) {
			others = 2 + rand() % 21;
		}
		//23-37
		if (diff == 2)
			others = 23 + rand() % 15;
		//38-42
		if (diff == 3)
			others = 38 + rand() % 5;
		while (others--)
		{
			int k = rand() % 81;
			int i = k / 9;
			int j = k % 9;

			j *= 2;
			if (ques_board[i][j] != '0')ques_board[i][j] = '0';
			else others++;
		}

		//freopen(QUESPATH, "w", stdout);
		for (int i = 0; i < 10; i++)
		{
			strcat(str, ques_board[i]);
		}if (!ques_num) str[161] = '\0';
		fputs(str, fpQues1);
	}
	fclose(fpBase1);
	fclose(fpQues1);
}
void ques_generate3(int ques_num, int space_num1, int space_num2)
{

	FILE* fpQues1;
	FILE* fpBase1;
	char str[200];

	fpBase1 = fopen(SUDOKUPATH, "r");
	fpQues1 = fopen(QUESPATH, "w");
	ques_board[9][0] = '\n';
	ques_board[9][1] = '\0';
	while (ques_num--)
	{
		str[0] = '\0';
		for (int i = 0; i < 9; i++)
		{
			fgets(ques_board[i], 20, fpBase1);
		}fgetc(fpBase1);

		//int base[9] = { 0,3,6,27,30,33,54,57,60 };
		int base[9] = { 0,6,12,54,60,66,108,114,120 };
		//int plus[9] = { 0,1,2,9,10,11,18,19,20 };
		int plus[9] = { 0,2,4,18,20,22,36,38,40 };

		for (int k = 0; k < 9; k++)//ÿ��3*3����Ϳ�2��
		{

			int i, j,
				hole[2];//3*3�����͵�λ��
			hole[0] = rand() % 9;
			//hole[1] *= 2;
			hole[1] = rand() % 9;
			//hole[2] *= 2;
			while (hole[0] == hole[1])//��ֹ�ظ�
			{
				hole[1] = rand() % 9;
			}
			for (int t = 0; t < 2; t++)
			{
				int dot;
				dot = base[k] + plus[hole[t]];
				i = dot / 18;
				j = dot % 18;
				ques_board[i][j] = '0';
			}
		}

		//�Ѿ��Ϳ���18��
		int others;
		others = space_num1 - 18 + rand() % (space_num2 - space_num1 + 1);
		while (others--)
		{
			int k = rand() % 81;
			int i = k / 9;
			int j = k % 9;

			j *= 2;
			if (ques_board[i][j] != '0')ques_board[i][j] = '0';
			else others++;
		}

		//freopen(QUESPATH, "w", stdout);
		for (int i = 0; i < 10; i++)
		{
			strcat(str, ques_board[i]);
		}if (!ques_num) str[161] = '\0';
		fputs(str, fpQues1);
	}
	fclose(fpBase1);
	fclose(fpQues1);
}
// ����Ψһ��
void ques_generate4(int ques_num)
{

	FILE* fpQues1;
	FILE* fpBase1;
	char str[200];

	fpBase1 = fopen(SUDOKUPATH, "r");
	fpQues1 = fopen(QUESPATH, "w");
	ques_board[9][0] = '\n';
	ques_board[9][1] = '\0';
	//while (ques_num--)
	while (ques_num)
	{
		str[0] = '\0';
		for (int i = 0; i < 9; i++)
		{
			fgets(ques_board[i], 20, fpBase1);
		}fgetc(fpBase1);

		//int base[9] = { 0,3,6,27,30,33,54,57,60 };
		int base[9] = { 0,6,12,54,60,66,108,114,120 };
		//int plus[9] = { 0,1,2,9,10,11,18,19,20 };
		int plus[9] = { 0,2,4,18,20,22,36,38,40 };

		for (int k = 0; k < 9; k++)//ÿ��3*3����Ϳ�2��
		{

			int i, j,
				hole[2];//3*3�����͵�λ��
			hole[0] = rand() % 9;
			//hole[1] *= 2;
			hole[1] = rand() % 9;
			//hole[2] *= 2;
			while (hole[0] == hole[1])//��ֹ�ظ�
			{
				hole[1] = rand() % 9;
			}
			for (int t = 0; t < 2; t++)
			{
				int dot;
				dot = base[k] + plus[hole[t]];
				i = dot / 18;
				j = dot % 18;
				ques_board[i][j] = '0';
			}
		}

		//�Ѿ��Ϳ���18��
		int others;
		others = 2 + rand() % 11;//����12-41���Ϳ�����
		while (others--)
		{
			int k = rand() % 81;
			int i = k / 9;
			int j = k % 9;

			j *= 2;
			if (ques_board[i][j] != '0')ques_board[i][j] = '0';
			else others++;
		}

		int temp[9][9];
		for (int i = 0;i < 9;i++) {
			for (int j = 0;j < 9;j++) {
				temp[i][j] = ques_board[i][2 * j];
				//cout << ques_board[i][2 * j];
			}
		}
		if (checkUniqueness(temp)) {
			// ֻ��Ψһ����������Լ��
			ques_num--;
			//freopen(QUESPATH, "w", stdout);
			for (int i = 0; i < 10; i++)
			{
				strcat(str, ques_board[i]);
			}if (!ques_num) str[161] = '\0';
			fputs(str, fpQues1);
		}
		else
			continue;
	}
	fclose(fpBase1);
	fclose(fpQues1);
}
// �����Ψһ��
bool checkUniqueness(int puzzle[UN][UN]) {
	//get the number of missing spots
	int missing = 0;

	for (int i = 0; i < UN; i++) {

		for (int j = 0; j < UN; j++) {

			if (puzzle[i][j] == 0) {
				missing++;
			}
		}
	}


	//get the rows and cols for each missing one
	int* row = new int[missing]; // ex. row[1], col[1] corresponds with one 0 point
	int* col = new int[missing];

	int counter = 0;

	for (int i = 0; i < UN; i++) {

		for (int j = 0; j < UN; j++) {

			if (puzzle[i][j] == 0) {
				row[counter] = i;
				col[counter] = j;
				counter++;
			}
		}
	}

	if (missing == 1 || missing == 0) {  // acounts for corner cases
		return true;
	}

	// get a completely solved puzzle as an example
	int solved[UN][UN];

	copy_grid(solved, puzzle);
	if (!solveSudoku(solved)) {  // if can't be solved, no solution so return false
		return false;
	}

	//search for another solution
	for (int i = 0; i < missing; i++) { // for each missing spot

		for (int j = 0; j < UN; j++) { // try each potential number

			if (j != solved[row[i]][col[i]]) { //skip over the number in solution

				int test[UN][UN];

				copy_grid(test, puzzle);

				//try solving with new number
				if (isValidInsert(test, row[i], col[i], j)) {

					test[row[i]][col[i]] = j;

					if (solveSudoku(test)) { //if it can be solved, return false
						return false;
					}
				}
			}
		}
	}
	return true;
}
// �����Ƶ�ǰ
void copy_grid(int puzzleCopy[UN][UN], int puzzle[UN][UN]) {

	for (int row = 0; row < UN; row++) {
		for (int column = 0; column < UN; column++)
			puzzleCopy[row][column] = puzzle[row][column];
	}
}
// �ж��Ƿ��н�
bool solveSudoku(int grid[UN][UN]) {
	int row, col;

	// if no empty space is found, we solved it
	if (!findEmptySpace(grid, &row, &col)) {
		return true;
	}

	// attempt to insert numbers 1 - 9
	for (int i = 1; i <= UN; i++) {

		// check if inserting tht number is allowed
		if (isValidInsert(grid, row, col, i)) {

			grid[row][col] = i;   // if allowed, insert it

			// if that number leads to a solution, great, stop.
			if (solveSudoku(grid)) {
				return true;
			}

			// if it doesn't, replace that number with a 0 and try the next number
			grid[row][col] = 0;
		}
	}
	// if it gets here, there is no solution
	return false;
}
// �ҵ���Ҫ���λ��
bool findEmptySpace(int grid[UN][UN], int* row, int* col) {

	for (int i = 0; i < UN; i++) {

		for (int j = 0; j < UN; j++) {

			// if it is zero, it is an empty space
			if (grid[i][j] == 0) {

				// save the row and column of the empty space
				*row = i; *col = j;
				return true;
			}
		}
	}
	return false;
}
// �����������Ƿ�Ϸ�
bool isValidInsert(int grid[UN][UN], int row, int col, int num) {

	// check if the number exists elsewhere in the same row
	for (int i = 0; i < UN; i++) {
		if (i != col && grid[row][i] == num) {
			return false;
		}
	}

	// check if the number exists elsewhere in the same column
	for (int i = 0; i < UN; i++) {
		if (i != row && grid[i][col] == num) {
			return false;
		}
	}

	// check if the number exists elsewhere in the 3 x 3 grid

	int startRow = row - (row % 3);  // starting row of the 3 x 3 grid
	int startCol = col - (col % 3);  // starting column of the 3 x 3 grid

	for (int i = startRow; i < startRow + 3; i++) {
		for (int j = startCol; j < startCol + 3; j++) {
			if (i != row && j != col && grid[i][j] == num) {
				return false;
			}
		}
	}

	return true;

}