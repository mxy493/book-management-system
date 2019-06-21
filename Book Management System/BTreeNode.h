#pragma once



const int m = 4;

struct BTreeNode
{
	int num;						//�ؼ��ָ���
	BTreeNode *parent;				//�����
	Book_Info *key[m];				//�ؼ��֣���ౣ�������ؼ��루ͼ�飩��key[0]��ʹ��
	BTreeNode *ptr[m];				//�ӽ�㣺��ౣ���ĸ�ָ�������ڵ��ָ��

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

	//���ڳ�ʼ��Ҫ����Ľ�㣨������������Ľ�㣩
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