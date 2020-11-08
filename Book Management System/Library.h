#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "book_list.h"
#include "reader_list.h"
#include "b_tree_node.h"

class Library
{
public:
	Library(){}
	~Library(){}

	//�����ܺ���
	void ImportBookData();											// 1.1 ����ͼ������
	void ImportReaderData();										// 1.2 �����������
	void ImportBorrowData(shared_ptr<ReaderList> new_reader, const string& id);	// 1.3 ������߽�������

	void BookAdd();													// 2 �ɱ����
	void BookListAdd(shared_ptr<BookList> newBook);					// 2.1 ��ӵ�ͼ������
	void BTreeInsert(shared_ptr<BookList> book, shared_ptr<BTreeNode> loc);	// 2.2 ����ͼ�鵽B����

	void BookShow();												// 3 ����ͼ��
	void BookListShow();											// 3.1 ������ʾ
	void BookBTreeShow(shared_ptr<BTreeNode> root, int depth);		// 3.2 B����ʾ

	void BookFind();												// 4 ����ͼ��
	void ListFind(vector<shared_ptr<BookInfo>>& books, string info);
	void backtrackFind(shared_ptr<BTreeNode> cur, vector<shared_ptr<BookInfo>>& books, string info);


	void FuncEmpty();												// 5. ������
	void BookRemove();												// 5.1 ���ĳһ��ͼ��Ŀ��
	void BookListEmpty();											// 5.2.1 �������
	void BTreeEmpty();												// 5.2.2 ���B��

	void ReaderBooks();												// 6 ������Ϣ
	void ShowReaderList();											// 6.1 �鿴��ע������б�
	void ReaderBorrowed();											// 6.2 ��ѯ�ѽ���ͼ��

	void BookBorrow();												// 7 ͼ�����
	void BookReturn();												// 8 ͼ��黹

	void SaveData();												// 9 �洢����

	//����������غ���
	shared_ptr<BTreeNode> BTreeLocate(BookInfo & book);				// ��λ����λ�ã�B��Ϊ���򷵻�nullptr��
	bool BookIsExistInList(BookInfo * book);						// ͼ���Ƿ��Ѵ�����������
	bool BookIsExistInBTree(shared_ptr<BTreeNode> loc, BookInfo & book); // ͼ���Ƿ��Ѵ�����B����
	void BTreeEstablish();											// ��������ͼ����Ϣ����B��
	shared_ptr<BTreeNode> InsertEleDirect(shared_ptr<BTreeNode> node, shared_ptr<BTreeNode> book);// ֱ���ڸ�������в���Ԫ�أ������ѣ�
private:
	shared_ptr<BookList> book_head_;  // ͼ������ͷָ��
	shared_ptr<ReaderList> reader_head_;  // ��������ͷָ��
	shared_ptr<BTreeNode> btree_root = nullptr;  // 2-3-4��ͷָ��
};

#endif // !LIBRARY_H_
