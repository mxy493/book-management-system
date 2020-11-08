#ifndef BTREE_NODE_H_
#define BTREE_NODE_H_

const int m = 4;

struct BTreeNode
{
	int num;						//关键字个数
	shared_ptr<BTreeNode> parent;	//父结点
	shared_ptr<BookInfo> key[m];	//关键字：最多保存三个关键码（图书），key[0]不使用
	shared_ptr<BTreeNode> ptr[m];	//子结点：最多保存四个指向子树节点的指针

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
	BTreeNode(const BookInfo& book)
	{
		num = 1;
		parent = nullptr;
		for (int i = 0; i < m; i++)
		{
			key[i] = nullptr;
			ptr[i] = nullptr;
		}
		key[1] = make_shared<BookInfo>(book); // 构造一个新的BookInfo对象 
	}

	BTreeNode(const shared_ptr<BookInfo> book)
	{
		num = 1;
		parent = nullptr;
		for (int i = 0; i < m; i++)
		{
			key[i] = nullptr;
			ptr[i] = nullptr;
		}
		key[1] = make_shared<BookInfo>(book); // 构造一个新的BookInfo对象 
	}

	BTreeNode(const shared_ptr<BTreeNode> node)
	{
		num = node->num;
		parent = nullptr; // 构造的新节点没有父节点，需要在使用的时候手动修改指向
		for (int i = 0; i < m; i++)
		{
			if (node->key[i] != nullptr)
				key[i] = make_shared<BookInfo>(node->key[i]);
			else
				key[i] = nullptr;
			ptr[i] = nullptr; // 所有指向孩子节点的指针置为空
		}
	}
};

#endif // !BTREE_NODE_H_
