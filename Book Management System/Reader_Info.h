#pragma once

#include <string>
#include "Reader_Books.h"

using namespace std;

struct Reader_Info
{
	string reader_ID;						//ѧ��
	string reader_name;						//����
	Reader_Books *borbook = NULL;			//���ĵ�ͼ���ͷָ��
};

