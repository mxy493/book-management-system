#ifndef BTREE_NODE_H_
#define BTREE_NODE_H_

const int m = 4;

struct BTreeNode
{
	int num;						//关键字个数
	BTreeNode *parent;				//父结点
	BookInfo *key[m];				//关键字：最多保存三个关键码（图书），key[0]不使用
	BTreeNode *ptr[m];				//子结点：最多保存四个指向子树节点的指针

	BTreeNode()
	{
		num = 0;
		parent = nullptr;
		for (int i = 0; i < m; i++)
		{
			key[i] = nullptr;
			ptr[i] = nullptr;
		}
	}

	//用于初始化要插入的结点（或者是往上提的结点）
	BTreeNode(BookInfo * book)
	{
		num = 1;
		parent = nullptr;
		for (int i = 0; i < m; i++)
		{
			key[i] = nullptr;
			ptr[i] = nullptr;
			if (i == 1)
				key[i] = new BookInfo(book);
		}
	}

	BTreeNode(BTreeNode * node)
	{
		num = node->num;
		parent = node->parent;
		for (int i = 0; i < m; i++)
		{
			if (node->key[i] != nullptr)
				key[i] = new BookInfo(node->key[i]);
			else
				key[i] = nullptr;
			if (node->ptr[i] != nullptr)
				ptr[i] = node->ptr[i];
			else
				ptr[i] = nullptr;
		}
	}
};

#endif // !BTREE_NODE_H_
