#pragma once

#include <string>
using namespace std;

struct Reader_Books
{
	string borbook_number;			//书号
	string borbook_name;			//书名
	string borbook_author;			//作者
	int borbook_quantity;			//借阅量

	Reader_Books *next = NULL;		//next指针

	Reader_Books(string number, string name, string author, int quantity)
	{
		borbook_number = number;
		borbook_name = name;
		borbook_author = author;
		borbook_quantity = quantity;
	}
};