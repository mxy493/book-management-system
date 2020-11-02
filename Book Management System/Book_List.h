#pragma once

#include "Book_Info.h"

struct BookList
{
	BookInfo book_info;
	shared_ptr<BookList> next = nullptr;

	BookList() {}
	BookList(string number, string name, string author, int quantity) 
	{
		book_info.id = number;
		book_info.name = name;
		book_info.author = author;
		book_info.exist = quantity;
		book_info.inventory = quantity;
	}
	BookList(string number, string name, string author, int exist, int inventory)
	{
		book_info.id = number;
		book_info.name = name;
		book_info.author = author;
		book_info.exist = exist;
		book_info.inventory = inventory;
	}

	BookList(BookInfo & book)
	{
		book_info.id = book.id;
		book_info.name = book.name;
		book_info.author = book.author;
		book_info.exist = book.exist;
		book_info.inventory = book.inventory;
	}
};
