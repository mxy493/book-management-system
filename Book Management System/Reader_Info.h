#pragma once

#include <string>
#include "Reader_Books.h"

using namespace std;

struct ReaderInfo
{
	string id;		//ѧ��
	string name;	//����
	BorrowedBooks *borrowed_head = nullptr;  // ���ĵ�ͼ���ͷָ��
};

