#ifndef BOOK_INFO_H_
#define BOOK_INFO_H_

#include "pch.h"

using namespace std;

struct BookInfo
{
	string id;		//书号
	string name;	//书名
	string author;	//作者
	int exist;		//现存量
	int inventory;	//总库存

	BookInfo()
	{
		id = -1;
		name = "";
		author = "";
		exist = -1;
		inventory = -1;
	}

	BookInfo(BookInfo * book)
	{
		id = book->id;
		name = book->name;
		author = book->author;
		exist = book->exist;
		inventory = book->inventory;
	}
};

#endif // !BOOK_INFO_H_