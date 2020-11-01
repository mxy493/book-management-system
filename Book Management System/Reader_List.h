#pragma once

#include "Reader_Info.h"

struct Reader_List
{
	Reader_Info r_info;
	shared_ptr<Reader_List> r_next = nullptr;

	Reader_List() {}
	Reader_List(string ID, string name)
	{
		r_info.reader_ID = ID;
		r_info.reader_name = name;
	}
};
