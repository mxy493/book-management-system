#pragma once

#include <string>
#include "Reader_Books.h"

using namespace std;

struct ReaderInfo
{
	string reader_id;						//学号
	string reader_name;						//姓名
	BorrowedBooks *borrowed_head = nullptr;	//借阅的图书的头指针
};

