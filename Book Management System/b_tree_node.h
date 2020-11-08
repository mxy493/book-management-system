#ifndef BTREE_NODE_H_
#define BTREE_NODE_H_

const int m = 4;

struct BTreeNode
{
	int num;						//�ؼ��ָ���
	shared_ptr<BTreeNode> parent;	//�����
	shared_ptr<BookInfo> key[m];	//�ؼ��֣���ౣ�������ؼ��루ͼ�飩��key[0]��ʹ��
	shared_ptr<BTreeNode> ptr[m];	//�ӽ�㣺��ౣ���ĸ�ָ�������ڵ��ָ��

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
	BTreeNode(const BookInfo& book)
	{
		num = 1;
		parent = nullptr;
		for (int i = 0; i < m; i++)
		{
			key[i] = nullptr;
			ptr[i] = nullptr;
		}
		key[1] = make_shared<BookInfo>(book); // ����һ���µ�BookInfo���� 
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
		key[1] = make_shared<BookInfo>(book); // ����һ���µ�BookInfo���� 
	}

	BTreeNode(const shared_ptr<BTreeNode> node)
	{
		num = node->num;
		parent = nullptr; // ������½ڵ�û�и��ڵ㣬��Ҫ��ʹ�õ�ʱ���ֶ��޸�ָ��
		for (int i = 0; i < m; i++)
		{
			if (node->key[i] != nullptr)
				key[i] = make_shared<BookInfo>(node->key[i]);
			else
				key[i] = nullptr;
			ptr[i] = nullptr; // ����ָ���ӽڵ��ָ����Ϊ��
		}
	}
};

#endif // !BTREE_NODE_H_
