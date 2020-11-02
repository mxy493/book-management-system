#pragma once

#include "Reader_Info.h"

struct ReaderList
{
	ReaderInfo reader_info;
	shared_ptr<ReaderList> reader_next = nullptr;

	ReaderList() {}
	ReaderList(string id, string name)
	{
		reader_info.reader_id = id;
		reader_info.reader_name = name;
	}
};
