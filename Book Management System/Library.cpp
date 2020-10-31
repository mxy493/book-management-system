#include <math.h>

#include "pch.h"
#include "Library.h"

using namespace std;

void Library::ImportBookData()
{
	cout << endl << endl << "==============================" << endl << endl;
	ifstream infile1("book data.dat", ios::in);

	Book_List* b_cur = nullptr;
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
			Book_List* newBook = new Book_List(b_number, b_name, b_author, b_exist, b_inventory);

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
		Reader_List* r_cur = nullptr;
		while (!infile2.eof())
		{
			string r_ID;				//ѧ��
			string r_name;				//����

			infile2 >> r_ID >> r_name;

			Reader_List* newReader = new Reader_List(r_ID, r_name);

			ImportBorrowData(newReader, r_ID);  // ����ö��ߵĽ�������

			if (r_first == NULL)
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
	cout << "<!>������Ϣ����ɹ���" << endl;
	cout << endl << "==============================" << endl;
}

void Library::ImportBorrowData(Reader_List* const new_reader, const string& reader_id)
{
	// ����ö��߽�����Ϣ
	string r_b_file = "reader books ";
	string r_b_file_type = ".dat";
	r_b_file = r_b_file + reader_id + r_b_file_type;
	ifstream infile3(r_b_file, ios::in);

	Reader_Books* r_b_cur = nullptr;  // ָ����ĵ�ͼ���ĩβ�ڵ�
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
	cout << "<!>����" << reader_id << "ͼ�������Ϣ����ɹ���" << endl;
}

void Library::BookListAdd(Book_List * newBook)
{
	Book_List *cur = b_first;
	if (b_first == NULL) {
		b_first = newBook;
	}
	else {
		//�ж��Ƿ���ڸ�ͼ����Ϣ
		while (cur != NULL)
		{
			if (newBook->b_info.book_number == cur->b_info.book_number) {
				cur->b_info.book_exist += newBook->b_info.book_exist;
				cur->b_info.book_inventory += newBook->b_info.book_inventory;
				break;
			}
			else {
				if (cur->b_next == NULL) {
					newBook->b_next = cur->b_next;
					cur->b_next = newBook;
					break;
				}
				else {
					cur = cur->b_next;
				}
			}
		}
	}
}

void Library::BookListShow()
{
	if (b_first == NULL)
	{
		cout << endl << "==============================" << endl;
		cout << endl << "<!>��ǰ���������ͼ�飡" << endl;
		cout << endl << "==============================" << endl;
	}
	else
	{
		Book_List *cur = b_first;
		cout.setf(ios::left | ios::unitbuf);						//����룬ÿ�������ˢ��������
		cout << endl << setw(70) << setfill('-') << "-" << setfill(' ') << endl;
		cout << setw(6) << "���" <<
			setw(30) << "����" <<
			setw(16) << "����" <<
			setw(10) << "�ִ���" <<
			setw(8) << "�ܿ����" << endl << endl;
		while (cur != NULL)
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

//B������
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
	int seq = 0;//���
	vector<Book_Info*> books;//������ҽ��
	//�������
	if (sel == 0) {
		ListFind(books, info);
	}
	//B������
	else if (sel == 1) {
		BTreeEmpty();					//�ÿ�B��
		BTreeEstablish();				//����B��
		backtrackFind(btree_root, books, info);
	}
	//��ӡ���ҽ��
	for (int i = 0; i < books.size(); i++) {
		if (i == 0) {
			cout << endl << setw(72) << setfill('-') << "-" << setfill(' ') << endl;
			cout << endl << setw(6) << "���" <<
				setw(10) << "���" <<
				setw(20) << "����" <<
				setw(16) << "����" <<
				setw(10) << "�ִ���" <<
				setw(10) << "�ܿ����" << endl;
		}
		cout << setw(6) << i + 1 <<
			setw(10) << books[i]->book_number <<
			setw(20) << books[i]->book_name <<
			setw(16) << books[i]->book_author <<
			setw(10) << books[i]->book_exist <<
			setw(10) << books[i]->book_inventory << endl;
	}

	if (!books.empty())
		cout << endl << setw(72) << setfill('-') << "-" << setfill(' ') << endl;
	else {
		cout << endl << "<!>û���ҵ����ͼ�飡" << endl;
		cout << endl << "==============================" << endl;
	}
}

//B���ݹ����
void Library::backtrackFind(BTreeNode* cur, vector<Book_Info*>& books, string info) {
	if (cur == NULL) return;
	for (int i = 0; i <= cur->num; i++) {
		//�ݹ����
		backtrackFind(cur->ptr[i], books, info);
		if (i == 0) continue;//key[0]������
		if (cur->key[i]->book_number.find(info) != -1 ||
			cur->key[i]->book_name.find(info) != -1 ||
			cur->key[i]->book_author.find(info) != -1)
		{
			books.push_back(cur->key[i]);
		}
	}
}

//�������
void Library::ListFind(vector<Book_Info*>& books, string info)
{
	Book_List* cur = b_first;
	while (cur != NULL)
	{
		if (cur->b_info.book_number.find(info) != -1 || 
			cur->b_info.book_name.find(info) != -1 || 
			cur->b_info.book_author.find(info) != -1)
		{
			books.push_back(&cur->b_info);
		}
		cur = cur->b_next;
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
	Book_List *cur = b_first;
	string info;
	vector<string> nums;
	int n = 0;
	cout << "������Ҫ�������ͼ��������Ϣ(��š�����������):";
	cin >> info;
	bool isExist = false;
	while (cur != NULL)
	{
		if (cur->b_info.book_number.find(info) != -1 || cur->b_info.book_name.find(info) != -1 || cur->b_info.book_author.find(info) != -1)
		{
			isExist = true;
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
			nums.push_back(cur->b_info.book_number);
			cout << setw(6) << n + 1 <<
				setw(6) << cur->b_info.book_number <<
				setw(30) << cur->b_info.book_name <<
				setw(16) << cur->b_info.book_author <<
				setw(10) << cur->b_info.book_exist <<
				setw(8) << cur->b_info.book_inventory << endl;
			n++;
		}
		cur = cur->b_next;
	}
	if (isExist == true)
		cout << setw(76) << setfill('-') << "-" << setfill(' ') << endl;
	else
	{
		cout << "<!>û���ҵ�����Ҫ�������ͼ����Ϣ��" << endl;
		return;
	}

	cur = b_first;
	Book_List *del;
	int num;
label:cout << "������Ҫ�����ͼ������Ӧ�����:";
	cin >> num;
	if (num > n)
	{
		cout << "������������������:";
		goto label;
	}
	if (b_first->b_info.book_number == nums[num - 1])
	{
		if (b_first->b_info.book_exist != b_first->b_info.book_inventory)
		{
			cout << endl << "<!>������ʧ�ܣ���ǰ���н����ͼ����δ�黹��" << endl;
		}
		else
		{
			del = b_first;
			b_first = b_first->b_next;
			delete cur;
			cout << endl << "<!>����������" << endl;
	}
	}
	else while (cur->b_next != NULL)
	{
		if (cur->b_next->b_info.book_number == nums[num - 1])
		{
			if (b_first->b_info.book_exist != b_first->b_info.book_inventory)
			{
				cout << endl << "<!>������ʧ�ܣ���ǰ���н����ͼ����δ�黹��" << endl;
				break;
			}
			else
			{
				del = cur->b_next;
				cur->b_next = del->b_next;
				delete del;
				cout << endl << "<!>����������" << endl;
				break;
			}
		}
		cur = cur->b_next;
	}
}

void Library::BookListEmpty()
{
	b_first = NULL;
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
		ReaderList();

	//��ѯ�ѽ���ͼ��
	else
		ReaderBorrowed();
	cout << endl << "==============================" << endl;
}

void Library::ReaderList()
{
	Reader_List *r_cur = r_first;
	cout.setf(ios::left | ios::unitbuf);						//����룬ÿ�������ˢ��������
	if (r_first == NULL)
	{
		cout << "<!>��ǰ����ע�������Ϣ��" << endl;
		cout << endl << "==============================" << endl;
		return;
	}
	else {
		if (r_cur == r_first)
		{
			cout << endl << setw(20) << setfill('-') << "-" << setfill(' ') << endl;
			cout << setw(10) << "ѧ��" << setw(10) << "����" << endl << endl;
		}
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
	if (r_first == NULL)
	{
		cout << "��ǰ����ע�������Ϣ��" << endl;
	}
	else
	{
		string ID;
		cout << endl << "����������ѧ��:";
		cin >> ID;
		Reader_List *r_cur = r_first;
		bool isExist = false;
		while (r_cur != NULL)
		{
			if (r_cur->r_info.reader_ID == ID)
			{
				isExist = true;
				cout << endl << "����ͼ�������Ϣ����:" << endl << endl;
				cout.setf(ios::left | ios::unitbuf);
				cout << "ѧ��:" << setw(10) << r_cur->r_info.reader_ID << "����:" << setw(1) << r_cur->r_info.reader_name << endl;
				if (r_cur->r_info.borbook == NULL)
					cout << endl << "<!>����ǰû�н����κ�ͼ�飡" << endl;
				else
				{
					cout.setf(ios::left | ios::unitbuf);
					cout << setw(58) << setfill('-') << "-" << setfill(' ') << endl;
					cout << setw(6) << "���" << setw(10) << "���" << setw(20) <<
						"����" << setw(16) << "����" << setw(6) << "����" << endl << endl;
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
			cout << endl << "<!>ѧ����Ϣ�����ڻ���������" << endl;
		}
	}
}

void Library::BookBorrow()
{
	cout << endl << "==============================" << endl << endl;
	Book_List *b_cur = b_first;
	string info;
	vector<string> nums;
	int n = 0;
	cout << "������ͼ��������Ϣ(��š�����������):";
	cin >> info;
	bool isExist = false;
	while (b_cur != NULL)
	{
		if (b_cur->b_info.book_number.find(info) != -1 || b_cur->b_info.book_name.find(info) != -1 || b_cur->b_info.book_author.find(info) != -1)
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
		cout << endl << "<!>û���ҵ����ͼ����Ϣ��" << endl;
		return;
	}
	else
	{
		cout << setw(72) << setfill('-') << "-" << setfill(' ') << endl << endl;

		b_cur = b_first;
		int num;
		cout << "������Ҫ���ĵ�ͼ������Ӧ�����:";
	L1:cin >> num;
		if (num > n)
		{
			cout << "������������������:";
			goto L1;
		}
		while (b_cur != NULL)
		{
			if (b_cur->b_info.book_number == nums[num - 1])
			{
				cout << "��Ҫ���ĵ�ͼ����Ϣ����:" << endl << endl;
				cout << "���:" << b_cur->b_info.book_number << endl;
				cout << "����:" << b_cur->b_info.book_name << endl;
				cout << "����:" << b_cur->b_info.book_name << endl;
				cout << "�ִ���:" << b_cur->b_info.book_exist << endl;
				cout << "�ܿ��:" << b_cur->b_info.book_inventory << endl;
				int qua = 0;
				cout << endl << "��������Ҫ���ĵ�����:";
			L2:cin >> qua;
				if (qua <= 0)
					break;
				else if (qua > b_cur->b_info.book_exist)
				{
					cout << "�ݴ��������㣬����������ģ�����������:";
					goto L2;
				}
				else
				{
					Reader_List *r_cur = r_first;			//ָ��ǰ����
					string ID;
					string name;
					cout << "����������ѧ��:";
					cin >> ID;
					cout << "��������������:";
					cin >> name;

					Reader_List *newReader = new Reader_List(ID, name);
					Reader_Books *newBorBook = new Reader_Books(b_cur->b_info.book_number, b_cur->b_info.book_name, b_cur->b_info.book_author, qua);

					if (r_first == NULL)					//������Ϣ��Ϊ�գ���ֱ����Ӹö����Լ����ĵ�ͼ��
					{
						r_first = newReader;
						r_first->r_info.borbook = newBorBook;
						b_cur->b_info.book_exist -= qua;
					}
					else									//�����ж��Ƿ���ڸö�����Ϣ
					{
						while (r_cur != NULL)
						{
							if (ID == r_cur->r_info.reader_ID)			//˵���Ѵ��ڸö�����Ϣ
							{
								if (r_cur->r_info.borbook == NULL)		//���ĵ�ͼ��ͷָ��Ϊ��
								{
									r_cur->r_info.borbook = newBorBook;
									break;
								}
								else {
									Reader_Books *borbook_cur = r_cur->r_info.borbook;		//ָ��ǰ���ߵĵ�ǰͼ��
									while (borbook_cur != NULL)
									{
										if (b_cur->b_info.book_number == borbook_cur->borbook_number)
										{
											b_cur->b_info.book_exist -= qua;				//ͼ��ݸ����ִ�����qua
											borbook_cur->borbook_number += qua;				//�ö��߽��ĵĸ�ͼ������qua
											break;
										}
										else
										{
											if (borbook_cur->next == NULL)					//�ö���û�н��Ĺ��Ȿ��
											{
												newBorBook->next = borbook_cur->next;		//���ĵ�ͼ�������β�½�ͼ����Ϣ
												borbook_cur->next = newBorBook;
												b_cur->b_info.book_exist -= qua;
												break;
											}
											else
												borbook_cur = borbook_cur->next;
										}
									}
								}
								break;
							}
							else
								if (r_cur->r_next == NULL)							//�����ڸö��ߵ������Ϣ
								{
									newReader->r_next = r_cur->r_next;				//����β�½�������Ϣ
									r_cur->r_next = newReader;
									r_cur->r_next->r_info.borbook = newBorBook;		//�½����߽��ĵ�ͼ����Ϣ	
									b_cur->b_info.book_exist -= qua;
									break;
								}
								else
									r_cur = r_cur->r_next;
						}
					}
				}
				break;			//�Ѿ���ͼ�������ҵ����Ȿ�飬ִ����Ӧ������������ѭ��
			}
			b_cur = b_cur->b_next;
		}
	}
	cout << endl << "<!>ͼ����ĳɹ���" << endl;
	cout << endl << "==============================" << endl;
}

void Library::BookReturn()
{
	cout << endl << "==============================" << endl << endl;
	if (r_first == NULL)
		cout << "��ǰû����ע��ѧ����Ϣ��" << endl;
	else
	{
		string ID;
		cout << "����������ѧ��:";
		cin >> ID;
		Reader_List *r_cur = r_first;
		bool isExist = false;
		while (r_cur != NULL)
		{
			if (r_cur->r_info.reader_ID == ID)
			{
				isExist = true;
				cout.setf(ios::left | ios::unitbuf);
				cout << "ѧ��:" << setw(10) << r_cur->r_info.reader_ID << "����:" << setw(10) << r_cur->r_info.reader_name << endl;
				if (r_cur->r_info.borbook == NULL)
				{
					cout << "<!>����ǰû�н����κ�ͼ�飡" << endl;
					break;
				}
				else
				{
					cout.setf(ios::left | ios::unitbuf);
					cout << endl << setw(58) << setfill('-') << "-" << setfill(' ') << endl;
					cout << setw(6) << "���" << setw(10) << "���" << setw(20) <<
						"����" << setw(16) << "����" << setw(6) << "����" << endl << endl;
					Reader_Books *r_b_cur = r_cur->r_info.borbook;
					int n = 1;
					vector<string> nums;
					while (r_b_cur != NULL)
					{
						cout << setw(6) << n << setw(10) << r_b_cur->borbook_number << setw(20) << r_b_cur->borbook_name <<
							setw(16) << r_b_cur->borbook_author << setw(6) << r_b_cur->borbook_quantity << endl;
						nums.push_back(r_b_cur->borbook_number);
						n++;
						r_b_cur = r_b_cur->next;
					}
					cout << setw(58) << setfill('-') << "-" << setfill(' ') << endl << endl;

					int num;
					cout << "��ѡ����Ҫ�黹��ͼ��:";
					L1:cin >> num;
					if (num<1 || num>n - 1)
					{
						cout << "������������������:";
						goto L1;
					}
					else
					{
						Reader_Books *r_b_cur2 = r_cur->r_info.borbook;
						while (r_b_cur2 != NULL)
						{
							if (r_b_cur2->borbook_number == nums[num - 1])
								break;
							r_b_cur2 = r_b_cur2->next;
						}
						int qua;
						cout << "������Ҫ�黹������:";
						L2:cin >> qua;
						if (qua<0 || qua>r_b_cur2->borbook_quantity)
						{
							cout << "������������������:";
							goto L2;
						}
						else
						{
							if (qua == r_b_cur2->borbook_quantity)			//��ոö��߽���ͼ���е��Ȿͼ��
								r_cur->r_info.borbook = NULL;
							else
								r_b_cur2->borbook_quantity -= qua;			//��ȥ�黹ͼ�������
							Book_List *b_cur = b_first;
							bool isExist = false;
							while (b_cur != NULL)
							{
								if (b_cur->b_info.book_number == nums[num - 1])
								{
									isExist = true;
									b_cur->b_info.book_exist += qua;
									cout << endl << "<!>ͼ���ѳɹ��黹��" << endl;
									break;
								}
								b_cur = b_cur->b_next;
							}
							if (isExist == false)
							{
								cout << endl << "<!>ͼ��黹ʧ�ܣ�ͼ�����û���Ȿ�����Ϣ��" << endl;
							}
						}
					}
				}
				break;
			}
			r_cur = r_cur->r_next;
		}
		if (isExist == false)
		{
			cout << "ϵͳ�в��������������Ϣ��" << endl;
		}
	}
	cout << endl << "==============================" << endl;
}

void Library::SaveData()
{
	cout << endl << "==============================" << endl << endl;
	ofstream outfile1("book data.dat", ios::out);
	Book_List *b_cur = b_first;

	if (!outfile1)
	{
		cerr << "<!>ͼ����Ϣ����ʧ�ܣ�" << endl;
		exit(1);
	}

	while (b_cur != NULL)
	{
		outfile1.setf(ios::right | ios::unitbuf);						//�Ҷ��룬ÿ�������ˢ��������
		outfile1 << setw(6) << b_cur->b_info.book_number <<
			setw(30) << b_cur->b_info.book_name <<
			setw(16) << b_cur->b_info.book_author <<
			setw(10) << b_cur->b_info.book_exist <<
			setw(10) << b_cur->b_info.book_inventory;
		if (b_cur->b_next == NULL)
			break;
		else
		{
			outfile1 << endl;
			b_cur = b_cur->b_next;
		}
	}
	outfile1.close();
	cout << "<!>ͼ����Ϣ����ɹ���" << endl;

	ofstream outfile2("reader data.dat", ios::out);
	Reader_List *r_cur = r_first;

	if (!outfile2)
	{
		cerr << "<!>������Ϣ����ʧ�ܣ�" << endl;
		exit(1);
	}
	while (r_cur != NULL)
	{
		outfile2.setf(ios::right | ios::unitbuf);						//�Ҷ��룬ÿ�������ˢ��������
		outfile2 << setw(10) << r_cur->r_info.reader_ID << setw(20) << r_cur->r_info.reader_name;
		if (r_cur->r_info.borbook != NULL)
		{
			string r_b_file = "reader books ";
			string r_b_file_type = ".dat";
			r_b_file = r_b_file + r_cur->r_info.reader_ID + r_b_file_type;
			
			Reader_Books *r_b_cur = r_cur->r_info.borbook;
			
			ofstream outfile3(r_b_file, ios::out);

			if (!outfile3)
			{
				cerr << "<!>���߽�����Ϣ����ʧ�ܣ�" << endl;
				exit(1);
			}

			while (r_b_cur != NULL)
			{
				outfile3.setf(ios::right | ios::unitbuf);						//�Ҷ��룬ÿ�������ˢ��������
				outfile3 << setw(6) << r_b_cur->borbook_number <<
					setw(30) << r_b_cur->borbook_name <<
					setw(10) << r_b_cur->borbook_author <<
					setw(4) << r_b_cur->borbook_quantity;
				if (r_b_cur->next == NULL)
					break;
				else
				{
					outfile3 << endl;
					r_b_cur = r_b_cur->next;
				}
			}
			outfile3.close();
			cout << "<!>����" << r_cur->r_info.reader_ID << "�Ľ�����Ϣ����ɹ���" << endl;
		}
		if (r_cur->r_next == NULL)
			break;
		else
		{
			outfile2 << endl;
			r_cur = r_cur->r_next;
		}
	}
	outfile2.close();
	cout << "<!>������Ϣ����ɹ���" << endl;
	cout << endl << "==============================" << endl;
}

void Library::BTreeEmpty()
{
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

//��λԪ�أ����B��Ϊ���򷵻�NULL�����򷵻����Ľ��λ��
BTreeNode * Library::BTreeLocate(Book_Info & book)
{
	BTreeNode *btree_cur = btree_root;
	while (btree_cur != NULL)
	{
		for (int i = 0; i < btree_cur->num; i++)
		{
			//Ԫ���Ѵ���
			if (book.book_number == btree_cur->key[i + 1]->book_number)
				return btree_cur;
			
			//Ԫ��[i+1]�������
			if (book.book_number < btree_cur->key[i + 1]->book_number)
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
	Book_List *b_cur = b_first;
	if (b_first == NULL)
	{
		cout << "<!>ͼ����ϢΪ�գ�" << endl;
		return;
	}
	else
	{
		while (b_cur != NULL)
		{
			BTreeNode * loc = BTreeLocate(b_cur->b_info);		//ָ��ǰ���

			//��Ԫ�أ�ͼ�飩�Ѵ���
			if (BookIsExistInBTree(loc, b_cur->b_info))
			{
				cout << "- ��� " << b_cur->b_info.book_number << " ��ͼ�顶" << b_cur->b_info.book_name << "���Ѵ��ڣ��������" << endl << endl;
				b_cur = b_cur->b_next;
				continue;
			}

			//����ǰ�����뵽234����
			else
			{
				cout << "- ��� " << b_cur->b_info.book_number << " ��ͼ�顶" << b_cur->b_info.book_name << "���������У��������Ԫ��" << endl;
				BTreeInsert(b_cur, loc);
				cout << "- ��� " << b_cur->b_info.book_number << " ��ͼ�顶" << b_cur->b_info.book_name << "���ѳɹ�����B��" << endl << endl;
			}
			b_cur = b_cur->b_next;
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

	Book_List *newBook = new Book_List(number, name, author, quantity);

	//��ӵ�ͼ��������
	BookListAdd(newBook);
	cout << endl << "<!> �ѳɹ���ӵ������У�" << endl;

	//���뵽B����
	BTreeInsert(newBook, BTreeLocate(newBook->b_info));
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
		if (book->key[1]->book_number < node->key[i + 1]->book_number)
			break;
		else if (book->key[1]->book_number > node->key[i + 1]->book_number)
		{
			//ֱ�Ӳ��뵽ĩβ
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
void Library::BTreeInsert(Book_List * book, BTreeNode * loc)
{
	BTreeNode * loc_parent;					//ָ��ǰ���ĸ����
	BTreeNode * newbook;					//��Ԫ�ؽ��
	BTreeNode * newBTreeNode = NULL;		//����Ԫ�ؽ��

	newbook = new BTreeNode(&book->b_info);		//��ֵ��ʼ��

Label:
	//���locΪ�գ���234����ָ��Ϊ�գ�B��Ϊ�գ��򽫸�ָ��ָ���½ڵ�
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
			int left_right = (loc->key[up]->book_number) > (newbook->key[1]->book_number) ? 0 : 1;

			//�������������
			newBTreeNode->ptr[0]->num = up - 1;
			newBTreeNode->ptr[0]->parent = newBTreeNode;
			for (int k = 0; k < up; k++)
			{
				newBTreeNode->ptr[0]->ptr[k] = loc->ptr[k];
				if (k == 0)
					continue;
				newBTreeNode->ptr[0]->key[k] = new Book_Info(loc->key[k]);
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
					loc->key[k - up] = new Book_Info(loc->key[k]);
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
bool Library::BookIsExistInList(Book_Info * book)
{
	Book_List *b_cur = b_first;
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

