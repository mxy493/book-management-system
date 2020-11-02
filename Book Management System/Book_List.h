#pragma once

#include "Book_Info.h"

struct BookList
{
	BookInfo book_info;
	shared_ptr<BookList> book_next = nullptr;

	BookList() {}
	BookList(string number, string name, string author, int quantity) 
	{
		book_info.book_number = number;
		book_info.book_name = name;
		book_info.book_author = author;
		book_info.book_exist = quantity;
		book_info.book_inventory = quantity;
	}
	BookList(string number, string name, string author, int exist, int inventory)
	{
		book_info.book_number = number;
		book_info.book_name = name;
		book_info.book_author = author;
		book_info.book_exist = exist;
		book_info.book_inventory = inventory;
	}

	BookList(BookInfo & book)
	{
		book_info.book_number = book.book_number;
		book_info.book_name = book.book_name;
		book_info.book_author = book.book_author;
		book_info.book_exist = book.book_exist;
		book_info.book_inventory = book.book_inventory;
	}
};
