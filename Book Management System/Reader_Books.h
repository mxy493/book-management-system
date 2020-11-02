#ifndef BOOROWED_BOOKS_H_
#define BOOROWED_BOOKS_H_

#include <string>
using namespace std;

struct BorrowedBooks
{
	string id;		//���
	string name;	//����
	string author;	//����
	int quantity{0};	//������

	BorrowedBooks *next = nullptr;	//nextָ��

	BorrowedBooks(string id, string name, string author, int quantity)
	{
		id = id;
		name = name;
		author = author;
		quantity = quantity;
	}
};

#endif // !BOOROWED_BOOKS_H_
