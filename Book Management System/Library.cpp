#include <math.h>

#include "pch.h"
#include "Library.h"

using namespace std;

void Library::ImportBookData()
{
	cout << endl << endl << "==============================" << endl << endl;
	ifstream infile1("book data.dat", ios::in);

	shared_ptr<BookList> b_cur = nullptr;
	if (!infile1)
	{
		cerr << "<!>ͼ����Ϣ����ʧ�ܣ�" << endl;
	}
	else
	{
		while (!infile1.eof())
		{
			string b_number;				//���
			string b_name;					//����
			string b_author;				//����
			int b_exist;					//�ִ���
			int b_inventory;				//�����
			infile1 >> b_number >> b_name >> b_author >> b_exist >> b_inventory;

			// ɾ���ڵ�ʱ��Ҫ�ͷ��ڴ�
			auto newBook = make_shared<BookList>(b_number, b_name, b_author, b_exist, b_inventory);

			if (book_head_ == nullptr)
			{
				book_head_ = newBook;
				b_cur = book_head_;
			}
			else
			{
				b_cur->next = newBook;
				b_cur = b_cur->next;
			}
		}
		infile1.close();
		cout << "<!>ͼ����Ϣ����ɹ���" << endl;
	}
	cout << endl << "==============================" << endl;
}

void Library::ImportReaderData()
{
	cout << endl << endl << "==============================" << endl << endl;
	ifstream infile2("reader data.dat", ios::in);

	if (!infile2)
	{
		cerr << "<!>������Ϣ����ʧ�ܣ�" << endl;
	}
	else
	{
		shared_ptr<ReaderList> r_cur = nullptr;
		while (!infile2.eof())
		{
			string r_ID;				//ѧ��
			string r_name;				//����

			infile2 >> r_ID >> r_name;

			shared_ptr<ReaderList> newReader = make_shared<ReaderList>(r_ID, r_name);

			ImportBorrowData(newReader, r_ID);  // ����ö��ߵĽ�������

			if (reader_head_ == nullptr)
			{
				reader_head_ = newReader;
				r_cur = reader_head_;
			}
			else
			{
				r_cur->next = newReader;
				r_cur = r_cur->next;
			}
		}
	}
	infile2.close();
	cout << "<!>������Ϣ����ɹ���" << endl;
	cout << endl << "==============================" << endl;
}

void Library::ImportBorrowData(shared_ptr<ReaderList> new_reader, const string& id)
{
	// ����ö��߽�����Ϣ
	string r_b_file = "reader books ";
	string r_b_file_type = ".dat";
	r_b_file = r_b_file + id + r_b_file_type;
	ifstream infile3(r_b_file, ios::in);

	BorrowedBooks* r_b_cur = nullptr;  // ָ����ĵ�ͼ���ĩβ�ڵ�
	if (!infile3)
	{
		cerr << "<!>����" << r_b_file << "��ͼ�������Ϣ����ʧ�ܣ�" << endl;
	}
	while (!infile3.eof())
	{
		string r_b_number;				//���
		string r_b_name;				//����
		string r_b_author;				//����
		int r_b_borrow;					//������
		infile3 >> r_b_number >> r_b_name >> r_b_author >> r_b_borrow;

		BorrowedBooks* newBorBook = new BorrowedBooks(r_b_number, r_b_name, r_b_author, r_b_borrow);
		if (new_reader->reader_info.borrowed_head == NULL)
		{
			new_reader->reader_info.borrowed_head = newBorBook;
			r_b_cur = new_reader->reader_info.borrowed_head;
		}
		else
		{
			r_b_cur->next = newBorBook;
			r_b_cur = r_b_cur->next;
		}
	}
	infile3.close();
	cout << "<!>����" << id << "ͼ�������Ϣ����ɹ���" << endl;
}

void Library::BookListAdd(shared_ptr<BookList> newBook)
{
	shared_ptr<BookList> cur = book_head_;
	if (book_head_ == NULL) {
		book_head_ = newBook;
	}
	else {
		//�ж��Ƿ���ڸ�ͼ����Ϣ
		while (cur != NULL)
		{
			if (newBook->book_info.id == cur->book_info.id)
			{
				cur->book_info.exist += newBook->book_info.exist;
				cur->book_info.inventory += newBook->book_info.inventory;
				break;
			}
			else {
				if (cur->next == NULL) {
					cur->next = newBook;
					break;
				}
			}
			cur = cur->next;
		}
	}
}

void Library::BookListShow()
{
	if (book_head_ == nullptr)
	{
		cout << endl << "==============================" << endl;
		cout << endl << "<!>��ǰ���������ͼ�飡" << endl;
		cout << endl << "==============================" << endl;
	}
	else
	{
		auto cur = book_head_;
		cout.setf(ios::left | ios::unitbuf);						//����룬ÿ�������ˢ��������
		cout << endl << setw(70) << setfill('-') << "-" << setfill(' ') << endl;
		cout << setw(6) << "���" <<
			setw(30) << "����" <<
			setw(16) << "����" <<
			setw(10) << "�ִ���" <<
			setw(8) << "�ܿ����" << endl << endl;
		while (cur != nullptr)
		{
			cout << setw(6) << cur->book_info.id <<
				setw(30) << cur->book_info.name <<
				setw(16) << cur->book_info.author <<
				setw(10) << cur->book_info.exist <<
				setw(8) << cur->book_info.inventory << endl;
			cur = cur->next;
		}
		cout << setw(70) << setfill('-') << "-" << setfill(' ') << endl;
	}
}

// ͼ�����
void Library::BookFind()
{
	int sel;
	cout << "0.�������" << endl;
	cout << "1.B������" << endl;
	cout << "ѡ����ҷ�ʽ��";
	cin >> sel;

	cout << endl << "==============================" << endl;
	string info;
	cout << endl << "������ͼ��������Ϣ(��š�����������):";
	cin >> info;
	int seq = 0;  // ���
	vector<BookInfo*> books;  // ������ҽ����ָ������
	// �������
	if (sel == 0) {
		ListFind(books, info);
	}
	// B������
	else if (sel == 1) {
		BTreeEmpty();					//�ÿ�B��
		BTreeEstablish();				//����B��
		backtrackFind(btree_root, books, info);
	}
	//��ӡ���ҽ��
	if (!books.empty())
	{
		cout << endl << setw(72) << setfill('-') << "-" << setfill(' ') << endl;
		cout << endl << setw(6) << "���" <<
			setw(10) << "���" <<
			setw(20) << "����" <<
			setw(16) << "����" <<
			setw(10) << "�ִ���" <<
			setw(10) << "�ܿ����" << endl;
		for (int i = 0; i < books.size(); i++) {
			cout << setw(6) << i + 1 <<
				setw(10) << books[i]->id <<
				setw(20) << books[i]->name <<
				setw(16) << books[i]->author <<
				setw(10) << books[i]->exist <<
				setw(10) << books[i]->inventory << endl;
		}
		cout << endl << setw(72) << setfill('-') << "-" << setfill(' ') << endl;
	}
	else {
		cout << endl << "<!>û���ҵ����ͼ�飡" << endl;
		cout << endl << "==============================" << endl;
	}
}

// B���ݹ����
void Library::backtrackFind(BTreeNode* cur, vector<BookInfo*>& books, string info) {
	if (cur == nullptr) return;
	for (int i = 0; i <= cur->num; i++) {
		//�ݹ����
		backtrackFind(cur->ptr[i], books, info);
		if (i == 0) continue;//key[0]������
		if (cur->key[i]->id.find(info) != -1 ||
			cur->key[i]->name.find(info) != -1 ||
			cur->key[i]->author.find(info) != -1)
		{
			books.push_back(cur->key[i]);
		}
	}
}

// �������
void Library::ListFind(vector<BookInfo*>& books, string info)
{
	auto cur = book_head_;
	while (cur != NULL)
	{
		if (cur->book_info.id.find(info) != -1 || 
			cur->book_info.name.find(info) != -1 || 
			cur->book_info.author.find(info) != -1)
		{
			books.push_back(&cur->book_info);  // ����ͼ�����ڴ��еĵ�ַ
		}
		cur = cur->next;
	}
}

void Library::FuncEmpty()
{
	cout << endl << "==============================" << endl;

	int func;
	cout << endl << "��1�����ĳһ����Ŀ��" << endl;
	cout << "��2�����ͼ�������ͼ��" << endl;
	cout << "��0���������˵�" << endl << endl;
	cout << ">>>��ѡ��Ҫִ�еĹ���:";
	cin >> func;

	if (func == 0)
		return;
	else if (func == 1)
		BookRemove();
	else if (func == 2)
	{
		BookListEmpty();
		cout << endl;
		cout << "<!>��������գ�" << endl;
		BTreeEmpty();
		cout << "<!>B������գ�" << endl;
	}

	cout << endl << "==============================" << endl;
}

void Library::BookRemove()
{
	auto cur = book_head_;
	string info;
	vector<string> nums;
	int n = 0;
	cout << "������Ҫ�������ͼ��������Ϣ(��š�����������):";
	cin >> info;
	while (cur != NULL)
	{
		if (cur->book_info.id.find(info) != -1 || cur->book_info.name.find(info) != -1 || cur->book_info.author.find(info) != -1)
		{
			if (n == 0)
			{
				cout << endl << setw(76) << setfill('-') << "-" << setfill(' ') << endl;
				cout << setw(6) << "���" << 
					setw(6) << "���" <<
					setw(30) << "����" <<
					setw(16) << "����" <<
					setw(10) << "�ִ���" <<
					setw(8) << "�ܿ����" << endl << endl;
			}
			nums.push_back(cur->book_info.id);
			cout << setw(6) << ++n <<
				setw(6) << cur->book_info.id <<
				setw(30) << cur->book_info.name <<
				setw(16) << cur->book_info.author <<
				setw(10) << cur->book_info.exist <<
				setw(8) << cur->book_info.inventory << endl;
		}
		cur = cur->next;
	}
	if (n > 0)
		cout << setw(76) << setfill('-') << "-" << setfill(' ') << endl;
	else
	{
		cout << "<!>û���ҵ�����Ҫ�������ͼ����Ϣ��" << endl;
		return;
	}

	cur = book_head_;
	int num;
	cout << "������Ҫ�����ͼ������Ӧ�����:";
	while (cin >> num)
	{
		if (num > n) cout << "������������������:";
		else break;
	}
	// �׽ڵ����⴦��
	if (book_head_->book_info.id == nums[num - 1])
	{
		if (book_head_->book_info.exist != book_head_->book_info.inventory)
		{
			cout << endl << "<!>������ʧ�ܣ���ǰ���н����ͼ����δ�黹��" << endl;
		}
		else
		{
			// �����Զ��ͷ��ڴ棬����delete
			book_head_ = book_head_->next;
			cout << endl << "<!>����������" << endl;
		}
	}
	// �����ڵ�
	else
	{
		while (cur->next != NULL)
		{
			if (cur->next->book_info.id == nums[num - 1])
			{
				if (cur->next->book_info.exist != cur->next->book_info.inventory)
				{
					cout << endl << "<!>������ʧ�ܣ���ǰ���н����ͼ����δ�黹��" << endl;
					break;
				}
				else
				{
					cur->next = cur->next->next;
					// �����Զ��ͷ��ڴ棬����delete
					cout << endl << "<!>����������" << endl;
					break;
				}
			}
			cur = cur->next;
		}
	}
}

void Library::BookListEmpty()
{
	while (book_head_ != nullptr)
	{
		// ����ָ���Զ��ͷ��ڴ�
		book_head_ = book_head_->next;
	}
}

void Library::ReaderBooks()
{
	cout << endl << "==============================" << endl;
	int func;
	cout << endl;
	cout << "��1���鿴��ע�����" << endl;
	cout << "��2����ѯ�ѽ���ͼ��" << endl;
	cout << "��3���������˵�" << endl;
	cout << endl << ">>>��ѡ��Ҫִ�еĹ���:";
	L:cin >> func;

	//��������
	if (func != 0 && func != 1 && func != 2)
	{
		cout << "������������������:";
		goto L;
	}

	//�������˵�
	else if (func == 0)
	{
		cout << endl << "==============================" << endl;
		return;
	}

	//�鿴��ע�����
	else if (func == 1)
		ShowReaderList();

	//��ѯ�ѽ���ͼ��
	else
		ReaderBorrowed();
	cout << endl << "==============================" << endl;
}

void Library::ShowReaderList()
{
	cout.setf(ios::left | ios::unitbuf);  // ����룬ÿ�������ˢ��������
	if (reader_head_ == nullptr)
	{
		cout << "<!>��ǰ����ע�������Ϣ��" << endl;
		cout << endl << "==============================" << endl;
		return;
	}
	else {
		cout << endl << setw(20) << setfill('-') << "-" << setfill(' ') << endl;
		cout << setw(10) << "ѧ��" << setw(10) << "����" << endl << endl;

		shared_ptr<ReaderList> r_cur = reader_head_;
		while (r_cur != NULL)
		{
			cout << setw(10) << r_cur->reader_info.id << setw(10) << r_cur->reader_info.name << endl;
			r_cur = r_cur->next;
		}
		cout << setw(20) << setfill('-') << "-" << setfill(' ') << endl;
	}
}

void Library::ReaderBorrowed()
{
	if (reader_head_ == nullptr)
	{
		cout << "��ǰ����ע�������Ϣ��" << endl;
	}
	else
	{
		string ID;
		cout << endl << "����������ѧ��:";
		cin >> ID;
		shared_ptr<ReaderList> r_cur = reader_head_;
		bool isExist = false;
		while (r_cur != NULL)
		{
			if (r_cur->reader_info.id == ID)
			{
				isExist = true;
				cout << endl << "����ͼ�������Ϣ����:" << endl << endl;
				cout.setf(ios::left | ios::unitbuf);
				cout << "ѧ��:" << setw(10) << r_cur->reader_info.id << "����:" << setw(1) << r_cur->reader_info.name << endl;
				if (r_cur->reader_info.borrowed_head == NULL)
				{
					cout << endl << "<!>����ǰû�н����κ�ͼ�飡" << endl;
				}
				else
				{
					cout.setf(ios::left | ios::unitbuf);
					cout << setw(58) << setfill('-') << "-" << setfill(' ') << endl;
					cout << setw(6) << "���" << setw(10) << "���" << setw(20) <<
						"����" << setw(16) << "����" << setw(6) << "����" << endl << endl;
					BorrowedBooks *r_b_cur = r_cur->reader_info.borrowed_head;
					int i = 1;
					while (r_b_cur != NULL)
					{
						cout << setw(6) << i << setw(10) << r_b_cur->id << setw(20) << r_b_cur->name <<
							setw(16) << r_b_cur->author << setw(6) << r_b_cur->quantity << endl;
						i++;
						r_b_cur = r_b_cur->next;
					}
					cout << setw(58) << setfill('-') << "-" << setfill(' ') << endl;
				}
			}
			r_cur = r_cur->next;
		}
		if (isExist == false)
		{
			cout << endl << "<!>ѧ����Ϣ�����ڻ���������" << endl;
		}
	}
}

void Library::BookBorrow()
{
	cout << endl << "==============================" << endl << endl;
	shared_ptr<BookList> b_cur = book_head_;
	string info;
	vector<string> nums;
	int n = 0;
	cout << "������ͼ��������Ϣ(��š�����������):";
	cin >> info;
	bool isExist = false;
	while (b_cur != nullptr)
	{
		if (b_cur->book_info.id.find(info) != -1 || b_cur->book_info.name.find(info) != -1 || b_cur->book_info.author.find(info) != -1)
		{
			isExist = true;
			if (n == 0)
			{
				cout << endl << "��Ϊ���ҵ�����ͼ��:" << endl;
				cout << setw(72) << setfill('-') << "-" << setfill(' ') << endl;
				cout << setw(6) << "���" <<
					setw(10) << "���" <<
					setw(20) << "����" <<
					setw(16) << "����" <<
					setw(10) << "�ִ���" <<
					setw(10) << "�ܿ����" << endl;
			}
			nums.push_back(b_cur->book_info.id);
			cout << setw(6) << n + 1 <<
				setw(10) << b_cur->book_info.id <<
				setw(20) << b_cur->book_info.name <<
				setw(16) << b_cur->book_info.author <<
				setw(10) << b_cur->book_info.exist <<
				setw(10) << b_cur->book_info.inventory << endl;
			n++;
		}
		b_cur = b_cur->next;
	}
	if (isExist == false)
	{
		cout << endl << "<!>û���ҵ����ͼ����Ϣ��" << endl;
		return;
	}
	else
	{
		cout << setw(72) << setfill('-') << "-" << setfill(' ') << endl << endl;

		b_cur = book_head_;
		int num;
		cout << "������Ҫ���ĵ�ͼ������Ӧ�����:";
		while (cin >> num)
		{
			if (num > n) break;
			cout << "������������������:";
		}
		while (b_cur != nullptr)
		{
			if (b_cur->book_info.id == nums[num - 1])
			{
				cout << "��Ҫ���ĵ�ͼ����Ϣ����:" << endl << endl;
				cout << "���:" << b_cur->book_info.id << endl;
				cout << "����:" << b_cur->book_info.name << endl;
				cout << "����:" << b_cur->book_info.name << endl;
				cout << "�ִ���:" << b_cur->book_info.exist << endl;
				cout << "�ܿ��:" << b_cur->book_info.inventory << endl;
				int qua = 0;
				cout << endl << "��������Ҫ���ĵ�����:";
				while (cin >> qua)
				{
					if (qua < b_cur->book_info.exist) break;
					cout << "�ݴ��������㣬����������ģ�����������:";
				}
				if (qua <= 0)
					break;
				else
				{
					auto r_cur = reader_head_;			//ָ��ǰ����
					string ID;
					string name;
					cout << "����������ѧ��:";
					cin >> ID;
					cout << "��������������:";
					cin >> name;

					auto newReader = make_shared<ReaderList>(ID, name);
					BorrowedBooks *newBorBook = new BorrowedBooks(b_cur->book_info.id, b_cur->book_info.name, b_cur->book_info.author, qua);

					if (reader_head_ == nullptr)  // ������Ϣ��Ϊ�գ���ֱ����Ӹö����Լ����ĵ�ͼ��
					{
						reader_head_ = newReader;
						reader_head_->reader_info.borrowed_head = newBorBook;
						b_cur->book_info.exist -= qua;  // ��ȥ���ĵ�����
					}
					else									//�����ж��Ƿ���ڸö�����Ϣ
					{
						bool exist = false;   // �Ѵ��ڸö�����Ϣ
						while (r_cur != nullptr)
						{
							if (r_cur->reader_info.id == ID)  // ˵���Ѵ��ڸö�����Ϣ
							{
								exist = true;
								if (r_cur->reader_info.borrowed_head == nullptr)
								{
									r_cur->reader_info.borrowed_head = newBorBook;  // û�н��Ĺ�ͼ��
									break;
								}
								else {
									BorrowedBooks *borbook_cur = r_cur->reader_info.borrowed_head;		//ָ��ǰ���ߵĵ�ǰͼ��
									bool borrowed = false;
									while (borbook_cur != nullptr)
									{
										if (b_cur->book_info.id == borbook_cur->id)
										{
											borrowed = true;
											b_cur->book_info.exist -= qua;				//ͼ��ݸ����ִ�����qua
											borbook_cur->id += qua;				//�ö��߽��ĵĸ�ͼ������qua
											break;
										}
										borbook_cur = borbook_cur->next;
									}
									if (!borrowed)  // �ö���û�н��Ĺ��Ȿ��
									{
										borbook_cur->next = newBorBook;
										b_cur->book_info.exist -= qua;  // ��ȥ�������
									}
								}
								break;
							}
							r_cur = r_cur->next;
						}
						if (!exist)  // �����ڸö��ߵ������Ϣ
						{
							r_cur->next = newReader;
							r_cur->next->reader_info.borrowed_head = newBorBook;		//�½����߽��ĵ�ͼ����Ϣ	
							b_cur->book_info.exist -= qua;
							break;
						}
					}
				}
				break;  // �Ѿ���ͼ�������ҵ����Ȿ�飬ִ����Ӧ������������ѭ��
			}
			b_cur = b_cur->next;
		}
	}
	cout << endl << "<!>ͼ����ĳɹ���" << endl;
	cout << endl << "==============================" << endl;
}

void Library::BookReturn()
{
	cout << endl << "==============================" << endl << endl;
	if (reader_head_ == nullptr)
		cout << "��ǰû����ע��ѧ����Ϣ��" << endl;
	else
	{
		string ID;
		cout << "����������ѧ��:";
		cin >> ID;
		auto r_cur = reader_head_;  // ��ǰ����
		bool isExist = false;
		while (r_cur != nullptr)
		{
			if (r_cur->reader_info.id == ID)
			{
				isExist = true;
				cout.setf(ios::left | ios::unitbuf);
				cout << "ѧ��:" << setw(10) << r_cur->reader_info.id << "����:" << setw(10) << r_cur->reader_info.name << endl;
				if (r_cur->reader_info.borrowed_head == nullptr)
				{
					cout << "<!>����ǰû�н����κ�ͼ�飡" << endl;
					break;
				}
				else
				{
					// ��ӡ�ö��ߵ�ǰ���ĵ�����ͼ��
					cout.setf(ios::left | ios::unitbuf);
					cout << endl << setw(58) << setfill('-') << "-" << setfill(' ') << endl;
					cout << setw(6) << "���" << setw(10) << "���" << setw(20) <<
						"����" << setw(16) << "����" << setw(6) << "����" << endl << endl;
					BorrowedBooks *r_b_cur = r_cur->reader_info.borrowed_head;  // ��ǰ�ĸö��߽��ĵ�ͼ��
					int n = 1;
					vector<string> nums;
					while (r_b_cur != nullptr)
					{
						cout << setw(6) << n << setw(10) << r_b_cur->id << setw(20) << r_b_cur->name <<
							setw(16) << r_b_cur->author << setw(6) << r_b_cur->quantity << endl;
						nums.push_back(r_b_cur->id);
						n++;
						r_b_cur = r_b_cur->next;
					}
					cout << setw(58) << setfill('-') << "-" << setfill(' ') << endl << endl;

					// ѡ��Ҫ�黹��ͼ�鲢�黹
					int index;
					cout << "��ѡ����Ҫ�黹��ͼ��:";
					while (cin >> index)
					{
						if (index >= 1 && index < n) break;
						cout << "������������������:";
					}
					int quantity;
					cout << "������Ҫ�黹������:";
					while (cin >> quantity)
					{
						if (quantity >= 0 && quantity <= r_b_cur->quantity) break;
						cout << "������������������:";
					}
					// Ҫ�黹����ͷ����ͼ��
					if (r_cur->reader_info.borrowed_head->id == nums[index - 1])
					{
						if (quantity == r_b_cur->quantity)			//��ոö��߽���ͼ���е��Ȿͼ��
						{
							BorrowedBooks* tmp = r_cur->reader_info.borrowed_head;
							r_cur->reader_info.borrowed_head = r_cur->reader_info.borrowed_head->next;  // �ƶ�ͷָ��
							delete tmp;  // �ͷ��ڴ�
						}
						else r_cur->reader_info.borrowed_head->quantity -= quantity;  // ��ȥ�黹ͼ�������
					}
					// Ҫ�黹�Ĳ���ͷ����ͼ�飬��Ҫ�ҵ�ǰһ�����
					else
					{
						r_b_cur = r_cur->reader_info.borrowed_head;  // �޸�ָ��ָ����ĵĵ�һ��ͼ��
						while (r_b_cur->next != nullptr)
						{
							if (r_b_cur->next->id == nums[index - 1])
								break;
							r_b_cur = r_b_cur->next;
						}
						if (quantity == r_b_cur->next->quantity)  // ��ոö��߽���ͼ���е��Ȿͼ��
						{
							BorrowedBooks* tmp = r_b_cur->next;
							r_b_cur->next = r_b_cur->next->next;  // �޸�ָ��ָ��
							delete tmp;  // �ͷ��ڴ�
						}
						else r_b_cur->next->quantity -= quantity;  // ��ȥ�黹ͼ�������
					}

					// ���ӹ黹��ͼ������
					auto b_cur = book_head_;
					bool exist = false;
					while (b_cur != nullptr)
					{
						if (b_cur->book_info.id == nums[index - 1])
						{
							exist = true;
							b_cur->book_info.exist += quantity;
							cout << endl << "<!>ͼ���ѳɹ��黹��" << endl;
							break;
						}
						b_cur = b_cur->next;
					}
					if (!exist)
					{
						cout << endl << "<!>ͼ��黹ʧ�ܣ�ͼ�����û���Ȿ�����Ϣ��" << endl;
					}
				}
				break;
			}
			r_cur = r_cur->next;
		}
		if (!isExist) cout << "ϵͳ�в��������������Ϣ��" << endl;
	}
	cout << endl << "==============================" << endl;
}

void Library::SaveData()
{
	cout << endl << "==============================" << endl << endl;
	ofstream outfile1("book data.dat", ios::out);
	auto b_cur = book_head_;

	if (!outfile1)
	{
		cerr << "<!>ͼ����Ϣ����ʧ�ܣ�" << endl;
		exit(1);
	}

	while (b_cur != nullptr)
	{
		outfile1.setf(ios::right | ios::unitbuf);  // �Ҷ��룬ÿ�������ˢ��������
		outfile1 << setw(6) << b_cur->book_info.id <<
			setw(30) << b_cur->book_info.name <<
			setw(16) << b_cur->book_info.author <<
			setw(10) << b_cur->book_info.exist <<
			setw(10) << b_cur->book_info.inventory;
		if (b_cur->next != nullptr) outfile1 << endl;
		b_cur = b_cur->next;
	}
	outfile1.close();
	cout << "<!>ͼ����Ϣ����ɹ���" << endl;

	ofstream outfile2("reader data.dat", ios::out);
	if (!outfile2)
	{
		cerr << "<!>������Ϣ����ʧ�ܣ�" << endl;
		exit(1);
	}
	auto r_cur = reader_head_;
	while (r_cur != nullptr)
	{
		outfile2.setf(ios::right | ios::unitbuf);  // �Ҷ��룬ÿ�������ˢ��������
		outfile2 << setw(10) << r_cur->reader_info.id << setw(20) << r_cur->reader_info.name;
		if (r_cur->reader_info.borrowed_head != nullptr)
		{
			string r_b_file = "reader books ";
			string r_b_file_type = ".dat";
			r_b_file = r_b_file + r_cur->reader_info.id + r_b_file_type;
			
			ofstream outfile3(r_b_file, ios::out);
			if (!outfile3)
			{
				cerr << "<!>���߽�����Ϣ����ʧ�ܣ�" << endl;
				exit(1);
			}
			BorrowedBooks *r_b_cur = r_cur->reader_info.borrowed_head;
			while (r_b_cur != nullptr)
			{
				outfile3.setf(ios::right | ios::unitbuf);  // �Ҷ��룬ÿ�������ˢ��������
				outfile3 << setw(6) << r_b_cur->id <<
					setw(30) << r_b_cur->name <<
					setw(10) << r_b_cur->author <<
					setw(4) << r_b_cur->quantity;
				if (r_b_cur->next != nullptr) outfile3 << endl;
				r_b_cur = r_b_cur->next;
			}
			outfile3.close();
			cout << "<!>����" << r_cur->reader_info.id << "�Ľ�����Ϣ����ɹ���" << endl;
		}
		if (r_cur->next != nullptr) outfile2 << endl;
		r_cur = r_cur->next;
	}
	outfile2.close();
	cout << "<!>������Ϣ����ɹ���" << endl;
	cout << endl << "==============================" << endl;
}

void Library::BTreeEmpty()
{
	// Ӧ�ñ���2-3-4���ͷ��ڴ�
	BTreeNode* tmp = btree_root;
	btree_root = NULL;
	delete tmp;
}

bool Library::BookIsExistInBTree(BTreeNode * loc, BookInfo & book)
{
	if (loc == NULL)
		return false;
	for (int i = 0; i < loc->num; i++)
	{
		if (book.id == loc->key[i + 1]->id)
			return true;
	}
	return false;
}

//��λԪ�أ����B��Ϊ���򷵻�nullptr�����򷵻����Ľ��λ��
BTreeNode * Library::BTreeLocate(BookInfo & book)
{
	BTreeNode *btree_cur = btree_root;
	while (btree_cur != NULL)
	{
		for (int i = 0; i < btree_cur->num; i++)
		{
			//Ԫ���Ѵ���
			if (book.id == btree_cur->key[i + 1]->id)
				return btree_cur;
			
			//Ԫ��[i+1]�������
			if (book.id < btree_cur->key[i + 1]->id)
			{
				//���btree_cur->ptr[i] == NULL˵��234���в����ڸ�Ԫ�أ�ͼ�飩
				if (btree_cur->ptr[i] == NULL)
					return btree_cur;
				else
				{
					btree_cur = btree_cur->ptr[i];
					break;
				}
			}

			//���Ҳ���
			else if (i == btree_cur->num - 1)
			{
				//���btree_cur->ptr[i] == NULL˵��234���в����ڸ�Ԫ�أ�ͼ�飩
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
	cout << "<!>��ʼ����������" << endl << endl;
	shared_ptr<BookList> b_cur = book_head_;
	if (book_head_ == NULL)
	{
		cout << "<!>ͼ����ϢΪ�գ�" << endl;
		return;
	}
	else
	{
		while (b_cur != NULL)
		{
			BTreeNode * loc = BTreeLocate(b_cur->book_info);		//ָ��ǰ���

			//��Ԫ�أ�ͼ�飩�Ѵ���
			if (BookIsExistInBTree(loc, b_cur->book_info))
			{
				cout << "- ��� " << b_cur->book_info.id << " ��ͼ�顶" << b_cur->book_info.name << "���Ѵ��ڣ��������" << endl << endl;
				b_cur = b_cur->next;
				continue;
			}

			//����ǰ�����뵽234����
			else
			{
				cout << "- ��� " << b_cur->book_info.id << " ��ͼ�顶" << b_cur->book_info.name << "���������У��������Ԫ��" << endl;
				BTreeInsert(b_cur, loc);
				cout << "- ��� " << b_cur->book_info.id << " ��ͼ�顶" << b_cur->book_info.name << "���ѳɹ�����B��" << endl << endl;
			}
			b_cur = b_cur->next;
		}
	}
	cout << endl << "<!>B����234���������ɹ���" << endl << endl;
	cout << endl << "==============================" << endl << endl;
}

void Library::BookShow()
{
	cout << endl << "==============================" << endl << endl;

	int fun;
	cout << "��1���б���ʾ" << endl;
	cout << "��2��B����ʾ" << endl;
	cout << "��0���������˵�" << endl;
	cout << endl << ">>>��ѡ����ʾģʽ:";
Label:cin >> fun;
	if (fun == 0)
		return;
	else if (fun == 1)
		BookListShow();
	else if (fun == 2)
	{
		BTreeEmpty();					//�ÿ�B��
		BTreeEstablish();				//����B��
		BookBTreeShow(btree_root, 0);	//���B��
	}
	else
	{
		cout << "������������������:";
		goto Label;
	}
	cout << endl << "==============================" << endl;
}

void Library::BookAdd()
{
	cout << endl << endl << "==============================" << endl;

	string number;				//���
	string name;				//����
	string author;				//����
	int quantity;				//����

	cout << endl;
	cout << "���������:";
	cin >> number;
	cout << "����������:";
	cin >> name;
	cout << "����������:";
	cin >> author;
	cout << "����������:";
	cin >> quantity;

	// ��ͼ�飬ע���ͷ��ڴ�
	auto newBook = make_shared<BookList>(number, name, author, quantity);

	//��ӵ�ͼ��������
	BookListAdd(newBook);
	cout << endl << "<!> �ѳɹ���ӵ������У�" << endl;

	//���뵽B����
	BTreeInsert(newBook, BTreeLocate(newBook->book_info));
	cout << endl << "<!> �ѳɹ���ӵ�B���У�" << endl;

	cout << endl << "<!> ͼ�����ɹ���" << endl;
	cout << endl << "==============================" << endl;
}

//ǰ������֪node���Ԫ��δ����ֱ�Ӳ���
//���÷��ѽڵ�������ֱ�Ӳ���Ԫ��
BTreeNode *Library::InsertEleDirect(BTreeNode * node, BTreeNode * book)
{
	//��λ�����뵽key[i]
	int i;
	for (i = 0; i < node->num; i++)
	{
		if (book->key[1]->id < node->key[i + 1]->id)
			break;
		else if (book->key[1]->id > node->key[i + 1]->id)
		{
			//ֱ�Ӳ��뵽ĩβ
			if (i == node->num - 1)
			{
				i = i + 2;
				node->key[i] = new BookInfo(book->key[1]);
				node->ptr[i - 1] = book->ptr[0];
				node->ptr[i] = book->ptr[1];
				node->num++;
				return node;
			}
			continue;
		}
	}

	int j;
	//Ԫ�غ���
	for (j = node->num + 1; j > i; j--)
	{
		node->key[j] = node->key[j - 1];
		node->ptr[j] = node->ptr[j - 1];
	}
	//����Ԫ��
	node->key[j + 1] = book->key[1];
	node->ptr[j] = book->ptr[0];
	node->ptr[j + 1] = book->ptr[1];
	node->num++;
	return node;
}

//��loc��ָ��������ͼ��book
void Library::BTreeInsert(shared_ptr<BookList> book, BTreeNode * loc)
{
	BTreeNode * loc_parent;					//ָ��ǰ���ĸ����
	BTreeNode * newbook;					//��Ԫ�ؽ��
	BTreeNode * newBTreeNode = NULL;		//����Ԫ�ؽ��

	newbook = new BTreeNode(&book->book_info);		//��ֵ��ʼ��

Label:
	//���locΪ�գ���234����ָ��Ϊ�գ�B��Ϊ�գ��򽫸�ָ��ָ���½ڵ�
	if (loc == NULL)
	{
		if (newBTreeNode == NULL)
			loc = newbook;
		else
			loc = newBTreeNode;
		btree_root = loc;
		book = book->next;
		return;
	}

	//loc�ǿգ�����loc��ָ��������Ԫ��
	else
	{
		//�����ǰ���δ��3��Ԫ�أ��򽫸�Ԫ�ز��뵽key[j]֮ǰ
		if (loc->num < m - 1)
		{
			loc = InsertEleDirect(loc, newbook);
			for (int i = 0; i <= loc->num; i++)
			{
				if (loc->ptr[i] == NULL)
					continue;
				loc->ptr[i]->parent = loc;
			}
			return;			//�Ѳ���ɹ�����������
		}

		//��ǰ�������3��Ԫ�أ���Ҫ���ѽ��
		else
		{
			//int up = ceil((i + 1) / 2.0);				//ȡ(i+1)/2����������Ӧ��Ԫ�ؼ�loc->key[up]����
			int up = 2;									//Ĭ�Ͻ��м��Ԫ�ؼ�loc->key[2]����
			//�½�һ��BTreeNode *ָ��ָ��Ҫ�����Ԫ��
			newBTreeNode = new BTreeNode(loc->key[up]);

			newBTreeNode->ptr[0] = new BTreeNode();
			newBTreeNode->ptr[1] = loc;

			//Ϊ0���������룬Ϊ1����������
			int left_right = (loc->key[up]->id) > (newbook->key[1]->id) ? 0 : 1;

			//�������������
			newBTreeNode->ptr[0]->num = up - 1;
			newBTreeNode->ptr[0]->parent = newBTreeNode;
			for (int k = 0; k < up; k++)
			{
				newBTreeNode->ptr[0]->ptr[k] = loc->ptr[k];
				if (k == 0)
					continue;
				newBTreeNode->ptr[0]->key[k] = new BookInfo(loc->key[k]);
			}

			//���뵽���ӽڵ���
			if (left_right == 0)
				newBTreeNode->ptr[0] = InsertEleDirect(newBTreeNode->ptr[0], newbook);

			//�������������
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
					loc->key[k - up] = new BookInfo(loc->key[k]);
					loc->ptr[k - up] = loc->ptr[k];
					loc->key[k] = NULL;
					loc->ptr[k] = NULL;
				}
			}
			loc->key[0] = NULL;
			loc->num -= up;

			//���뵽���ӽڵ���
			if (left_right == 1)
				newBTreeNode->ptr[1] = InsertEleDirect(newBTreeNode->ptr[1], newbook);

			//newBTreeNode��Ϊ��Ԫ������һ�����
			newbook = newBTreeNode;
			loc = loc_parent;
			goto Label;
		}
	}
}

//�жϸ�ͼ���Ƿ��Ѵ�����ͼ��������
bool Library::BookIsExistInList(BookInfo * book)
{
	shared_ptr<BookList> b_cur = book_head_;
	while (b_cur != NULL)
	{
		if (b_cur->book_info.id == book->id)
			return true;
		b_cur = b_cur->next;
	}
	return false;
}

void Library::BookBTreeShow(BTreeNode * root, int depth)
{
	if (root == NULL)
		return;
	int n = root->num;									//���Ԫ�ظ���
	while (n != 0)
	{
		if (root->ptr[n] != NULL)						//�����ǿգ��ݹ��ӡ����
			BookBTreeShow(root->ptr[n], depth + 1);
		if (root->key[n] != NULL)						//��ӡԪ��
		{
			if (n > 0)
				for (int i = 0; i <= depth; i++)
					cout << "      ";
			cout << "---" << root->key[n]->id << endl;
		}
		n--;
	}
	if (root->ptr[0] != NULL)
	{
		BookBTreeShow(root->ptr[0], depth + 1);
		cout << endl;
	}
}

