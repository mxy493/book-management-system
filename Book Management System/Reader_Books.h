#pragma once

#include <string>
using namespace std;

struct BorrowedBooks
{
	string borbook_number;			//书号
	string borbook_name;			//书名
	string borbook_author;			//作者
	int borbook_quantity;			//借阅量

	BorrowedBooks *next = nullptr;		//next指针

	BorrowedBooks(string number, string name, string author, int quantity)
	{
		borbook_number = number;
		borbook_name = name;
		borbook_author = author;
		borbook_quantity = quantity;
	}
};