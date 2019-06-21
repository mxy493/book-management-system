// Book Management System.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include <iostream>

#include "Library.h"

using namespace std;

int main()
{
	Library library;		//图书信息库

	int func;
	do 
	{
		cout.setf(ios::left | ios::unitbuf);
		cout << endl << "=========图书管理系统=========" << endl << endl;
		cout << setw(8) << " " << setw(12) << "【1】导入数据" << endl;
		cout << setw(8) << " " << setw(12) << "【2】图书入库" << endl;
		cout << setw(8) << " " << setw(12) << "【3】所有图书" << endl;
		cout << setw(8) << " " << setw(12) << "【4】查找图书" << endl;
		cout << setw(8) << " " << setw(12) << "【5】清除库存" << endl;
		cout << setw(8) << " " << setw(12) << "【6】借阅信息" << endl;
		cout << setw(8) << " " << setw(12) << "【7】图书借阅" << endl;
		cout << setw(8) << " " << setw(12) << "【8】图书归还" << endl;
		cout << setw(8) << " " << setw(12) << "【9】存储数据" << endl;
		cout << setw(8) << " " << setw(12) << "【0】退出系统" << endl;
		cout << endl << "==============================" << endl;
		cout << endl << ">>>请选择要执行的操作:";
		cin >> func;
		switch (func)
		{
		case 1:
			library.ImportData();
			break;
		case 2:
			library.BookAdd(); 
			break;
		case 3:
			library.BookShow();
			break;
		case 4:
			library.BookFind();
			break;
		case 5:
			library.FuncEmpty();
			break;
		case 6:
			library.ReaderBooks();
			break;
		case 7:
			library.BookBorrow();
			break;
		case 8:
			library.BookReturn();
			break;
		case 9:
			library.SaveData();
			break;
		case 0:
			break;
		}
	} while (func != 0);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
