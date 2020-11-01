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

	//主功能函数
	void ImportBookData();											// 1.1 导入图书数据
	void ImportReaderData();										// 1.2 导入读者数据
	void ImportBorrowData(shared_ptr<Reader_List> new_reader, const string& reader_id);	// 1.3 导入读者借阅数据

	void BookAdd();													// 2 采编入库
	void BookListAdd(shared_ptr<Book_List> newBook);							// 2.1 添加到图书链表
	void BTreeInsert(shared_ptr<Book_List> book, BTreeNode * loc);			// 2.2 插入图书到B树中

	void BookShow();												// 3 所有图书
	void BookListShow();											// 3.1 链表显示
	void BookBTreeShow(BTreeNode * root, int depth);				// 3.2 B树显示

	void BookFind();												// 4 查找图书
	void ListFind(vector<Book_Info*>& books, string info);
	void backtrackFind(BTreeNode* cur, vector<Book_Info*>& books, string info);


	void FuncEmpty();												// 5. 清除库存
	void BookRemove();												// 5.1 清除某一本图书的库存
	void BookListEmpty();											// 5.2.1 清空链表
	void BTreeEmpty();												// 5.2.2 清空B树

	void ReaderBooks();												// 6 借阅信息
	void ReaderList();												// 6.1 查看已注册读者列表
	void ReaderBorrowed();											// 6.2 查询已借阅图书

	void BookBorrow();												// 7 图书借阅
	void BookReturn();												// 8 图书归还

	void SaveData();												// 9 存储数据

	//辅助功能相关函数
	BTreeNode * BTreeLocate(Book_Info & book);						// 定位插入位置（B树为空则返回nullptr）
	bool BookIsExistInList(Book_Info * book);						// 图书是否已存在于链表中
	bool BookIsExistInBTree(BTreeNode *loc, Book_Info & book);		// 图书是否已存在于B树中
	void BTreeEstablish();											// 根据链表图书信息构建B树
	BTreeNode * InsertEleDirect(BTreeNode * node, BTreeNode * book);// 直接在给定结点中插入元素（不分裂）
private:
	shared_ptr<Book_List> b_first;
	shared_ptr<Reader_List> r_first;
	BTreeNode *btree_root = NULL;
};