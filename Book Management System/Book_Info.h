#pragma once

#include "pch.h"

using namespace std;

struct Book_Info
{
	string book_number;			//���
	string book_name;			//����
	string book_author;			//����
	int book_exist;				//�ִ���
	int book_inventory;			//�ܿ��

	Book_Info()
	{
		book_number = -1;
		book_name = "";
		book_author = "";
		book_exist = -1;
		book_inventory = -1;
	}

	Book_Info(Book_Info * book)
	{
		book_number = book->book_number;
		book_name = book->book_name;
		book_author = book->book_author;
		book_exist = book->book_exist;
		book_inventory = book->book_inventory;
	}
};
