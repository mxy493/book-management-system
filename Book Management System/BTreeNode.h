#pragma once



const int m = 4;

struct BTreeNode
{
	int num;						//关键字个数
	BTreeNode *parent;				//父结点
	Book_Info *key[m];				//关键字：最多保存三个关键码（图书），key[0]不使用
	BTreeNode *ptr[m];				//子结点：最多保存四个指向子树节点的指针

	BTreeNode()
	{
		num = 0;
		parent = NULL;
		for (int i = 0; i < m; i++)
		{
			key[i] = NULL;
			ptr[i] = NULL;
		}
	}

	//用于初始化要插入的结点（或者是往上提的结点）
	BTreeNode(Book_Info * book)
	{
		num = 1;
		parent = NULL;
		for (int i = 0; i < m; i++)
		{
			key[i] = NULL;
			ptr[i] = NULL;
			if (i == 1)
				key[i] = new Book_Info(book);
		}
	}

	BTreeNode(BTreeNode * node)
	{
		num = node->num;
		parent = node->parent;
		for (int i = 0; i < m; i++)
		{
			if (node->key[i] != NULL)
				key[i] = new Book_Info(node->key[i]);
			else
				key[i] = NULL;
			if (node->ptr[i] != NULL)
				ptr[i] = node->ptr[i];
			else
				ptr[i] = NULL;
		}
	}
};