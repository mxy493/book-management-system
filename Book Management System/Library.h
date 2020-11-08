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

	//主功能函数
	void ImportBookData();											// 1.1 导入图书数据
	void ImportReaderData();										// 1.2 导入读者数据
	void ImportBorrowData(shared_ptr<ReaderList> new_reader, const string& id);	// 1.3 导入读者借阅数据

	void BookAdd();													// 2 采编入库
	void BookListAdd(shared_ptr<BookList> newBook);					// 2.1 添加到图书链表
	void BTreeInsert(shared_ptr<BookList> book, shared_ptr<BTreeNode> loc);	// 2.2 插入图书到B树中

	void BookShow();												// 3 所有图书
	void BookListShow();											// 3.1 链表显示
	void BookBTreeShow(shared_ptr<BTreeNode> root, int depth);		// 3.2 B树显示

	void BookFind();												// 4 查找图书
	void ListFind(vector<shared_ptr<BookInfo>>& books, string info);
	void backtrackFind(shared_ptr<BTreeNode> cur, vector<shared_ptr<BookInfo>>& books, string info);


	void FuncEmpty();												// 5. 清除库存
	void BookRemove();												// 5.1 清除某一本图书的库存
	void BookListEmpty();											// 5.2.1 清空链表
	void BTreeEmpty();												// 5.2.2 清空B树

	void ReaderBooks();												// 6 借阅信息
	void ShowReaderList();											// 6.1 查看已注册读者列表
	void ReaderBorrowed();											// 6.2 查询已借阅图书

	void BookBorrow();												// 7 图书借阅
	void BookReturn();												// 8 图书归还

	void SaveData();												// 9 存储数据

	//辅助功能相关函数
	shared_ptr<BTreeNode> BTreeLocate(BookInfo & book);				// 定位插入位置（B树为空则返回nullptr）
	bool BookIsExistInList(BookInfo * book);						// 图书是否已存在于链表中
	bool BookIsExistInBTree(shared_ptr<BTreeNode> loc, BookInfo & book); // 图书是否已存在于B树中
	void BTreeEstablish();											// 根据链表图书信息构建B树
	shared_ptr<BTreeNode> InsertEleDirect(shared_ptr<BTreeNode> node, shared_ptr<BTreeNode> book);// 直接在给定结点中插入元素（不分裂）
private:
	shared_ptr<BookList> book_head_;  // 图书链表头指针
	shared_ptr<ReaderList> reader_head_;  // 读者链表头指针
	shared_ptr<BTreeNode> btree_root = nullptr;  // 2-3-4树头指针
};

#endif // !LIBRARY_H_
