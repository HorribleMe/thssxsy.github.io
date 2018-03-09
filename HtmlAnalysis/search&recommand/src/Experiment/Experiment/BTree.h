//
//  BTree.h
//  Experiment
//	Haus of Gaga
//  Created by HorribleMe on 15/12/16.
//  Copyright © 2015年 熊世裕. All rights reserved.
//
#ifndef BTree_h
#define BTree_h
#include <iostream>

using namespace std;  

template <class Xtype>
class XSY_BTree  //B-树
{
private:
	static const unsigned int CORE = 66;  //B-树属性
	static const unsigned int MAX_KEY = CORE - 1;
	static const unsigned int MIN_KEY = (CORE / 2) - 1;
	static const unsigned int MAX_CHILD = CORE;
	static const unsigned int MIN_CHILD = CORE / 2;
	struct BTreeNode  //B-树的结点
	{
		unsigned int keyNum;
		bool isLeaf;
		Xtype Keys[MAX_KEY];
		BTreeNode *children[MAX_CHILD];
		BTreeNode()
		{
			isLeaf = true;
			keyNum = 0;
			for(int i = 0;i < MAX_CHILD;i++)
			{
				children[i] = NULL;
			}
		}
	};
	BTreeNode *root;

public:
	XSY_BTree()
	{
		root = NULL;
	}
	~XSY_BTree()
	{
		clear();
	}

	Xtype*  operator[] (Xtype target)  //重载的[]以便对结点进行修改
	{
		BTreeNode *tem, *targetPoint;
		tem = targetPoint = NULL;
		unsigned int targetIndex;
		bool sign;
		sign = search(root, target, targetPoint, tem, targetIndex);
		if(sign == false)
		{
			cerr << "can't find" << endl;
			exit(1);
		}
		else
		{
			Xtype *result = &targetPoint->Keys[targetIndex];
			return result;
		}
	}

	bool insert(const Xtype &target)  //插入
	{
		BTreeNode *position, *parent;
		position = parent = NULL;
		unsigned int index;
		if(search(root, target, position, parent, index) == true)
			return false;
		else
		{
			if(root == NULL)
			{
				root = new BTreeNode;
				root->Keys[0] = target;
				root->keyNum++;
				return true;
			}
			else
			{
				if(position->isLeaf == true)
				{
					if(position->keyNum == MAX_KEY)
					{
						splitChild(position, parent);
						insert(target);
						return true;
					}
					for(unsigned int i = position->keyNum;i > index;i--)
						position->Keys[i] = position->Keys[i - 1];
					position->Keys[index] = target;
					position->keyNum++;
				}
				else
				{
					cerr << "Bug1" << endl;
					exit(1);
				}
				return true;
			}
		}
	}

	bool remove(const Xtype target)  //删除
	{
		BTreeNode *targetPoint, *parent;
		targetPoint = parent = NULL;
		unsigned int targetIndex;
		if(search(root, target, targetPoint, parent, targetIndex) == false)return false;
		if(root->keyNum == 1)
		{
			if(root->isLeaf == true)
			{
				clear();
				return true;
			}
			else
			{
				BTreeNode *child1 = root->children[0];
				BTreeNode *child2 = root->children[1];
				if(child1->keyNum == MIN_KEY && child2->keyNum == MIN_KEY)
				{
					mergeNodes(root, 0);
					deleteNode(root);
					root = child1;
				}
			}
		}
		deleteX(targetPoint, parent, target, targetIndex);
		return true;
	}

	bool contained(const Xtype &target)  //查找
	{
		BTreeNode *tem1;
		unsigned int tem2;
		return find(target, tem1, tem2);
	}

	void clear()  //清空
	{
		partDestroy(root);
		root = NULL;
	}

private:
	bool find(const Xtype &target, BTreeNode *&targetPoint, unsigned int &targetIndex)const//私有的查找，并得到查找到的结点以便进行操作
	{   
		//私有的查找，并得到查找到的结点以便进行操作
		BTreeNode *tem;
		return search(root, target, targetPoint, tem, targetIndex);
	}

	unsigned int getIndex(BTreeNode *Node, BTreeNode *parent)  //得到一个孩子的序号
	{
		if(Node == root)return -1;
		else
		{
			for(unsigned int i = 0;i < MAX_CHILD;i++)
			{
				if(parent->children[i] == Node)
					return i;
			}
		}
		return -2;
	}

	BTreeNode* findLeast(BTreeNode *presentNode, BTreeNode *&_parent)  //找到最左的孩子，用于删除时的替代
	{
		if(presentNode == NULL)
		{
			cerr << "valid operation" << endl;
			exit(1);
		}
		BTreeNode *least = presentNode;
		while(least->children[0] != NULL)
		{
			_parent = least;
			least = least->children[0];
		}
		return least;
	}

	void partDestroy(BTreeNode *partRoot)//子树摧毁
	{
		if(partRoot != NULL)
		{
			if(partRoot->isLeaf == false)
			{
				for(unsigned int i = 0;i < partRoot->keyNum;i++)
					partDestroy(partRoot->children[i]);
			}
			deleteNode(partRoot);
		}
	}

	void deleteNode(BTreeNode *Node)//删除某结点
	{
		if(Node != NULL)
		{
			delete Node;
			Node = NULL;
		}
	}

	bool search(BTreeNode *partRoot, const Xtype &target, BTreeNode *&targetPoint, BTreeNode *&parent, unsigned int &targetIndex)const//私有的查找，还可以得到相应的结点进行操作
	{
		//私有的查找，还可以得到相应的结点进行操作
		if(partRoot == NULL)
		{
			return false;
		}
		else
		{
			targetPoint = partRoot;
			unsigned int i;
			for(i = 0;i < partRoot->keyNum && partRoot->Keys[i] < target;i++){}
			targetIndex = i;
			if(i < partRoot->keyNum && partRoot->Keys[i] == target)
			{
				return true;
			}
			else
			{
				if(partRoot->isLeaf == true)
				{
					return false;
				}
				else
				{
					parent = partRoot;
					return  search(partRoot->children[i], target, targetPoint, parent, targetIndex);
				}
			}
		}
	}

	void splitChild(BTreeNode *&fullNode, BTreeNode *parent)//分裂结点
	{
		if(fullNode == root)
		{
			BTreeNode *newRoot = new BTreeNode;
			newRoot->isLeaf = false;
			newRoot->children[0] = root;
			root = newRoot;
			splitChild(root->children[0], root);
			return;
		}
		unsigned int index = getIndex(fullNode, parent);
		BTreeNode* newNode = new BTreeNode;
		newNode->isLeaf = fullNode->isLeaf;
		newNode->keyNum = MIN_KEY;
		for(unsigned int i = 0;i < MIN_KEY;i++)
			newNode->Keys[i] = fullNode->Keys[MIN_KEY + 1 + i];
		if(fullNode->isLeaf == false)
		{
			for(unsigned int i = 0;i < MIN_CHILD;i++)
			{
				newNode->children[i] = fullNode->children[MIN_CHILD + i];
				fullNode->children[MIN_CHILD + i] = NULL;
			}
		}
		fullNode->keyNum = MIN_KEY;
		for(unsigned int i = parent->keyNum;i > index;i--)
		{
			parent->Keys[i] = parent->Keys[i - 1];
			parent->children[i + 1] = parent->children[i];
		}
		parent->keyNum++;
		parent->Keys[index] = fullNode->Keys[MIN_KEY];
		parent->children[index + 1] = newNode;
		if(parent->keyNum == MAX_KEY)
		{
			if(parent == root)
				splitChild(root, NULL);
			else
			{
				BTreeNode *_Parent, *tem;
				_Parent = tem = NULL;
				unsigned int _Index;
				if(search(root, parent->Keys[0], tem, _Parent, _Index) == false)
					cerr << "error1" << endl;
				else
					splitChild(parent, _Parent);
			}
		}
	}

	void mergeNodes(BTreeNode *parent, int index)  //融合孩子
	{
		BTreeNode *_Parent, *tem;
		unsigned int _Index;
		_Parent = tem = NULL;
		if(parent->keyNum == MIN_KEY)
		{
			if(search(root, parent->Keys[0], tem, _Parent, _Index) == false)
			{
				cerr << "error2" << endl;
				exit(1);
			}
		}
		BTreeNode *child1 = parent->children[index];
		BTreeNode *child2 = parent->children[index + 1];
		child1->keyNum = MAX_KEY - 1;
		child1->Keys[MIN_KEY] = parent->Keys[index];
		for(unsigned int i = 0;i < MIN_KEY - 1;i++)
			child1->Keys[MIN_KEY + i + 1] = child2->Keys[i];
		if(child1->isLeaf == false)
		{
			for(unsigned int i = 0;i < MIN_CHILD - 1;i++)
				child1->children[i + MIN_CHILD] = child2->children[i];
		}
		for(unsigned int i = index;i < parent->keyNum;i++)
		{
			parent->Keys[i] = parent->Keys[i + 1];
			parent->children[i + 1] = parent->children[i + 2];
		}
		parent->keyNum--;
		delete child2;
		if(parent->keyNum == MIN_KEY - 1)
			checkAndAdjust(parent, _Parent);
	}

	void deleteX(BTreeNode *&targetPoint, BTreeNode *parent, const Xtype target, int targetIndex) //删除某关键字
	{
		if(targetPoint->Keys[targetIndex] != target)
		{
			cerr << "Bug2" << endl;
			exit(1);
		}
		else
		{
			if(targetPoint->isLeaf == true)
			{
				for(unsigned int i = targetIndex;i < targetPoint->keyNum;i++)
					targetPoint->Keys[i] = targetPoint->Keys[i + 1];
				targetPoint->keyNum--;
				checkAndAdjust(targetPoint, parent);
			}
			else
			{
				BTreeNode *_parent = parent->children[targetIndex + 1];
				BTreeNode *least = findLeast(targetPoint->children[targetIndex + 1], _parent);
				targetPoint->Keys[targetIndex] = least->Keys[0];
				deleteX(least, _parent, least->Keys[0], 0);
			}
		}
	}

	void checkAndAdjust(BTreeNode *patient, BTreeNode *parent)  //删除后检查是否平衡，以及相应的调整函数
	{
		if(patient == root)return;
		if(patient->keyNum >= MIN_KEY)return;
		int index = getIndex(patient, parent);
		if(patient->keyNum == MIN_KEY - 1)
		{
			BTreeNode *LBrother = getLBrother(patient, parent);
			BTreeNode *RBrother = getRBrother(patient, parent);
			if(LBrother != NULL || RBrother != NULL)
			{
				if(LBrother != NULL && LBrother->keyNum > MIN_KEY)
				{
					for(unsigned int i = patient->keyNum;i > 0;i--)
						patient->Keys[i] = patient->Keys[i - 1];
					patient->Keys[0] = parent->Keys[index - 1];
					patient->keyNum++;
					parent->Keys[index - 1] = LBrother->Keys[LBrother->keyNum - 1];
					LBrother->keyNum--;
				}
				else if(RBrother != NULL && RBrother->keyNum > MIN_KEY)
				{
					patient->Keys[patient->keyNum] = parent->Keys[index];
					parent->Keys[index] = RBrother->Keys[0];
					patient->keyNum++;
					RBrother->keyNum--;
				}
				else
				{
					if(LBrother != NULL && LBrother->keyNum == MIN_KEY)
						mergeNodes(parent, index - 1);
					else if(RBrother != NULL && RBrother->keyNum == MIN_KEY)
						mergeNodes(parent, index);
					else
					{
						cerr << "Bug3" << endl;
						exit(1);
					}
				}
			}
			else
			{
				cerr << "valid tree" << endl;
				exit(1);
			}
		}
		else
		{
			cerr << "Bug4" << endl;
			exit(1);
		}
	}

	BTreeNode *getLBrother(BTreeNode *Node, BTreeNode *parent)//得到结点的左兄弟
	{
		if(Node == root)return NULL;
		int i = getIndex(Node, parent);
		if(i == 0)return NULL;
		else
			return parent->children[i - 1];
	}

	BTreeNode *getRBrother(BTreeNode *Node, BTreeNode *parent)//得到结点的右兄弟
	{
		if(Node == root)return NULL;
		int i = getIndex(Node, parent);
		if(i == MAX_CHILD)return NULL;
		else
			return parent->children[i + 1];
	}
};
#endif /* BTree_h */
