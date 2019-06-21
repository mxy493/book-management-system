#pragma once

#include <string>
#include "Reader_Books.h"

using namespace std;

struct Reader_Info
{
	string reader_ID;						//学号
	string reader_name;						//姓名
	Reader_Books *borbook = NULL;			//借阅的图书的头指针
};

