#ifndef READER_INFO_H_
#define READER_INFO_H_

#include <string>
#include "Reader_Books.h"

using namespace std;

struct ReaderInfo
{
	string id;		//学号
	string name;	//姓名
	shared_ptr<BorrowedBooks> borrowed_head = nullptr;  // 借阅的图书的头指针
};

#endif
