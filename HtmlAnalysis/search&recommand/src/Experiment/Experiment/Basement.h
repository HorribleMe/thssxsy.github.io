//
//  Basement.h
//  Experiment
//	Haus of Gaga
//  Created by HorribleMe on 15/11/6.
//  Copyright © 2015年 熊世裕. All rights reserved.
//
//所有自己写的数据类型

#ifndef Basement_h
#define Basement_h
#include <iostream>
#include <string>
#include <stdlib.h>

#define MAXSIZE 10000  //没声明时，栈的最大长度

using namespace std; 

class XSY_String  //字符串
{
public:
	XSY_String();
	XSY_String(const char* const cstring);
	XSY_String(const XSY_String &xstring);
	XSY_String(const string cstring);
	~XSY_String();

	char & operator[] (unsigned int index);  //重载的符号
	char operator[] (unsigned int index) const;
	bool operator< (const XSY_String &xHelper)const  //for <set>
	{
		unsigned int newLenth;
		if(lenth < xHelper.Size())
			newLenth = lenth;
		else
			newLenth = xHelper.Size();
		for(unsigned int i = 0;i < newLenth;i++)
		{
			if(myString[i] < xHelper[i])
				return true;
			if(myString[i] > xHelper[i])
				return false;
		}
		if(lenth < xHelper.Size())
			return true;
		else
			return false;
	}  
	friend ostream& operator<< (ostream &output, const XSY_String &xstring);
	friend istream& operator>> (istream &input, XSY_String &xstring);
	friend bool operator== (const XSY_String &string1, const XSY_String &stirng2);
	friend bool operator!= (const XSY_String &string1, const XSY_String &stirng2);
	friend bool operator!= (const XSY_String &string1, const char* string2);
	XSY_String operator+ (const XSY_String &xstring);
	void operator+= (const XSY_String &xstring);
	void operator+= (const char x);
	XSY_String & operator= (const XSY_String &xstring);
	XSY_String & operator= (const string cstring);

	unsigned int indexOf(const string cstring);  //找到指定字符串的位置
	void deleteTail();  //删除尾部一个字符
	void subString(unsigned int start);  //删掉start之前部分
	void subString(unsigned int start, unsigned int end);  //删掉start之前，end之后部分
	void subString(const XSY_String &xstring);  //删掉指定字符串
	void subString(char*);  //Especailly for upgradeInfo
	void addFrontPart(const XSY_String &xstring);  //加指定字符串到该字符串前面
	XSY_String cutForService();
	XSY_String getFrontPart(unsigned int MaxLen);  //返回前面MaxLen长度的字符串

	unsigned int Size()const { return lenth; }  //返回字符串长度
	const char* GetString()const { return myString; }  
	void clear();  //字符串清空
private:
	XSY_String(unsigned int newLenth);  //私有构造
	char* myString;
	unsigned int lenth;
};

template <class Xtype>
class XSY_Stack
{
private:
	int top;  //栈顶指示
	Xtype *stackName;  //数组名
	int maxsize;  //栈最大可容纳元素个数
public:
	XSY_Stack():top(-1),maxsize(MAXSIZE)
	{
		stackName = new Xtype[maxsize];
		if(stackName == NULL)
		{
			cerr<<"动态存储分配失败"<<endl;
			exit(1);
		}
	}

	XSY_Stack(int size):top(-1),maxsize(size)
	{
		stackName = new Xtype[maxsize];
		if(stackName == NULL)
		{     
			cerr<<"动态存储分配失败"<<endl;
			exit(1);
		}
	}

	XSY_Stack(Xtype data[],int size):top(-1),maxsize(size)
	{
		stackName = new Xtype[maxsize];
		if(stackName == NULL)
		{ 
			cerr<<"动态存储分配失败"<<endl;
			exit(1);
		}
		for(int i = 0;i < maxsize;i++){
			stackName[i] = data[i];
		}
		top += maxsize;
	}

	~XSY_Stack()
	{
		delete []stackName;
	}

	void Push(const Xtype item)  //压栈
	{
		if(Full())
		{         
			cerr<<"栈满不能压栈"<<endl;
			exit(1);
		}
		top++;   
		stackName[top] = item;
	}
	void Pop()  //退栈
	{
		if(Empty()){
			cerr<<"栈空不能退栈!"<<endl;
			exit(1);
		}
		top--;
	}
	Xtype Top()  //获得栈顶元素
	{
		if(Empty())
		{
			cerr<<"栈空!"<<endl;
			exit(1);
		}
		return stackName[top];
	}
	bool Empty()const  //判断栈是否为空
	{
		if(top == -1)
			return true;
		else
			return false;
	}
	bool Full()const  //判断栈是否满
	{
		if(top == maxsize - 1)
			return true;
		else
			return false;
	}
	void Clear() //清空
	{
		top = -1;
	}
};

struct StringNode
{
	XSY_String data;
	StringNode *pre, *next;
};

class XSY_StringLink
{
public:
	XSY_StringLink();
	XSY_StringLink(const XSY_StringLink&);
	~XSY_StringLink();

	void addNode(const XSY_String target);  //添加结点
	void addNode(const string target);
	void addNode(const XSY_String target, unsigned int position);  //添加结点到指定位置
	void deleteNode(unsigned int location);  //删除指定位置结点
	void deleteNode(const XSY_String target);  //删除含指定字符串结点
	void deleteTail();
	void copy(XSY_StringLink&);  //复制链表
	unsigned int findNode(const XSY_String target);  //找到含指定字符串的结点
	XSY_String findNode(unsigned int position);  //返回指定位置结点的字符串
	StringNode* getPowerForNode(unsigned int position);

	unsigned int getLenth()const{return lenth;}  //返回链表长度
	bool Empty()const  //判断链表是否为空
	{
		if(lenth == 0)
			return true;
		else
			return false;
	}
	void clear(); //销毁链表
	StringNode *head, *tail;  //公有的头尾指针
private:
	StringNode *pHelper, *qHelper;
	unsigned int lenth;
};

#endif /* Basement_h */
