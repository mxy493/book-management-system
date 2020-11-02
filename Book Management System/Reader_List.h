#ifndef READER_LIST_H_
#define READER_LIST_H_

#include "Reader_Info.h"

struct ReaderList
{
	ReaderInfo reader_info;
	shared_ptr<ReaderList> next = nullptr;

	ReaderList() {}
	ReaderList(string id, string name)
	{
		reader_info.id = id;
		reader_info.name = name;
	}
};

#endif // !READER_LIST_H_
