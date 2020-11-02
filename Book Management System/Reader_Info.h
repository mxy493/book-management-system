#pragma once

#include <string>
#include "Reader_Books.h"

using namespace std;

struct ReaderInfo
{
	string id;		//学号
	string name;	//姓名
	BorrowedBooks *borrowed_head = nullptr;  // 借阅的图书的头指针
};

