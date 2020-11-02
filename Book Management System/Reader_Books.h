#ifndef BOOROWED_BOOKS_H_
#define BOOROWED_BOOKS_H_

#include <string>
using namespace std;

struct BorrowedBooks
{
	string id;		//书号
	string name;	//书名
	string author;	//作者
	int quantity{0};	//借阅量

	BorrowedBooks *next = nullptr;	//next指针

	BorrowedBooks(string id, string name, string author, int quantity)
	{
		id = id;
		name = name;
		author = author;
		quantity = quantity;
	}
};

#endif // !BOOROWED_BOOKS_H_
