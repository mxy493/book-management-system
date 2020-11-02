#pragma once

#include <string>
using namespace std;

struct BorrowedBooks
{
	string id;		//���
	string name;	//����
	string author;	//����
	int quantity;	//������

	BorrowedBooks *next = nullptr;	//nextָ��

	BorrowedBooks(string number, string name, string author, int quantity)
	{
		id = number;
		name = name;
		author = author;
		quantity = quantity;
	}
};