//
//  WordsAndDoc.cpp
//  Experiment
//	Haus of Gaga
//  Created by HorribleMe on 15/12/14.
//  Copyright © 2015年 熊世裕. All rights reserved.
//
#include "DicAndDoc.h"
#include "Basement.h"
#include "BTree.h"
#include "Reader.h"
#include <iostream>

using namespace std;

Document::Document()
{
	ID = -1;
	hasWriter = false;
	pre = next = NULL;
}

Document::Document(Document &xDoc)
{
	ID = xDoc.ID;
	hasWriter = xDoc.hasWriter;
	SongInfo.copy(xDoc.SongInfo);
	Words.copy(xDoc.Words);
	upgradeInfo();
	pre = next = NULL;
}

Document::Document(int i, XSY_StringLink &info, XSY_StringLink &word)
{
	ID = i;
	hasWriter = false;
	SongInfo.copy(info);
	Words.copy(word);
	upgradeInfo();
	pre = next = NULL;
}

void Document::upgradeInfo()
{
	StringNode *travel = SongInfo.head;
	char tem = ' ';
	char tem2 = '(';
	char tem3 = '&';
	char *_tem = &tem;
	char *_tem2 = &tem2;
	char *_tem3 = &tem3;
	for(unsigned int i = 0;i < 8;i++)
	{
		if(i == 0)
		{
			travel->data.subString(_tem);
			travel->data.subString(_tem2);
		}
		if(i == 6)
		{
			if(travel->data.getFrontPart(4) == "词：")
			{
				travel->data.subString(4);
				travel->data.subString(_tem3);
				hasWriter = true;
			}
			else if(travel->data.getFrontPart(3) == "词:")
			{
				travel->data.subString(3);
				travel->data.subString(_tem3);
				hasWriter = true;
			}
		}
		if(i == 7)
		{
			if(travel->data.getFrontPart(4) == "曲：")
			{
				travel->data.subString(4);
				travel->data.subString(_tem3);
			}
			else if(travel->data.getFrontPart(3) == "曲:")
			{
				travel->data.subString(3);
				travel->data.subString(_tem3);
			}
		}
		travel->data.subString(" ");
		travel = travel->next;
	}
}

DocumentLink::DocumentLink()
{
	lenth = 0;
	head = tail = NULL;
}

DocumentLink::DocumentLink(const DocumentLink &xDocument)
{
	lenth = xDocument.lenth;
	head = tail = NULL;
	if(lenth == 0)
		return;
	Document *travel, *pHelper, *qHelper;
	travel = xDocument.head;
	pHelper = qHelper = NULL;
	for(unsigned int i = 0;i < lenth;i++)
	{
		if(head == NULL)
		{
			head = new Document(travel->ID, travel->SongInfo, travel->Words);
			pHelper = qHelper = head;
		}
		else
		{
			pHelper = new Document(travel->ID, travel->SongInfo, travel->Words);
			qHelper->next = pHelper;
			pHelper->pre = qHelper;
			qHelper = pHelper;
		}
	}
	pHelper->next = NULL;
	tail = pHelper;
}

DocumentLink::~DocumentLink()
{
	destroy();
}

void DocumentLink::addDocument(Document &xDocument)
{
	lenth++;
	if(head == NULL)
	{
		head = new Document(xDocument);
		tail = head;
	}
	else
	{
		Document *pHelper = new Document(xDocument);
		tail->next = pHelper;
		pHelper->pre = tail;
		tail = pHelper;
	}
}

void DocumentLink::addDocument(const unsigned int num, Document &xDocument)
{
	Document *pHelper = NULL, *qHelper = NULL;
	if(head == NULL)
	{
		head = new Document(xDocument);
		tail = head;
	}
	else if(num == 0)
	{
		pHelper = new Document(xDocument);
		head->pre = pHelper;
		pHelper->next = head;
		head = pHelper;
	}
	else if(num >= lenth)
	{
		addDocument(xDocument);
	}
	else
	{
		Document *travel = head;
		for(unsigned int i = 1;i < num;i++)travel = travel->next;
		qHelper = travel->next;
		pHelper = new Document(xDocument.ID, xDocument.SongInfo, xDocument.Words);
		travel->next = pHelper;
		pHelper->pre = travel;
		pHelper->next = qHelper;
		qHelper->pre = pHelper;
	}
	lenth++;
}

void DocumentLink::replaceDocument(const int xID, Document &xDocument)
{
	Document *travel = head;
	for(unsigned int i = 0;i < lenth;i++)
	{
		if(travel->ID == xID)
		{
			travel->ID = xDocument.ID;
			travel->SongInfo.copy(xDocument.SongInfo);
			travel->Words.copy(xDocument.Words);
			break;
		}
	}
}

void DocumentLink::replaceDocumentByNum(const unsigned int num, Document &xDocument)
{
	if(num == 0 || num > lenth)return;
	Document *travel = head;
	for(unsigned int i = 1;i < num;i++)
		travel = travel->next;
	travel->ID = xDocument.ID;
	travel->SongInfo.copy(xDocument.SongInfo);
	travel->Words.copy(xDocument.Words);
}

void DocumentLink::deleteDocument(const int xID)
{
	Document *travel = head;
	if(lenth == 0)return;
	for(unsigned int i = 0;i < lenth;i++)
	{
		if(travel->ID = xID)
		{
			if(travel == head)
			{
				head = head->next;
				head->pre = NULL;
			}
			else if(travel = tail)
			{
				tail = tail->pre;
				tail->next = NULL;
			}
			else
			{
				travel->pre->next = travel->next;
				travel->next->pre = travel->pre;
			}
			delete travel;
			break;
		}
	}
	lenth--;
}

void DocumentLink::deleteDocumentByNum(const unsigned int num)
{
	if(num == 0 || num > lenth)return;
	Document *travel = head;
	for(unsigned int i = 1;i < num;i++)
		travel = travel->next;

	if(travel == head)
	{
		head = head->next;
		head->pre = NULL;
	}
	else if(travel = tail)
	{
		tail = tail->pre;
		tail->next = NULL;
	}
	else
	{
		travel->pre->next = travel->next;
		travel->next->pre = travel->pre;
	}
	delete travel;
}

void DocumentLink::display()
{
	Document *travel = head;
	for(unsigned int i = 0;i < lenth;i++)
	{
		cout << "(" << travel->ID;
		for(int i = 1;i <= 8;i++)
		{
			if(i != 3 && i != 6)
			{
				if(i == 7 || i == 8)
				{
					if(travel->hasWriter == true)
						cout << "-" << travel->SongInfo.findNode(i);
				}
				else
					cout << "-" << travel->SongInfo.findNode(i);
			}
		}
		cout << ")" << endl;
		travel = travel->next;
	}
}

void DocumentLink::destroy()
{
	if(lenth == 0)return;
	Document *pHelper, *qHelper;
	pHelper = qHelper = head;
	for(unsigned int i = 0;i < lenth;i++)
	{
		pHelper = pHelper->next;
		delete qHelper;
		qHelper = pHelper;
	}
	head = tail = NULL;
	lenth = 0;
}

unsigned int DocumentLink::getLenth()
{
	return lenth;
}

Document DocumentLink::findDocument(const int xID)
{
	Document *travel = head;
	for(unsigned int i = 0;i < lenth;i++)
	{
		if(travel->ID == xID)
			return *travel;
		travel = travel->next;
	}
	cerr << "指定文件不在链表中" << endl;
	exit(1);
}

Document* DocumentLink::findDocument(XSY_String songName)
{
	Document *travel = head;
	for(unsigned int i = 0;i < lenth;i++)
	{
		if(travel->SongInfo.findNode(1) == songName)
			return travel;
		travel = travel->next;
	}
	return tail;
}

Document* DocumentLink::getPowerForDoc(const int xID)
{
	Document *travel = head;
	for(unsigned int i = 0;i < lenth;i++)
	{
		if(travel->ID == xID)
			return travel;
		travel = travel->next;
	}
	cerr << "指定文件不在链表中" << endl;
	exit(1);
}

Document DocumentLink::findDocumentByNum(const unsigned int num)
{
	if(num == 0 || num > lenth)
	{
		cerr << "指定的数值不在查找范围内" << endl;
		exit(1);
	}
	Document *travel = head;
	for(unsigned int i = 1;i < num;i++)travel = travel->next;
	return *travel;
}

Document* DocumentLink::getPowerForDocByNum(const unsigned int num)
{
	if(num == 0 || num > lenth)
	{
		cerr << "指定的数值不在查找范围内" << endl;
		exit(1);
	}
	Document *travel = head;
	for(unsigned int i = 1;i < num;i++)travel = travel->next;
	return travel;
}

DocInfoLink::DocInfoLink()
{
	lenth = 0;
	head = tail = NULL;
}

DocInfoLink::~DocInfoLink()
{
	clear();
}

void DocInfoLink::addNode(DocInfo &xDoc)
{
	if(lenth == 0)
	{
		head = new DocInfo;
		head->ID = xDoc.ID;
		head->times = xDoc.times;
		head->songName = xDoc.songName;
		head->hasWriter = xDoc.hasWriter;
		head->lWriter = xDoc.lWriter;
		head->sWriter = xDoc.sWriter;
		head->next = head->pre = NULL;
		tail = head;
		lenth++;
	}
	else if(lenth == 1)
	{
		if(head->ID == xDoc.ID)
		{
			head->times += xDoc.times;
			return;
		}
		else
		{
			lenth++;
			DocInfo *pHelper = new DocInfo;
			pHelper->ID = xDoc.ID;
			pHelper->hasWriter = xDoc.hasWriter;
			pHelper->times = xDoc.times;
			pHelper->songName = xDoc.songName;
			pHelper->lWriter = xDoc.lWriter;
			pHelper->sWriter = xDoc.sWriter;
			if(pHelper->times > head->times)
			{
				pHelper->next = head;
				head->pre = pHelper;
				tail = head;
				head = pHelper;
				head->pre = NULL;
			}
			else
			{
				pHelper->pre = head;
				pHelper->next = NULL;
				head->next = pHelper;
				tail = pHelper;
			}
			return;
		}
	}
	else
	{
		DocInfo *pHelper = new DocInfo;
		pHelper->ID = xDoc.ID;
		pHelper->times = xDoc.times;
		pHelper->songName = xDoc.songName;
		pHelper->hasWriter = xDoc.hasWriter;
		pHelper->lWriter = xDoc.lWriter;
		pHelper->sWriter = xDoc.sWriter;
		DocInfo *tem = findLoc(pHelper);
		if(tem->ID == pHelper->ID)
		{
			tem->times += pHelper->times;
			return;
		}
		lenth++;
		if(tem == head)
		{
			head->pre = pHelper;
			pHelper->next = head;
			head = pHelper;
			head->pre = NULL;
		}
		else if(tem == tail && tem->times > xDoc.times)
		{
			pHelper->pre = tail;
			pHelper->next = NULL;
			tail->next = pHelper;
			tail = pHelper;
		}
		else
		{
			DocInfo *_tem = tem->pre;
			_tem->next = pHelper;
			pHelper->pre = _tem;
			pHelper->next =tem;
			tem->pre = pHelper;
		}
	}
}

void DocInfoLink:: deleteNode()
{
	DocInfo *tem = tail;
	tail = tail->pre;
	tail->next = NULL;
	lenth--;
	delete tem;
}

void DocInfoLink:: deleteNode(const int xID) //By ID
{
	if(head == NULL)return;
	if(lenth == 1 && head->ID == xID)clear();
	DocInfo *travel = head;
	while(travel != NULL && travel->ID != xID)
		travel = travel->next;
	if(travel == NULL)return;
	lenth--;
	if(travel == head)
	{
		head = head->next;
		head->pre = NULL;
		delete travel;
	}
	else if(travel == tail)
	{
		tail = tail->pre;
		tail->next = NULL;
		delete travel;
	}
	else
	{
		travel->pre->next = travel->next;
		travel->next->pre = travel->pre;
		delete travel;
	}
}

DocInfo* DocInfoLink::getPowerForNode(const int xID)//By ID
{
	if(head == NULL)
		return NULL;
	DocInfo *travel = head;
	while(travel != NULL && travel->ID != xID)
		travel = travel->next;
	travel;
	return travel;
}

void DocInfoLink::clear()
{
	if(head == NULL)return;
	DocInfo *pHelper = head, *qHelper = head;
	for(unsigned int i = 0;i < lenth;i++)
	{
		pHelper = pHelper->next;
		delete qHelper;
		qHelper = pHelper;
	}
	head = tail = NULL;
	lenth = 0;
}

void DocInfoLink::display()
{
	DocInfo *travel = head;
	if(lenth == 0)
	{
		cout << "无效的查询" << endl;
		return;
	}
	while(travel != NULL)
	{
		if(travel->hasWriter == false)
			cout << "(" << travel->songName << "-" << travel->ID << "-" << travel->times << ")" << endl;
		else
			cout << "(" << travel->songName << "-" << travel->ID << "-" << travel->times << "-" << travel->lWriter << "-" << travel->sWriter << ")" <<endl;
		travel = travel->next;
	}
}

unsigned int DocInfoLink::getLenth()const
{
	return lenth;
}

DocInfo* DocInfoLink::findLoc(DocInfo *travel)
{
	DocInfo *tem = head;
	while(tem != tail && tem->times > travel->times)
		tem = tem->next;
	return tem;
}

bool Dictionary::containedDoc(int docID)
{
	if(m_Docment->head == NULL)
		return false;
	DocInfo *travel = m_Docment->head;
	while(travel != NULL && travel->ID != docID)
		travel = travel->next;
	if(travel == NULL)
		return false;
	else
	{
		if(travel->ID == docID)
			return true;
		else
		{
			cerr << "error" << endl;
			exit(1);
		}
	}
}

void creatInvertedFile(XSY_BTree<Dictionary> &allWords, DocumentLink &allDoc)
{
	int wordID = 1;
	if(allDoc.getLenth() == 0)return;
	Document *travel = allDoc.head;  //得到所有存储文档信息链表的头结点
	Dictionary tem;  //用于插入B-树
	for(unsigned int i = 1;i <= allDoc.getLenth();i++) //词库循环层
	{
		StringNode *wordTravel = travel->Words.head;
		for(unsigned int j = 0;j < travel->Words.getLenth();j++) //文档循环层
		{
			tem.word = wordTravel->data;
			if(allWords.contained(tem) == true)  //判断B-树中是否有该关键字
			{
				allWords[tem]->Occur++;
				if(allWords[tem]->containedDoc(i) == false)  //判断该词中是否有该文档
				{
					allWords[tem]->DF++;
					DocInfo infoTem;
					infoTem.ID = i;
					infoTem.times = 1;
					infoTem.songName = travel->SongInfo.findNode(1);  //歌名，下同
					if(travel->hasWriter == true) //该文档是否有作者信息
					{
						infoTem.hasWriter = true;
						infoTem.lWriter = travel->SongInfo.findNode(7);  //词作者，下同
						infoTem.sWriter = travel->SongInfo.findNode(8);  //曲作者，下同
					}
					else
						infoTem.hasWriter = false;
					allWords[tem]->m_Docment->addNode(infoTem);  //把文档插入到词语中
				} 
				else  //有该文档，则只需times++
				{
					DocInfo *_tem = allWords[tem]->m_Docment->getPowerForNode(i);  //得到该文档结点进行操作
					_tem->times++;
					_tem = NULL;
				}
			}
			else  //B-树中没有该词
			{
				Dictionary *_tem = new Dictionary;
				_tem->word = tem.word;
				DocInfo infoTem;
				infoTem.ID = i;
				infoTem.times = 1;
				if(travel->hasWriter == true)
				{
					infoTem.hasWriter = true;
					infoTem.lWriter = travel->SongInfo.findNode(7);
					infoTem.sWriter = travel->SongInfo.findNode(8);
				}
				else
					infoTem.hasWriter = false;
				infoTem.songName = travel->SongInfo.findNode(1);
				_tem->m_Docment = new DocInfoLink;
				_tem->m_Docment->addNode(infoTem);  //把文档插入到词中
				_tem->DF = _tem->Occur = 1;
				_tem->ID = wordID;
				wordID++;
				bool sign = false;
				sign = allWords.insert(*_tem);  //插入该词
				if(sign == false)
				{
					cerr << "error" << endl;
					exit(1);
				}
			}
			wordTravel = wordTravel->next;
		}
		travel = travel->next;
	}
}