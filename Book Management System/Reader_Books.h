#pragma once

#include <string>
using namespace std;

struct Reader_Books
{
	string borbook_number;			//���
	string borbook_name;			//����
	string borbook_author;			//����
	int borbook_quantity;			//������

	Reader_Books *next = NULL;		//nextָ��

	Reader_Books(string number, string name, string author, int quantity)
	{
		borbook_number = number;
		borbook_name = name;
		borbook_author = author;
		borbook_quantity = quantity;
	}
};