//
//  WordsAndDoc.h
//  Experiment
//	Haus of Gaga
//  Created by HorribleMe on 15/12/14.
//  Copyright © 2015年 熊世裕. All rights reserved.
//
#ifndef DicAndDoc_h
#define DicAndDoc_h
#include "Basement.h"
#include "BTree.h"
#include "Reader.h"
#include <iostream>

//文档、文档链表以及词典

class Document  //存储完整信息的文档
{
public:
	Document();
	Document(Document&);
	Document(int i, XSY_StringLink &info, XSY_StringLink &word);
	int ID;
	bool hasWriter;   //歌曲是否有作者
	XSY_StringLink SongInfo;  //存储歌曲信息的链表
	XSY_StringLink Words;  //存储词语的链表，分词结果
	Document *pre, *next;
private:
	void upgradeInfo();  //歌曲信息的优化，删除一些无效信息
};

class DocumentLink  //存储文档所有信息的链表
{
public:
	DocumentLink();
	DocumentLink(const DocumentLink&);
	~DocumentLink();
	void addDocument(Document &xDocument);  //添加
	void addDocument(const int unsigned num, Document &xDocument);
	void replaceDocument(const int xID, Document &xDocument);  //替换
	void replaceDocumentByNum(const unsigned int num, Document &xDocument);
	void deleteDocument(const int xID);  //删除
	void deleteDocumentByNum(const unsigned int num);
	void display();  //Especially for RecommendSongs_Service
	void destroy();  //摧毁
	unsigned int getLenth();
	Document findDocument(const int xID);  //查找
	Document* findDocument(XSY_String);
	Document* getPowerForDoc(const int xID);  //得到结点进行操作
	Document findDocumentByNum(const unsigned int num);  //查找
	Document* getPowerForDocByNum(const unsigned int num);  //得到结点进行操作
	Document *head;
	Document *tail;
private:
	unsigned int lenth;
};

struct DocInfo  
{
	XSY_String songName;  //歌曲名
	XSY_String sWriter, lWriter;  //作者
	bool hasWriter;  //是否有作者
	int ID;
	int times;
	DocInfo *pre, *next;
};

class DocInfoLink  //放置于词典中的文档链表
{
public:
	DocInfoLink();
	~DocInfoLink();
	void addNode(DocInfo&);  //to tail
	void deleteNode();  //删除末尾结点
	void deleteNode(const int); //By ID
	DocInfo *getPowerForNode(const int);//By ID
	void clear();  //销毁
	void display(); //Especially for SearchWord_Service
	unsigned int getLenth()const;
	DocInfo *head, *tail;
private:
	unsigned int lenth;
	DocInfo* findLoc(DocInfo *);  //找到插入位置，以便排序
};

class Dictionary  //词典
{
public:
	Dictionary()
	{
		ID = DF = Occur = 0;
		m_Docment = NULL;
	}
	~Dictionary()
	{
		if(m_Docment != NULL)
		{
			m_Docment->clear();
			m_Docment = NULL;
		}
	}
	XSY_String word;
	int ID;
	int DF;
	int Occur;
	DocInfoLink *m_Docment;

	bool operator== (const Dictionary &xHelper)const
	{
		if(word == xHelper.word)
			return true;
		else
			return false;
	}
	bool operator != (const Dictionary &xHelper)const
	{
		if(word == xHelper.word)
			return false;
		else
			return true;
	}
	bool operator< (const Dictionary &xHelper)const
	{
		if(word < xHelper.word)
			return true;
		else
			return false;
	}

	bool containedDoc(int docID);  //查找
	void clear();  //清空
};

void creatInvertedFile(XSY_BTree<Dictionary>&, DocumentLink&);  //建立倒排文档
#endif /* DicAndDoc_h */
