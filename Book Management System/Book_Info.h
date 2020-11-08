#ifndef BOOK_INFO_H_
#define BOOK_INFO_H_

#include "pch.h"

using namespace std;

struct BookInfo
{
	string id;		//���
	string name;	//����
	string author;	//����
	int exist;		//�ִ���
	int inventory;	//�ܿ��

	BookInfo()
	{
		id = -1;
		name = "";
		author = "";
		exist = -1;
		inventory = -1;
	}

	BookInfo(const string& id, const string& name, const string& author, const int exist, const int inventory)
	{
		this->id = id;
		this->name = name;
		this->author = author;
		this->exist = exist;
		this->inventory = inventory;
	}

	BookInfo(const BookInfo* book)
	{
		id = book->id;
		name = book->name;
		author = book->author;
		exist = book->exist;
		inventory = book->inventory;
	}

	BookInfo(const BookInfo& book)
	{
		id = book.id;
		name = book.name;
		author = book.author;
		exist = book.exist;
		inventory = book.inventory;
	}

	BookInfo(const shared_ptr<BookInfo> book)
	{
		id = book->id;
		name = book->name;
		author = book->author;
		exist = book->exist;
		inventory = book->inventory;
	}
};

#endif // !BOOK_INFO_H_