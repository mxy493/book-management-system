#ifndef BTREE_NODE_H_
#define BTREE_NODE_H_

const int m = 4;

struct BTreeNode
{
	int num;						//�ؼ��ָ���
	BTreeNode *parent;				//�����
	BookInfo *key[m];				//�ؼ��֣���ౣ�������ؼ��루ͼ�飩��key[0]��ʹ��
	BTreeNode *ptr[m];				//�ӽ�㣺��ౣ���ĸ�ָ�������ڵ��ָ��

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

	//���ڳ�ʼ��Ҫ����Ľ�㣨������������Ľ�㣩
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
