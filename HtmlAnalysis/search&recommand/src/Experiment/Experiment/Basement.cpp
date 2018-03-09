//
//  Basement.cpp
//  Experiment
//	Haus of Gaga
//  Created by HorribleMe on 15/11/6.
//  Copyright © 2015年 熊世裕. All rights reserved.
//
#include "Basement.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;//类函数注释见头文件

XSY_String::XSY_String()
{
	myString = new char[1];
	myString[0] = '\0';
	lenth = 0;
}

XSY_String::XSY_String(unsigned int newLenth)
{
	myString = new char[newLenth + 1];
	for(unsigned int i = 0;i <= newLenth;i++)
		myString[i] = '\0';
	lenth = newLenth;
}

XSY_String::XSY_String(const char* const cstring)
{
	lenth = strlen(cstring);
	myString = new char[lenth + 1];
	for(unsigned int i=0;i < lenth;i++)
		myString[i] = cstring[i];
	myString[lenth] = '\0';
}

XSY_String::XSY_String(const string cstring)
{
	lenth = cstring.size();
	myString = new char[lenth + 1];
	for(unsigned int i = 0;i < lenth;i++)
		myString[i] = cstring[i];
	myString[lenth] = '\0';
}

XSY_String::XSY_String(const XSY_String &xstring)
{
	lenth = xstring.Size();
	myString = new char[lenth + 1];
	for(unsigned int i = 0;i < lenth;i++)
		myString[i] = xstring[i];
	myString[lenth] = '\0';
}

XSY_String::~XSY_String()
{
	delete []myString;
	lenth = 0;
}

char & XSY_String::operator [](unsigned int index)
{
	if(index > lenth)
		return myString[lenth - 1];
	else
		return myString[index];
}

char XSY_String::operator [](unsigned int index) const
{
	if(index > lenth)
		return myString[lenth - 1];
	else
		return myString[index];
}

ostream& operator<< (ostream &output, const XSY_String &xstring)
{
	output << xstring.myString;
	return output;
}

istream& operator>> (istream &input, XSY_String &xstring)
{
	string cstring;
	input >> cstring;
	xstring = cstring;
	return input;
}

bool operator== (const XSY_String &string1, const XSY_String &string2)
{
	return strcmp(string1.myString, string2.myString) == 0;
}

bool operator!= (const XSY_String &string1, const XSY_String &string2)
{
	return strcmp(string1.myString, string2.myString) != 0;
}

bool operator!= (const XSY_String &string1, const char* string2)
{
	return strcmp(string1.myString, string2) != 0;
}

XSY_String XSY_String::operator+ (const XSY_String &xstring)
{
	unsigned int newLenth = lenth + xstring.Size();
	XSY_String temp(newLenth);
	unsigned int i, j;
	for(i = 0;i < lenth;i++)
		temp[i] = myString[i];
	for(j = 0;j < xstring.Size();j++,i++)
		temp[i] = xstring[j];
	return temp;
}

void XSY_String::operator+= (const XSY_String &xstring)
{
	unsigned int xLen = xstring.Size();
	unsigned int newLenth = lenth + xLen;
	XSY_String temp(newLenth);
	unsigned int i,j;
	for(i = 0;i < lenth;i++)
		temp[i] = myString[i];
	for(j = 0;j < xLen;j++,i++)
		temp[i] = xstring[j];
	*this = temp;
}

void XSY_String::operator+= (const char x)
{
	XSY_String temp(lenth + 1);
	for(unsigned int i= 0; i < lenth; i++)
		temp[i] = myString[i];
	temp[lenth] = x;
	*this = temp;
}

XSY_String& XSY_String::operator= (const XSY_String &xstring)
{
	if(this == &xstring)
		return *this;
	delete []myString;
	lenth = xstring.Size();
	myString = new char[lenth + 1];
	for(unsigned int i = 0;i < lenth;i++)
		myString[i] = xstring[i];
	myString[lenth] = '\0';
	return *this;
}

XSY_String& XSY_String::operator= (const string cstring)
{
	delete []myString;
	lenth = cstring.size();
	myString = new char[lenth + 1];
	for(unsigned int i = 0;i < lenth;i++)
		myString[i] = cstring[i];
	myString[lenth] = '\0';
	return *this;
}

unsigned int XSY_String::indexOf(const string cstring)
{
	if(cstring.size() == 0 || lenth == 0)
		return 0;
	unsigned int i, j, start;
	bool isSame = false;
	for(i = 0;i < lenth - cstring.size();i++)
	{
		if(myString[i] == cstring[0])
		{
			start = i;
			isSame = true;
			for(j = 0;j < cstring.size();i++, j++)
			{
				if(cstring[j] != myString[i])
				{
					isSame = false;
					break;
				}
			}
		}
		if(isSame == true)break;
	}
	if(isSame == true)
		return start;
	else
		return 0;
}

void XSY_String::deleteTail()
{
	if(lenth == 1)
		this->clear();
	myString[lenth - 1] = '\0';
	lenth--;
}

void XSY_String::subString(unsigned int start)
{
	if(start == 0)
		return;
	unsigned int newlenth;
	if(start >= lenth)
		this->clear();
	else
	{
		newlenth = lenth - start;
		XSY_String temp(newlenth);
		unsigned int i, j;
		for(i = start, j = 0;j < newlenth;i++, j++)
			temp[j] = myString[i];
		*this = temp;
	}
}

void XSY_String::subString(unsigned int start, unsigned int end)
{
	if(start == 0 && end >= lenth)
		return;
	if(start > end)
		return;
	if(start >= lenth || end == 0 || start == end)
		this->clear();
	unsigned int newlenth = end - start;
	XSY_String temp(newlenth);
	unsigned int i, j;
	for(i = start, j = 0;j < newlenth;i++, j++)
		temp[j] = myString[i];
	*this = temp;
}

void XSY_String::subString(const XSY_String &xstring)//删除指定的字符串,要求该字符串必须包含在被删减的字符串中
{
	if(xstring.Size() == 0 || lenth == 0)
		return;
	unsigned int i, j, start;
	bool isSame = false;
	for(i = 0;i <= lenth - xstring.Size();i++)
	{
		if(myString[i] == xstring[0])
		{
			start = i;
			isSame = true;
			for(j = 0;j < xstring.Size();i++, j++)
			{
				if(xstring[j] != myString[i])
				{
					isSame = false;
					break;
				}
			}
		}
		if(isSame == true)break;
	}
	if(isSame == true)
	{
		unsigned int newlenth = lenth - xstring.Size();
		XSY_String temp(newlenth);
		for(i = 0, j = 0;i < newlenth;i++, j++)
		{
			if(i == start)
				j += xstring.Size();
			temp[i] = myString[j];
		}
		*this = temp;
	}
}

void XSY_String::subString(char *x)
{
	unsigned int index = 0;
	for(;index < lenth;index++)
	{
		if(myString[index] == x[0])
			break;
	}
	if(index == lenth)return;
	else
	{
		XSY_String temp(index);
		for(unsigned int i = 0;i < index;i++)
			temp[i] = myString[i];
		*this = temp;
		return;
	}
}

void XSY_String::addFrontPart(const XSY_String &xstring)
{
	if(xstring.Size() == 0)
		return;
	unsigned int newlenth = lenth + xstring.Size();
	XSY_String temp(newlenth);
	unsigned int i;
	for(i = 0;i < xstring.Size();i++)
		temp[i] = xstring[i];
	for(unsigned int j = 0;i < newlenth;i++, j++)
		temp[i] = myString[j];
	*this = temp;
}

XSY_String XSY_String::getFrontPart(unsigned int MaxLen)
{
	if(MaxLen > lenth)
		return *this;
	XSY_String temp(MaxLen);
	for(unsigned int i = 0;i < MaxLen;i++)
		temp[i] = myString[i];
	return temp;
}

void XSY_String::clear()
{
	XSY_String temp;
	*this = temp;
}

XSY_String XSY_String::cutForService()
{
	unsigned int index = 0;
	XSY_String temp;
	for(;index < lenth;index++)
	{
		if(myString[index] == ' ')
		{
			if(index == 0)
			{
				subString(1);
				return cutForService();
			}
			temp = getFrontPart(index);
			subString(index + 1);
			return temp;
		}
	}
	temp = *this;
	this->clear();
	return temp;
}

XSY_StringLink::XSY_StringLink()
{
	lenth = 0;
	head = tail = NULL;
	pHelper = qHelper = NULL;
}

XSY_StringLink::XSY_StringLink(const XSY_StringLink &xLink)
{
	lenth = xLink.lenth;
	head = tail = NULL;
	if(lenth == 0)
		return;
	StringNode *travel;
	travel = xLink.head;
	for(unsigned int i = 0;i < lenth;i++)
	{
		if(head == NULL)
		{
			head = new StringNode;
			head->pre = NULL;
			head->data = travel->data;
			pHelper = qHelper = head;
		}
		else
		{
			pHelper = new StringNode;
			pHelper->data = travel->data;
			qHelper->next = pHelper;
			pHelper->pre = qHelper;
			qHelper = pHelper;
		}
	}
	pHelper->next = NULL;
	tail = pHelper;
}

XSY_StringLink::~XSY_StringLink()
{
	clear();
}

void XSY_StringLink::addNode(const XSY_String target)
{
	lenth++;
	if(head == NULL)
	{
		head = new StringNode;
		head->data = target;
		head->pre = head->next = NULL;
		tail = head;
	}
	else
	{
		pHelper = new StringNode;
		pHelper->data = target;
		tail->next = pHelper;
		pHelper->pre = tail;
		pHelper->next = NULL;
		tail = pHelper;
	}
}

void XSY_StringLink::addNode(const string target)
{
	XSY_String _target = target;
	addNode(_target);
}

void XSY_StringLink::addNode(const XSY_String target, unsigned int position)//加在position之后一个结点
{
	if(position >= lenth)
	{
		addNode(target);
		return;
	}
	StringNode *travel, *xHelper;
	travel = head;
	lenth++;
	if(position == 0)
	{
		xHelper = new StringNode;
		xHelper->data = target;
		xHelper->pre = NULL;
		xHelper->next = head;
		head = xHelper;
		return;
	}
	for(unsigned int i = 1;i < position;i++)
		travel = travel->next;
	xHelper = new StringNode;
	xHelper->data = target;
	xHelper->pre = travel;
	xHelper->next = travel->next;
	travel->next->pre = xHelper;
	travel->next = xHelper;
}

void XSY_StringLink::deleteNode(unsigned int location)
{
	if(location == 0 || location > lenth)
		return;
	StringNode *travel, *xHelper;
	lenth--;
	if(location == 1)
	{
		if(lenth == 1)
		{
			this->clear();
			return;
		}
		xHelper = head;
		head = head->next;
		head->pre = NULL;
		delete xHelper;
		return;
	}
	if(location == lenth)
	{
		xHelper = tail;
		tail = tail->pre;
		tail->next = NULL;
		delete xHelper;
		return;
	}
	if(location <= (lenth / 2))
	{
		travel = head;
		for(unsigned int i = 1;i < location;i++)
			travel = travel->next;
		xHelper = travel->pre;
		xHelper->next = travel->next;
		travel->next->pre = xHelper;
		delete travel;
		return;
	}
	else
	{
		travel = tail;
		for(unsigned int i = lenth;i > location;i--)
			travel = travel->pre;
		xHelper = travel->pre;
		xHelper->next = travel->next;
		travel->next->pre = xHelper;
		delete travel;
		return;
	}
}

void XSY_StringLink::deleteNode(const XSY_String target)
{
	if(this->Empty() == true)
		return;
	StringNode *left, *xHelper;
	left = head;
	while(left != tail)
	{
		if(left->data == target)
		{
			if(lenth == 1)
			{
				this->clear();
				return;
			}
			lenth--;
			if(left == head)
			{
				head = head->next;
				head->pre = NULL;
				delete left;
				return;
			}
			else if(left == tail)
			{
				tail = tail->pre;
				tail->next = NULL;
				delete left;
				return;
			}
			else
			{
				xHelper = left->pre;
				xHelper->next = left->next;
				left->next->pre = xHelper;
				delete left;
				return;
			}
		}
		left = left->next;
	}
}

void XSY_StringLink::deleteTail()
{
	if(lenth == 0)return;
	lenth--;
	StringNode *tem = tail;
	tail = tail->pre;
	tail->next = NULL;
	delete tem;
}

void XSY_StringLink::copy(XSY_StringLink &xLink)
{
	clear();
	lenth = xLink.lenth;
	head = tail = NULL;
	if(lenth == 0)
		return;
	StringNode *travel;
	travel = xLink.head;
	for(unsigned int i = 0;i < lenth;i++)
	{
		if(head == NULL)
		{
			head = new StringNode;
			head->pre = NULL;
			head->data = travel->data;
			pHelper = qHelper = head;
		}
		else
		{
			pHelper = new StringNode;
			pHelper->data = travel->data;
			qHelper->next = pHelper;
			pHelper->pre = qHelper;
			qHelper = pHelper;
		}
		travel = travel->next;
	}
	pHelper->next = NULL;
	tail = pHelper;
}

unsigned int XSY_StringLink::findNode(const XSY_String target)
{
	if(this->Empty() == true)
		return 0;
	StringNode *travel = head;
	for(unsigned int i = 1;i <= lenth;i++)
	{
		if(travel->data == target)
			return i;
		travel = travel->next;
	}
	return 0;
}

XSY_String XSY_StringLink::findNode(unsigned int position)
{
	if(position > lenth || position == 0)
	{
		cerr << "查找出错" << endl;
		exit(1);
	}
	StringNode *travel = head;
	for(unsigned int i = 1;i < position;i++)
		travel = travel->next;
	return travel->data;
}

StringNode* XSY_StringLink::getPowerForNode(unsigned int position)
{
	if(position > lenth || position == 0)
	{
		cerr << "查找出错" << endl;
		exit(1);
	}
	StringNode *travel = head;
	for(unsigned int i = 1;i < position;i++)
		travel = travel->next;
	return travel;
}

void XSY_StringLink::clear()
{
	if(head == NULL)
		return;
	pHelper = qHelper = head;
	for(unsigned int i = 0;i < lenth;i++)
	{
		pHelper = pHelper->next;
		delete qHelper;
		qHelper = pHelper;
	}
	head = tail = NULL;
	lenth = 0;
}//置空，=0