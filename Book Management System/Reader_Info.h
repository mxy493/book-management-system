#pragma once

#include <string>
#include "Reader_Books.h"

using namespace std;

struct ReaderInfo
{
	string reader_id;						//ѧ��
	string reader_name;						//����
	BorrowedBooks *borrowed_head = nullptr;	//���ĵ�ͼ���ͷָ��
};

