#include "pch.h"
#include "CppUnitTest.h"
#include "../shudu/shudu.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest_lyx)
	{
	public:
		
		int argc1, argc2, argc3;
		char** argv1, ** argv2, ** argv3, ** argv4, ** argv5, ** argv6;
		UnitTest_lyx()
		{
			argc1 = 3;
			argc2 = 4;
			argc3 = 5;
			argv1 = new char* [3];//c
			argv2 = new char* [3];//s
			argv3 = new char* [3];//n
			argv4 = new char* [4];//n u
			argv5 = new char* [5];//n m
			argv6 = new char* [5];//n r


			for (int i = 0; i < 3; i++)
			{
				argv1[i] = new char[30];
				argv2[i] = new char[30];
				argv3[i] = new char[30];

			}

			for (int i = 0; i < 4; i++)
			{
				argv4[i] = new char[30];

			}
			for (int i = 0; i < 5; i++)
			{
				argv5[i] = new char[30];
				argv6[i] = new char[30];
			}
			strcpy_s(argv1[0], 30, "shuduku.exe");
			strcpy_s(argv1[1], 30, "-c");
			strcpy_s(argv1[2], 30, "100");

			strcpy_s(argv2[0], 30, "shuduku.exe");
			strcpy_s(argv2[1], 30, "-s");
			strcpy_s(argv2[2], 30, "ques.txt");

			strcpy_s(argv3[0], 30, "shuduku.exe");
			strcpy_s(argv3[1], 30, "-n");
			strcpy_s(argv3[2], 30, "100");

			strcpy_s(argv4[0], 30, "shuduku.exe");
			strcpy_s(argv4[1], 30, "-n");
			strcpy_s(argv4[2], 30, "10");
			strcpy_s(argv4[3], 30, "-u");

			strcpy_s(argv5[0], 30, "shuduku.exe");
			strcpy_s(argv5[1], 30, "-n");
			strcpy_s(argv5[2], 30, "100");
			strcpy_s(argv5[3], 30, "-m");
			strcpy_s(argv5[4], 30, "3");

			strcpy_s(argv6[0], 30, "shuduku.exe");
			strcpy_s(argv6[1], 30, "-n");
			strcpy_s(argv6[2], 30, "100");
			strcpy_s(argv6[3], 30, "-r");
			strcpy_s(argv6[4], 30, "20-30");
		}

		//测试函数ParameterProcess(),参数为-c时
		TEST_METHOD(TestMethod1)
		{
			Input inputs(argc1, argv1);
			inputs.ParameterProcess();
			Assert::AreEqual(inputs.GetNum() == 100, true);
			Assert::AreEqual(inputs.GetType1() == 'c', true);
		}

		//测试函数ParameterProcess(), 参数为 - s时
		TEST_METHOD(TestMethod2)
		{
			
			Input inputs(argc1, argv2);
			inputs.ParameterProcess();
			//bool abc = ques_generate1(100);
			Assert::AreEqual(inputs.GetType1() == 's', true);
			//Assert::AreEqual(abc, true);
		}

		//测试函数ParameterProcess(), 参数为 - s时
		TEST_METHOD(TestMethod15)
		{

			Input inputs(argc1, argv3);
			inputs.ParameterProcess();
			bool abc = ques_generate1(1);
			Assert::AreEqual(inputs.GetType1() == 'n', true);
			Assert::AreEqual(abc, true);
		}

		//测试函数ParameterProcess()，命令行参数不是2个
		TEST_METHOD(TestMethod3)
		{
			argc1 = 2;
			Input inputs(argc1, argv1);
			Assert::AreEqual(inputs.GetType1() == 'y', true);
			//'n'代表没有类别，表示没有输入正确的参数-c和-s
		}

		//测试函数ParameterProcess()，参数不是-c\-s\-n
		TEST_METHOD(TestMethod4)
		{
			argv1[1][1] = 'x';
			Input inputs(argc1, argv1);
			Assert::AreEqual(inputs.GetType1() == 'y', true);
			//'n'代表没有类别，表示没有输入正确的参数-c和-s
		}

		//测试-c时输入的数量
		TEST_METHOD(TestMethod5)
		{
			argv1[2][0] = '-';
			argv1[2][1] = '1';
			Input inputs(argc1, argv1);
			Assert::AreEqual(inputs.GetNum() == 0, true);
		}

		//测试生成数独终局
		TEST_METHOD(TestMethod6)
		{
			strcpy_s(argv1[2], 30, "1");
			Input inputs(argc1, argv1);
			inputs.ParameterProcess();
			bool a = sudoku_generate(inputs.GetNum());
			Assert::AreEqual(true, a);
		}

		//测试求解数独函数
		TEST_METHOD(TestMethod7)
		{
			Input inputs(argc1, argv2);
			inputs.ParameterProcess();
			int grid[9][9] = { {0,1,2,3,4,6,7,8,9},
				{3,4,6,7,8,9,5,1,2},
				{7,8,9,5,1,2,3,4,6},
				{1,2,3,4,6,7,8,9,5},
				{4,6,7,8,9,5,1,2,3},
				{8,9,5,1,2,3,4,6,7},
				{2,3,4,6,7,8,9,5,1},
				{6,7,8,9,5,1,2,3,4},
				{9,5,1,2,3,4,6,7,8} };
			bool AWM = checkUniqueness(grid);
			Assert::AreEqual(true, AWM);
		}

		TEST_METHOD(TestMethod8)
		{
			Input inputs(argc2, argv4);
			inputs.ParameterProcess();
			Assert::AreEqual(inputs.GetNum() == 10, true);
			Assert::AreEqual(inputs.GetType1() == 'n', true);
			Assert::AreEqual(inputs.GetType2() == 'u', true);

		}
		TEST_METHOD(TestMethod9)
		{
			Input inputs(argc3, argv5);
			inputs.ParameterProcess();
			Assert::AreEqual(inputs.GetNum() == 100, true);
			Assert::AreEqual(inputs.GetType1() == 'n', true);
			Assert::AreEqual(inputs.GetType2() == 'm', true);
			Assert::AreEqual(inputs.GetDiff() == 3, true);

		}

		TEST_METHOD(TestMethod10)
		{
			Input inputs(argc3, argv6);
			inputs.ParameterProcess();
			Assert::AreEqual(inputs.GetNum() == 100, true);
			Assert::AreEqual(inputs.GetType1() == 'n', true);
			Assert::AreEqual(inputs.GetType2() == 'r', true);
			Assert::AreEqual(inputs.GetRange1() == 20, true);
			Assert::AreEqual(inputs.GetRange2() == 30, true);
		}

		TEST_METHOD(TestMethod11)
		{
			bool abc = ques_generate3(1,20,30);
			Assert::AreEqual(abc, true);
		}
		TEST_METHOD(TestMethod12)
		{
			bool abc = ques_generate1(1);
			Assert::AreEqual(abc, true);
		}
		TEST_METHOD(TestMethod13)
		{
			bool abc = ques_generate2(1,3);
			Assert::AreEqual(abc, true);
		}
		TEST_METHOD(TestMethod14)
		{
			bool abc = ques_generate4(1);
			Assert::AreEqual(abc, true);
		}
		TEST_METHOD(TestMethod16)
		{
			bool abc = settle_ques();
			Assert::AreEqual(abc, true);
		}
		
	};
}
