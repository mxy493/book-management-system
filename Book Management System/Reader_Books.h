#pragma once

#include <string>
using namespace std;

struct BorrowedBooks
{
	string id;		//书号
	string name;	//书名
	string author;	//作者
	int quantity;	//借阅量

	BorrowedBooks *next = nullptr;	//next指针

	BorrowedBooks(string number, string name, string author, int quantity)
	{
		id = number;
		name = name;
		author = author;
		quantity = quantity;
	}
};