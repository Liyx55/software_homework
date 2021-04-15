/*
** (C) Copyright 2020 Zty. LTD.(WuHan) All Rights Reserved.
** Description：Shu
** Author：Lyx,Sjy
** Date: 
** Modify Record:
*/
#pragma once
#ifndef SHUDU
#define SHUDU

#include "inputcontrol.h"
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <time.h>

using namespace std;

#define SUDOKUPATH  "sudoku.txt"
#define QUESPATH "ques.txt"
#define SOLUTIONPATH "solution.txt"
#define BASEPATH "sudokubase.txt"
#define GENERATEPATH "generation.txt" 
#define MAX 200000000
#define UN 9

static char AbsolutePath[100] = { 0 };
static char ques_board[10][20];

extern bool sudoku_generate(int n);
extern void ques_generate1(int ques_num);
extern void ques_generate2(int ques_num, int diff);
extern void ques_generate3(int ques_num, int space_num1, int space_num2);
extern void ques_generate4(int ques_num);
extern bool checkUniqueness(int puzzle[UN][UN]);
extern void copy_grid(int puzzleCopy[UN][UN], int puzzle[UN][UN]);
extern bool solveSudoku(int grid[UN][UN]);
extern bool findEmptySpace(int grid[UN][UN], int* row, int* col);
extern bool isValidInsert(int grid[UN][UN], int row, int col, int num);
#endif  // !GENERATORH
