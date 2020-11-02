#pragma once

#include <string>
using namespace std;

struct BorrowedBooks
{
	string borbook_number;			//���
	string borbook_name;			//����
	string borbook_author;			//����
	int borbook_quantity;			//������

	BorrowedBooks *next = nullptr;		//nextָ��

	BorrowedBooks(string number, string name, string author, int quantity)
	{
		borbook_number = number;
		borbook_name = name;
		borbook_author = author;
		borbook_quantity = quantity;
	}
};