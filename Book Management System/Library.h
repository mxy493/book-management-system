#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "Book_List.h"
#include "Reader_List.h"
#include "BTreeNode.h"

class Library
{
public:
	Library(){}
	~Library(){}

	//�����ܺ���
	void ImportData();														// 1 ��������

	void BookAdd();															// 2 �ɱ����
	void BookListAdd(Book_List * newBook);									// 2.1 ���ӵ�ͼ������
	void BTreeInsert(Book_List * book, BTreeNode * loc);					// 2.2 ����ͼ�鵽B����

	void BookShow();														// 3 ����ͼ��
	void BookListShow();													// 3.1 ������ʾ
	void BookBTreeShow(BTreeNode * root, int depth);						// 3.2 B����ʾ

	void BookFind();														// 4 ����ͼ��

	void FuncEmpty();														// 5. ������
	void BookRemove();														// 5.1 ���ĳһ��ͼ��Ŀ��
	void BookListEmpty();													// 5.2.1 �������
	void BTreeEmpty();														// 5.2.2 ���B��

	void ReaderBooks();														// 6 ������Ϣ
	void ReaderList();														// 6.1 �鿴��ע������б�
	void ReaderBorrowed();													// 6.2 ��ѯ�ѽ���ͼ��

	void BookBorrow();														// 7 ͼ�����
	void BookReturn();														// 8 ͼ��黹

	void SaveData();														// 9 �洢����

	//����������غ���
	BTreeNode * BTreeLocate(Book_Info & book);								// ��λ����λ�ã�B��Ϊ���򷵻�nullptr��
	bool BookIsExistInList(Book_Info * book);								// ͼ���Ƿ��Ѵ�����������
	bool BookIsExistInBTree(BTreeNode *loc, Book_Info & book);				// ͼ���Ƿ��Ѵ�����B����
	void BTreeEstablish();													// ��������ͼ����Ϣ����B��
	BTreeNode * InsertEleDirect(BTreeNode * node, BTreeNode * book);		// ֱ���ڸ�������в���Ԫ�أ������ѣ�
private:
	Book_List *b_first;
	Reader_List *r_first;
	BTreeNode *btree_root = NULL;
};