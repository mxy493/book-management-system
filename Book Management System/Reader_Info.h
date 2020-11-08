#ifndef READER_INFO_H_
#define READER_INFO_H_

#include <string>
#include "Reader_Books.h"

using namespace std;

struct ReaderInfo
{
	string id;		//ѧ��
	string name;	//����
	shared_ptr<BorrowedBooks> borrowed_head = nullptr;  // ���ĵ�ͼ���ͷָ��
};

#endif
