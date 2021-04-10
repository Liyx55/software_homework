#pragma once
#ifndef GENERATORH
#define GENERATORH

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<time.h>
using namespace std;

#define SUDOKUPATH  "sudoku.txt"//读，c的时候生成
#define QUESPATH "ques.txt"
#define SOLUTIONPATH "solution.txt"
#define BASEPATH "sudokubase.txt"
#define GENERATEPATH "generation.txt" 
#define MAX 200000000
static char AbsolutePath[100] = { 0 };
static char ques_board[10][20];


extern void sudoku_generate(int n);
extern void ques_generate1(int ques_num);
extern void ques_generate2(int ques_num, int diff);
extern void ques_generate3(int ques_num, int space_num1, int space_num2);
#endif // !GENERATORH


