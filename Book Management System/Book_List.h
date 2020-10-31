#pragma once

#include "Book_Info.h"

struct Book_List
{
	Book_Info b_info;
	shared_ptr<Book_List> b_next = nullptr;

	Book_List() {}
	Book_List(string number, string name, string author, int quantity) 
	{
		b_info.book_number = number;
		b_info.book_name = name;
		b_info.book_author = author;
		b_info.book_exist = quantity;
		b_info.book_inventory = quantity;
	}
	Book_List(string number, string name, string author, int exist, int inventory)
	{
		b_info.book_number = number;
		b_info.book_name = name;
		b_info.book_author = author;
		b_info.book_exist = exist;
		b_info.book_inventory = inventory;
	}

	Book_List(Book_Info & book)
	{
		b_info.book_number = book.book_number;
		b_info.book_name = book.book_name;
		b_info.book_author = book.book_author;
		b_info.book_exist = book.book_exist;
		b_info.book_inventory = book.book_inventory;
	}
};
