#include <math.h>

#include "pch.h"
#include "Library.h"

using namespace std;

void Library::ImportBookData()
{
	cout << endl << endl << "==============================" << endl << endl;
	ifstream infile1("book data.dat", ios::in);

	shared_ptr<Book_List> b_cur = nullptr;
	if (!infile1)
	{
		cerr << "<!>图书信息导入失败！" << endl;
	}
	else
	{
		while (!infile1.eof())
		{
			string b_number;				//书号
			string b_name;					//书名
			string b_author;				//作者
			int b_exist;					//现存量
			int b_inventory;				//库存量
			infile1 >> b_number >> b_name >> b_author >> b_exist >> b_inventory;

			// 删除节点时需要释放内存
			auto newBook = make_shared<Book_List>(b_number, b_name, b_author, b_exist, b_inventory);

			if (b_first == nullptr)
			{
				b_first = newBook;
				b_cur = b_first;
			}
			else
			{
				b_cur->b_next = newBook;
				b_cur = b_cur->b_next;
			}
		}
		infile1.close();
		cout << "<!>图书信息导入成功！" << endl;
	}
	cout << endl << "==============================" << endl;
}

void Library::ImportReaderData()
{
	cout << endl << endl << "==============================" << endl << endl;
	ifstream infile2("reader data.dat", ios::in);

	if (!infile2)
	{
		cerr << "<!>读者信息导入失败！" << endl;
	}
	else
	{
		shared_ptr<Reader_List> r_cur = nullptr;
		while (!infile2.eof())
		{
			string r_ID;				//学号
			string r_name;				//姓名

			infile2 >> r_ID >> r_name;

			shared_ptr<Reader_List> newReader = make_shared<Reader_List>(r_ID, r_name);

			ImportBorrowData(newReader, r_ID);  // 导入该读者的借阅数据

			if (r_first == nullptr)
			{
				r_first = newReader;
				r_cur = r_first;
			}
			else
			{
				r_cur->r_next = newReader;
				r_cur = r_cur->r_next;
			}
		}
	}
	infile2.close();
	cout << "<!>读者信息导入成功！" << endl;
	cout << endl << "==============================" << endl;
}

void Library::ImportBorrowData(shared_ptr<Reader_List> new_reader, const string& reader_id)
{
	// 导入该读者借阅信息
	string r_b_file = "reader books ";
	string r_b_file_type = ".dat";
	r_b_file = r_b_file + reader_id + r_b_file_type;
	ifstream infile3(r_b_file, ios::in);

	Reader_Books* r_b_cur = nullptr;  // 指向借阅的图书的末尾节点
	if (!infile3)
	{
		cerr << "<!>读者" << r_b_file << "的图书借阅信息导入失败！" << endl;
	}
	while (!infile3.eof())
	{
		string r_b_number;				//书号
		string r_b_name;				//书名
		string r_b_author;				//作者
		int r_b_borrow;					//借阅量
		infile3 >> r_b_number >> r_b_name >> r_b_author >> r_b_borrow;

		Reader_Books* newBorBook = new Reader_Books(r_b_number, r_b_name, r_b_author, r_b_borrow);
		if (new_reader->r_info.borbook == NULL)
		{
			new_reader->r_info.borbook = newBorBook;
			r_b_cur = new_reader->r_info.borbook;
		}
		else
		{
			r_b_cur->next = newBorBook;
			r_b_cur = r_b_cur->next;
		}
	}
	infile3.close();
	cout << "<!>读者" << reader_id << "图书借阅信息导入成功！" << endl;
}

void Library::BookListAdd(shared_ptr<Book_List> newBook)
{
	shared_ptr<Book_List> cur = b_first;
	if (b_first == NULL) {
		b_first = newBook;
	}
	else {
		//判断是否存在该图书信息
		while (cur != NULL)
		{
			if (newBook->b_info.book_number == cur->b_info.book_number)
			{
				cur->b_info.book_exist += newBook->b_info.book_exist;
				cur->b_info.book_inventory += newBook->b_info.book_inventory;
				break;
			}
			else {
				if (cur->b_next == NULL) {
					cur->b_next = newBook;
					break;
				}
			}
			cur = cur->b_next;
		}
	}
}

void Library::BookListShow()
{
	if (b_first == nullptr)
	{
		cout << endl << "==============================" << endl;
		cout << endl << "<!>当前暂无已入库图书！" << endl;
		cout << endl << "==============================" << endl;
	}
	else
	{
		auto cur = b_first;
		cout.setf(ios::left | ios::unitbuf);						//左对齐，每次输出后刷新所有流
		cout << endl << setw(70) << setfill('-') << "-" << setfill(' ') << endl;
		cout << setw(6) << "书号" <<
			setw(30) << "书名" <<
			setw(16) << "作者" <<
			setw(10) << "现存量" <<
			setw(8) << "总库存量" << endl << endl;
		while (cur != nullptr)
		{
			cout << setw(6) << cur->b_info.book_number <<
				setw(30) << cur->b_info.book_name <<
				setw(16) << cur->b_info.book_author <<
				setw(10) << cur->b_info.book_exist <<
				setw(8) << cur->b_info.book_inventory << endl;
			cur = cur->b_next;
		}
		cout << setw(70) << setfill('-') << "-" << setfill(' ') << endl;
	}
}

// 图书查找
void Library::BookFind()
{
	int sel;
	cout << "0.链表查找" << endl;
	cout << "1.B树查找" << endl;
	cout << "选择查找方式：";
	cin >> sel;

	cout << endl << "==============================" << endl;
	string info;
	cout << endl << "请输入图书的相关信息(书号、书名、作者):";
	cin >> info;
	int seq = 0;  // 序号
	vector<Book_Info*> books;  // 保存查找结果的指针数组
	// 链表查找
	if (sel == 0) {
		ListFind(books, info);
	}
	// B树查找
	else if (sel == 1) {
		BTreeEmpty();					//置空B树
		BTreeEstablish();				//构建B树
		backtrackFind(btree_root, books, info);
	}
	//打印查找结果
	if (!books.empty())
	{
		cout << endl << setw(72) << setfill('-') << "-" << setfill(' ') << endl;
		cout << endl << setw(6) << "序号" <<
			setw(10) << "书号" <<
			setw(20) << "书名" <<
			setw(16) << "作者" <<
			setw(10) << "现存量" <<
			setw(10) << "总库存量" << endl;
		for (int i = 0; i < books.size(); i++) {
			cout << setw(6) << i + 1 <<
				setw(10) << books[i]->book_number <<
				setw(20) << books[i]->book_name <<
				setw(16) << books[i]->book_author <<
				setw(10) << books[i]->book_exist <<
				setw(10) << books[i]->book_inventory << endl;
		}
		cout << endl << setw(72) << setfill('-') << "-" << setfill(' ') << endl;
	}
	else {
		cout << endl << "<!>没有找到相关图书！" << endl;
		cout << endl << "==============================" << endl;
	}
}

// B树递归查找
void Library::backtrackFind(BTreeNode* cur, vector<Book_Info*>& books, string info) {
	if (cur == nullptr) return;
	for (int i = 0; i <= cur->num; i++) {
		//递归查找
		backtrackFind(cur->ptr[i], books, info);
		if (i == 0) continue;//key[0]无意义
		if (cur->key[i]->book_number.find(info) != -1 ||
			cur->key[i]->book_name.find(info) != -1 ||
			cur->key[i]->book_author.find(info) != -1)
		{
			books.push_back(cur->key[i]);
		}
	}
}

// 链表查找
void Library::ListFind(vector<Book_Info*>& books, string info)
{
	auto cur = b_first;
	while (cur != NULL)
	{
		if (cur->b_info.book_number.find(info) != -1 || 
			cur->b_info.book_name.find(info) != -1 || 
			cur->b_info.book_author.find(info) != -1)
		{
			books.push_back(&cur->b_info);  // 保存图书在内存中的地址
		}
		cur = cur->b_next;
	}
}

void Library::FuncEmpty()
{
	cout << endl << "==============================" << endl;

	int func;
	cout << endl << "【1】清楚某一本书的库存" << endl;
	cout << "【2】清空图书馆所有图书" << endl;
	cout << "【0】返回主菜单" << endl << endl;
	cout << ">>>请选择要执行的功能:";
	cin >> func;

	if (func == 0)
		return;
	else if (func == 1)
		BookRemove();
	else if (func == 2)
	{
		BookListEmpty();
		cout << endl;
		cout << "<!>链表已清空！" << endl;
		BTreeEmpty();
		cout << "<!>B树已清空！" << endl;
	}

	cout << endl << "==============================" << endl;
}

void Library::BookRemove()
{
	auto cur = b_first;
	string info;
	vector<string> nums;
	int n = 0;
	cout << "请输入要清楚库存的图书的相关信息(书号、书名、作者):";
	cin >> info;
	while (cur != NULL)
	{
		if (cur->b_info.book_number.find(info) != -1 || cur->b_info.book_name.find(info) != -1 || cur->b_info.book_author.find(info) != -1)
		{
			if (n == 0)
			{
				cout << endl << setw(76) << setfill('-') << "-" << setfill(' ') << endl;
				cout << setw(6) << "序号" << 
					setw(6) << "书号" <<
					setw(30) << "书名" <<
					setw(16) << "作者" <<
					setw(10) << "现存量" <<
					setw(8) << "总库存量" << endl << endl;
			}
			nums.push_back(cur->b_info.book_number);
			cout << setw(6) << ++n <<
				setw(6) << cur->b_info.book_number <<
				setw(30) << cur->b_info.book_name <<
				setw(16) << cur->b_info.book_author <<
				setw(10) << cur->b_info.book_exist <<
				setw(8) << cur->b_info.book_inventory << endl;
		}
		cur = cur->b_next;
	}
	if (n > 0)
		cout << setw(76) << setfill('-') << "-" << setfill(' ') << endl;
	else
	{
		cout << "<!>没有找到您想要清除库存的图书信息！" << endl;
		return;
	}

	cur = b_first;
	int num;
	cout << "请输入要清除的图书所对应的序号:";
	while (cin >> num)
	{
		if (num > n) cout << "输入有误，请重新输入:";
		else break;
	}
	// 首节点特殊处理
	if (b_first->b_info.book_number == nums[num - 1])
	{
		if (b_first->b_info.book_exist != b_first->b_info.book_inventory)
		{
			cout << endl << "<!>清除库存失败！当前还有借出的图书暂未归还！" << endl;
		}
		else
		{
			// 智能自动释放内存，无需delete
			b_first = b_first->b_next;
			cout << endl << "<!>库存已清除！" << endl;
		}
	}
	// 其它节点
	else
	{
		while (cur->b_next != NULL)
		{
			if (cur->b_next->b_info.book_number == nums[num - 1])
			{
				if (cur->b_next->b_info.book_exist != cur->b_next->b_info.book_inventory)
				{
					cout << endl << "<!>清除库存失败！当前还有借出的图书暂未归还！" << endl;
					break;
				}
				else
				{
					cur->b_next = cur->b_next->b_next;
					// 智能自动释放内存，无需delete
					cout << endl << "<!>库存已清除！" << endl;
					break;
				}
			}
			cur = cur->b_next;
		}
	}
}

void Library::BookListEmpty()
{
	while (b_first != nullptr)
	{
		// 智能指针自动释放内存
		b_first = b_first->b_next;
	}
}

void Library::ReaderBooks()
{
	cout << endl << "==============================" << endl;
	int func;
	cout << endl;
	cout << "【1】查看已注册读者" << endl;
	cout << "【2】查询已借阅图书" << endl;
	cout << "【3】返回主菜单" << endl;
	cout << endl << ">>>请选择要执行的功能:";
	L:cin >> func;

	//输入有误
	if (func != 0 && func != 1 && func != 2)
	{
		cout << "输入有误，请重新输入:";
		goto L;
	}

	//返回主菜单
	else if (func == 0)
	{
		cout << endl << "==============================" << endl;
		return;
	}

	//查看已注册读者
	else if (func == 1)
		ReaderList();

	//查询已借阅图书
	else
		ReaderBorrowed();
	cout << endl << "==============================" << endl;
}

void Library::ReaderList()
{
	cout.setf(ios::left | ios::unitbuf);  // 左对齐，每次输出后刷新所有流
	if (r_first == nullptr)
	{
		cout << "<!>当前无已注册读者信息！" << endl;
		cout << endl << "==============================" << endl;
		return;
	}
	else {
		cout << endl << setw(20) << setfill('-') << "-" << setfill(' ') << endl;
		cout << setw(10) << "学号" << setw(10) << "姓名" << endl << endl;

		shared_ptr<Reader_List> r_cur = r_first;
		while (r_cur != NULL)
		{
			cout << setw(10) << r_cur->r_info.reader_ID << setw(10) << r_cur->r_info.reader_name << endl;
			r_cur = r_cur->r_next;
		}
		cout << setw(20) << setfill('-') << "-" << setfill(' ') << endl;
	}
}

void Library::ReaderBorrowed()
{
	if (r_first == nullptr)
	{
		cout << "当前无已注册读者信息！" << endl;
	}
	else
	{
		string ID;
		cout << endl << "请输入您的学号:";
		cin >> ID;
		shared_ptr<Reader_List> r_cur = r_first;
		bool isExist = false;
		while (r_cur != NULL)
		{
			if (r_cur->r_info.reader_ID == ID)
			{
				isExist = true;
				cout << endl << "您的图书借阅信息如下:" << endl << endl;
				cout.setf(ios::left | ios::unitbuf);
				cout << "学号:" << setw(10) << r_cur->r_info.reader_ID << "姓名:" << setw(1) << r_cur->r_info.reader_name << endl;
				if (r_cur->r_info.borbook == NULL)
				{
					cout << endl << "<!>您当前没有借阅任何图书！" << endl;
				}
				else
				{
					cout.setf(ios::left | ios::unitbuf);
					cout << setw(58) << setfill('-') << "-" << setfill(' ') << endl;
					cout << setw(6) << "序号" << setw(10) << "书号" << setw(20) <<
						"书名" << setw(16) << "作者" << setw(6) << "数量" << endl << endl;
					Reader_Books *r_b_cur = r_cur->r_info.borbook;
					int i = 1;
					while (r_b_cur != NULL)
					{
						cout << setw(6) << i << setw(10) << r_b_cur->borbook_number << setw(20) << r_b_cur->borbook_name <<
							setw(16) << r_b_cur->borbook_author << setw(6) << r_b_cur->borbook_quantity << endl;
						i++;
						r_b_cur = r_b_cur->next;
					}
					cout << setw(58) << setfill('-') << "-" << setfill(' ') << endl;
				}
			}
			r_cur = r_cur->r_next;
		}
		if (isExist == false)
		{
			cout << endl << "<!>学号信息不存在或输入有误！" << endl;
		}
	}
}

void Library::BookBorrow()
{
	cout << endl << "==============================" << endl << endl;
	shared_ptr<Book_List> b_cur = b_first;
	string info;
	vector<string> nums;
	int n = 0;
	cout << "请输入图书的相关信息(书号、书名、作者):";
	cin >> info;
	bool isExist = false;
	while (b_cur != nullptr)
	{
		if (b_cur->b_info.book_number.find(info) != -1 || b_cur->b_info.book_name.find(info) != -1 || b_cur->b_info.book_author.find(info) != -1)
		{
			isExist = true;
			if (n == 0)
			{
				cout << endl << "已为您找到以下图书:" << endl;
				cout << setw(72) << setfill('-') << "-" << setfill(' ') << endl;
				cout << setw(6) << "序号" <<
					setw(10) << "书号" <<
					setw(20) << "书名" <<
					setw(16) << "作者" <<
					setw(10) << "现存量" <<
					setw(10) << "总库存量" << endl;
			}
			nums.push_back(b_cur->b_info.book_number);
			cout << setw(6) << n + 1 <<
				setw(10) << b_cur->b_info.book_number <<
				setw(20) << b_cur->b_info.book_name <<
				setw(16) << b_cur->b_info.book_author <<
				setw(10) << b_cur->b_info.book_exist <<
				setw(10) << b_cur->b_info.book_inventory << endl;
			n++;
		}
		b_cur = b_cur->b_next;
	}
	if (isExist == false)
	{
		cout << endl << "<!>没有找到相关图书信息！" << endl;
		return;
	}
	else
	{
		cout << setw(72) << setfill('-') << "-" << setfill(' ') << endl << endl;

		b_cur = b_first;
		int num;
		cout << "请输入要借阅的图书所对应的序号:";
		while (cin >> num)
		{
			if (num > n) break;
			cout << "输入有误，请重新输入:";
		}
		while (b_cur != nullptr)
		{
			if (b_cur->b_info.book_number == nums[num - 1])
			{
				cout << "你要借阅的图书信息如下:" << endl << endl;
				cout << "书号:" << b_cur->b_info.book_number << endl;
				cout << "书名:" << b_cur->b_info.book_name << endl;
				cout << "作者:" << b_cur->b_info.book_name << endl;
				cout << "现存数:" << b_cur->b_info.book_exist << endl;
				cout << "总库存:" << b_cur->b_info.book_inventory << endl;
				int qua = 0;
				cout << endl << "请输入您要借阅的数量:";
				while (cin >> qua)
				{
					if (qua < b_cur->b_info.book_exist) break;
					cout << "馆存数量不足，如您还需借阅，请重新输入:";
				}
				if (qua <= 0)
					break;
				else
				{
					auto r_cur = r_first;			//指向当前读者
					string ID;
					string name;
					cout << "请输入您的学号:";
					cin >> ID;
					cout << "请输入您的姓名:";
					cin >> name;

					auto newReader = make_shared<Reader_List>(ID, name);
					Reader_Books *newBorBook = new Reader_Books(b_cur->b_info.book_number, b_cur->b_info.book_name, b_cur->b_info.book_author, qua);

					if (r_first == nullptr)  // 读者信息库为空，则直接添加该读者以及借阅的图书
					{
						r_first = newReader;
						r_first->r_info.borbook = newBorBook;
						b_cur->b_info.book_exist -= qua;  // 减去借阅的数量
					}
					else									//否则，判断是否存在该读者信息
					{
						bool exist = false;   // 已存在该读者信息
						while (r_cur != nullptr)
						{
							if (r_cur->r_info.reader_ID == ID)  // 说明已存在该读者信息
							{
								exist = true;
								if (r_cur->r_info.borbook == nullptr)
								{
									r_cur->r_info.borbook = newBorBook;  // 没有借阅过图书
									break;
								}
								else {
									Reader_Books *borbook_cur = r_cur->r_info.borbook;		//指向当前读者的当前图书
									bool borrowed = false;
									while (borbook_cur != nullptr)
									{
										if (b_cur->b_info.book_number == borbook_cur->borbook_number)
										{
											borrowed = true;
											b_cur->b_info.book_exist -= qua;				//图书馆该书现存量减qua
											borbook_cur->borbook_number += qua;				//该读者借阅的该图书量加qua
											break;
										}
										borbook_cur = borbook_cur->next;
									}
									if (!borrowed)  // 该读者没有借阅过这本书
									{
										borbook_cur->next = newBorBook;
										b_cur->b_info.book_exist -= qua;  // 减去借出数量
									}
								}
								break;
							}
							r_cur = r_cur->r_next;
						}
						if (!exist)  // 不存在该读者的相关信息
						{
							r_cur->r_next = newReader;
							r_cur->r_next->r_info.borbook = newBorBook;		//新建读者借阅的图书信息	
							b_cur->b_info.book_exist -= qua;
							break;
						}
					}
				}
				break;  // 已经在图书库存中找到了这本书，执行相应操作后则跳出循环
			}
			b_cur = b_cur->b_next;
		}
	}
	cout << endl << "<!>图书借阅成功！" << endl;
	cout << endl << "==============================" << endl;
}

void Library::BookReturn()
{
	cout << endl << "==============================" << endl << endl;
	if (r_first == nullptr)
		cout << "当前没有已注册学生信息！" << endl;
	else
	{
		string ID;
		cout << "请输入您的学号:";
		cin >> ID;
		auto r_cur = r_first;  // 当前读者
		bool isExist = false;
		while (r_cur != nullptr)
		{
			if (r_cur->r_info.reader_ID == ID)
			{
				isExist = true;
				cout.setf(ios::left | ios::unitbuf);
				cout << "学号:" << setw(10) << r_cur->r_info.reader_ID << "姓名:" << setw(10) << r_cur->r_info.reader_name << endl;
				if (r_cur->r_info.borbook == nullptr)
				{
					cout << "<!>您当前没有借阅任何图书！" << endl;
					break;
				}
				else
				{
					// 打印该读者当前借阅的所有图书
					cout.setf(ios::left | ios::unitbuf);
					cout << endl << setw(58) << setfill('-') << "-" << setfill(' ') << endl;
					cout << setw(6) << "序号" << setw(10) << "书号" << setw(20) <<
						"书名" << setw(16) << "作者" << setw(6) << "数量" << endl << endl;
					Reader_Books *r_b_cur = r_cur->r_info.borbook;  // 当前的该读者借阅的图书
					int n = 1;
					vector<string> nums;
					while (r_b_cur != nullptr)
					{
						cout << setw(6) << n << setw(10) << r_b_cur->borbook_number << setw(20) << r_b_cur->borbook_name <<
							setw(16) << r_b_cur->borbook_author << setw(6) << r_b_cur->borbook_quantity << endl;
						nums.push_back(r_b_cur->borbook_number);
						n++;
						r_b_cur = r_b_cur->next;
					}
					cout << setw(58) << setfill('-') << "-" << setfill(' ') << endl << endl;

					// 选择要归还的图书并归还
					int index;
					cout << "请选择您要归还的图书:";
					while (cin >> index)
					{
						if (index >= 1 && index < n) break;
						cout << "输入有误，请重新输入:";
					}
					int quantity;
					cout << "请输入要归还的数量:";
					while (cin >> quantity)
					{
						if (quantity >= 0 && quantity <= r_b_cur->borbook_quantity) break;
						cout << "输入有误，请重新输入:";
					}
					// 要归还的是头结点的图书
					if (r_cur->r_info.borbook->borbook_number == nums[index - 1])
					{
						if (quantity == r_b_cur->borbook_quantity)			//清空该读者借阅图书中的这本图书
						{
							Reader_Books* tmp = r_cur->r_info.borbook;
							r_cur->r_info.borbook = r_cur->r_info.borbook->next;  // 移动头指针
							delete tmp;  // 释放内存
						}
						else r_cur->r_info.borbook->borbook_quantity -= quantity;  // 减去归还图书的数量
					}
					// 要归还的不是头结点的图书，需要找到前一个结点
					else
					{
						r_b_cur = r_cur->r_info.borbook;  // 修改指针指向借阅的第一本图书
						while (r_b_cur->next != nullptr)
						{
							if (r_b_cur->next->borbook_number == nums[index - 1])
								break;
							r_b_cur = r_b_cur->next;
						}
						if (quantity == r_b_cur->next->borbook_quantity)  // 清空该读者借阅图书中的这本图书
						{
							Reader_Books* tmp = r_b_cur->next;
							r_b_cur->next = r_b_cur->next->next;  // 修改指针指向
							delete tmp;  // 释放内存
						}
						else r_b_cur->next->borbook_quantity -= quantity;  // 减去归还图书的数量
					}

					// 增加归还的图书数量
					auto b_cur = b_first;
					bool exist = false;
					while (b_cur != nullptr)
					{
						if (b_cur->b_info.book_number == nums[index - 1])
						{
							exist = true;
							b_cur->b_info.book_exist += quantity;
							cout << endl << "<!>图书已成功归还！" << endl;
							break;
						}
						b_cur = b_cur->b_next;
					}
					if (!exist)
					{
						cout << endl << "<!>图书归还失败！图书馆内没有这本书的信息！" << endl;
					}
				}
				break;
			}
			r_cur = r_cur->r_next;
		}
		if (!isExist) cout << "系统中不存在您的相关信息！" << endl;
	}
	cout << endl << "==============================" << endl;
}

void Library::SaveData()
{
	cout << endl << "==============================" << endl << endl;
	ofstream outfile1("book data.dat", ios::out);
	auto b_cur = b_first;

	if (!outfile1)
	{
		cerr << "<!>图书信息保存失败！" << endl;
		exit(1);
	}

	while (b_cur != nullptr)
	{
		outfile1.setf(ios::right | ios::unitbuf);  // 右对齐，每次输出后刷新所有流
		outfile1 << setw(6) << b_cur->b_info.book_number <<
			setw(30) << b_cur->b_info.book_name <<
			setw(16) << b_cur->b_info.book_author <<
			setw(10) << b_cur->b_info.book_exist <<
			setw(10) << b_cur->b_info.book_inventory;
		if (b_cur->b_next != nullptr) outfile1 << endl;
		b_cur = b_cur->b_next;
	}
	outfile1.close();
	cout << "<!>图书信息保存成功！" << endl;

	ofstream outfile2("reader data.dat", ios::out);
	if (!outfile2)
	{
		cerr << "<!>读者信息保存失败！" << endl;
		exit(1);
	}
	auto r_cur = r_first;
	while (r_cur != nullptr)
	{
		outfile2.setf(ios::right | ios::unitbuf);  // 右对齐，每次输出后刷新所有流
		outfile2 << setw(10) << r_cur->r_info.reader_ID << setw(20) << r_cur->r_info.reader_name;
		if (r_cur->r_info.borbook != nullptr)
		{
			string r_b_file = "reader books ";
			string r_b_file_type = ".dat";
			r_b_file = r_b_file + r_cur->r_info.reader_ID + r_b_file_type;
			
			ofstream outfile3(r_b_file, ios::out);
			if (!outfile3)
			{
				cerr << "<!>读者借阅信息保存失败！" << endl;
				exit(1);
			}
			Reader_Books *r_b_cur = r_cur->r_info.borbook;
			while (r_b_cur != nullptr)
			{
				outfile3.setf(ios::right | ios::unitbuf);  // 右对齐，每次输出后刷新所有流
				outfile3 << setw(6) << r_b_cur->borbook_number <<
					setw(30) << r_b_cur->borbook_name <<
					setw(10) << r_b_cur->borbook_author <<
					setw(4) << r_b_cur->borbook_quantity;
				if (r_b_cur->next != nullptr) outfile3 << endl;
				r_b_cur = r_b_cur->next;
			}
			outfile3.close();
			cout << "<!>读者" << r_cur->r_info.reader_ID << "的借阅信息保存成功！" << endl;
		}
		if (r_cur->r_next != nullptr) outfile2 << endl;
		r_cur = r_cur->r_next;
	}
	outfile2.close();
	cout << "<!>读者信息保存成功！" << endl;
	cout << endl << "==============================" << endl;
}

void Library::BTreeEmpty()
{
	// 应该遍历2-3-4树释放内存
	BTreeNode* tmp = btree_root;
	btree_root = NULL;
	delete tmp;
}

bool Library::BookIsExistInBTree(BTreeNode * loc, Book_Info & book)
{
	if (loc == NULL)
		return false;
	for (int i = 0; i < loc->num; i++)
	{
		if (book.book_number == loc->key[i + 1]->book_number)
			return true;
	}
	return false;
}

//定位元素，如果B树为空则返回nullptr，否则返回最后的结点位置
BTreeNode * Library::BTreeLocate(Book_Info & book)
{
	BTreeNode *btree_cur = btree_root;
	while (btree_cur != NULL)
	{
		for (int i = 0; i < btree_cur->num; i++)
		{
			//元素已存在
			if (book.book_number == btree_cur->key[i + 1]->book_number)
				return btree_cur;
			
			//元素[i+1]的左侧找
			if (book.book_number < btree_cur->key[i + 1]->book_number)
			{
				//如果btree_cur->ptr[i] == NULL说明234树中不存在该元素（图书）
				if (btree_cur->ptr[i] == NULL)
					return btree_cur;
				else
				{
					btree_cur = btree_cur->ptr[i];
					break;
				}
			}

			//最右侧找
			else if (i == btree_cur->num - 1)
			{
				//如果btree_cur->ptr[i] == NULL说明234树中不存在该元素（图书）
				if (btree_cur->ptr[i+1] == NULL)
					return btree_cur;
				else
				{
					btree_cur = btree_cur->ptr[i + 1];
					break;
				}
			}
		}
	}
	return nullptr;
}

void Library::BTreeEstablish()
{
	cout << endl << "==============================" << endl << endl;
	cout << endl;
	cout << "<!>开始建立索引！" << endl << endl;
	shared_ptr<Book_List> b_cur = b_first;
	if (b_first == NULL)
	{
		cout << "<!>图书信息为空！" << endl;
		return;
	}
	else
	{
		while (b_cur != NULL)
		{
			BTreeNode * loc = BTreeLocate(b_cur->b_info);		//指向当前结点

			//该元素（图书）已存在
			if (BookIsExistInBTree(loc, b_cur->b_info))
			{
				cout << "- 书号 " << b_cur->b_info.book_number << " 的图书《" << b_cur->b_info.book_name << "》已存在，无需插入" << endl << endl;
				b_cur = b_cur->b_next;
				continue;
			}

			//将当前结点插入到234树中
			else
			{
				cout << "- 书号 " << b_cur->b_info.book_number << " 的图书《" << b_cur->b_info.book_name << "》不在树中，插入该新元素" << endl;
				BTreeInsert(b_cur, loc);
				cout << "- 书号 " << b_cur->b_info.book_number << " 的图书《" << b_cur->b_info.book_name << "》已成功插入B树" << endl << endl;
			}
			b_cur = b_cur->b_next;
		}
	}
	cout << endl << "<!>B树（234树）构建成功！" << endl << endl;
	cout << endl << "==============================" << endl << endl;
}

void Library::BookShow()
{
	cout << endl << "==============================" << endl << endl;

	int fun;
	cout << "【1】列表显示" << endl;
	cout << "【2】B树显示" << endl;
	cout << "【0】返回主菜单" << endl;
	cout << endl << ">>>请选择显示模式:";
Label:cin >> fun;
	if (fun == 0)
		return;
	else if (fun == 1)
		BookListShow();
	else if (fun == 2)
	{
		BTreeEmpty();					//置空B树
		BTreeEstablish();				//构建B树
		BookBTreeShow(btree_root, 0);	//输出B树
	}
	else
	{
		cout << "输入有误，请重新输入:";
		goto Label;
	}
	cout << endl << "==============================" << endl;
}

void Library::BookAdd()
{
	cout << endl << endl << "==============================" << endl;

	string number;				//书号
	string name;				//书名
	string author;				//作者
	int quantity;				//数量

	cout << endl;
	cout << "请输入书号:";
	cin >> number;
	cout << "请输入书名:";
	cin >> name;
	cout << "请输入作者:";
	cin >> author;
	cout << "请输入数量:";
	cin >> quantity;

	// 新图书，注意释放内存
	auto newBook = make_shared<Book_List>(number, name, author, quantity);

	//添加到图书链表中
	BookListAdd(newBook);
	cout << endl << "<!> 已成功添加到链表中！" << endl;

	//插入到B树中
	BTreeInsert(newBook, BTreeLocate(newBook->b_info));
	cout << endl << "<!> 已成功添加到B树中！" << endl;

	cout << endl << "<!> 图书入库成功！" << endl;
	cout << endl << "==============================" << endl;
}

//前提是已知node结点元素未满能直接插入
//不用分裂节点的情况下直接插入元素
BTreeNode *Library::InsertEleDirect(BTreeNode * node, BTreeNode * book)
{
	//定位，插入到key[i]
	int i;
	for (i = 0; i < node->num; i++)
	{
		if (book->key[1]->book_number < node->key[i + 1]->book_number)
			break;
		else if (book->key[1]->book_number > node->key[i + 1]->book_number)
		{
			//直接插入到末尾
			if (i == node->num - 1)
			{
				i = i + 2;
				node->key[i] = new Book_Info(book->key[1]);
				node->ptr[i - 1] = book->ptr[0];
				node->ptr[i] = book->ptr[1];
				node->num++;
				return node;
			}
			continue;
		}
	}

	int j;
	//元素后移
	for (j = node->num + 1; j > i; j--)
	{
		node->key[j] = node->key[j - 1];
		node->ptr[j] = node->ptr[j - 1];
	}
	//插入元素
	node->key[j + 1] = book->key[1];
	node->ptr[j] = book->ptr[0];
	node->ptr[j + 1] = book->ptr[1];
	node->num++;
	return node;
}

//在loc所指结点插入新图书book
void Library::BTreeInsert(shared_ptr<Book_List> book, BTreeNode * loc)
{
	BTreeNode * loc_parent;					//指向当前结点的父结点
	BTreeNode * newbook;					//新元素结点
	BTreeNode * newBTreeNode = NULL;		//上提元素结点

	newbook = new BTreeNode(&book->b_info);		//传值初始化

Label:
	//如果loc为空，即234树根指针为空，B树为空，则将根指针指向新节点
	if (loc == NULL)
	{
		if (newBTreeNode == NULL)
			loc = newbook;
		else
			loc = newBTreeNode;
		btree_root = loc;
		book = book->b_next;
		return;
	}

	//loc非空，则在loc所指结点插入新元素
	else
	{
		//如果当前结点未满3个元素，则将该元素插入到key[j]之前
		if (loc->num < m - 1)
		{
			loc = InsertEleDirect(loc, newbook);
			for (int i = 0; i <= loc->num; i++)
			{
				if (loc->ptr[i] == NULL)
					continue;
				loc->ptr[i]->parent = loc;
			}
			return;			//已插入成功，结束函数
		}

		//当前结点已满3个元素，需要分裂结点
		else
		{
			//int up = ceil((i + 1) / 2.0);				//取(i+1)/2的上整，对应的元素即loc->key[up]上提
			int up = 2;									//默认将中间的元素即loc->key[2]上提
			//新建一个BTreeNode *指针指向要上提的元素
			newBTreeNode = new BTreeNode(loc->key[up]);

			newBTreeNode->ptr[0] = new BTreeNode();
			newBTreeNode->ptr[1] = loc;

			//为0左子树插入，为1右子树插入
			int left_right = (loc->key[up]->book_number) > (newbook->key[1]->book_number) ? 0 : 1;

			//构造左子树结点
			newBTreeNode->ptr[0]->num = up - 1;
			newBTreeNode->ptr[0]->parent = newBTreeNode;
			for (int k = 0; k < up; k++)
			{
				newBTreeNode->ptr[0]->ptr[k] = loc->ptr[k];
				if (k == 0)
					continue;
				newBTreeNode->ptr[0]->key[k] = new Book_Info(loc->key[k]);
			}

			//插入到左子节点中
			if (left_right == 0)
				newBTreeNode->ptr[0] = InsertEleDirect(newBTreeNode->ptr[0], newbook);

			//构造右子树结点
			loc_parent = loc->parent;
			newBTreeNode->ptr[1]->parent = newBTreeNode;
			for (int k = 0; k <= loc->num; k++)
			{
				if (k < up)
				{
					loc->key[k] = NULL;
					loc->ptr[k] = NULL;
				}
				else
				{
					loc->key[k - up] = new Book_Info(loc->key[k]);
					loc->ptr[k - up] = loc->ptr[k];
					loc->key[k] = NULL;
					loc->ptr[k] = NULL;
				}
			}
			loc->key[0] = NULL;
			loc->num -= up;

			//插入到右子节点中
			if (left_right == 1)
				newBTreeNode->ptr[1] = InsertEleDirect(newBTreeNode->ptr[1], newbook);

			//newBTreeNode作为新元素在上一层插入
			newbook = newBTreeNode;
			loc = loc_parent;
			goto Label;
		}
	}
}

//判断该图书是否已存在于图书链表中
bool Library::BookIsExistInList(Book_Info * book)
{
	shared_ptr<Book_List> b_cur = b_first;
	while (b_cur != NULL)
	{
		if (b_cur->b_info.book_number == book->book_number)
			return true;
		b_cur = b_cur->b_next;
	}
	return false;
}

void Library::BookBTreeShow(BTreeNode * root, int depth)
{
	if (root == NULL)
		return;
	int n = root->num;									//结点元素个数
	while (n != 0)
	{
		if (root->ptr[n] != NULL)						//子树非空，递归打印子树
			BookBTreeShow(root->ptr[n], depth + 1);
		if (root->key[n] != NULL)						//打印元素
		{
			if (n > 0)
				for (int i = 0; i <= depth; i++)
					cout << "      ";
			cout << "---" << root->key[n]->book_number << endl;
		}
		n--;
	}
	if (root->ptr[0] != NULL)
	{
		BookBTreeShow(root->ptr[0], depth + 1);
		cout << endl;
	}
}

