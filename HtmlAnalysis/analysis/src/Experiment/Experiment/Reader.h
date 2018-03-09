//
//  Reader.h
//  Experiment
//	Haus of Gaga
//  Created by HorribleMe on 15/11/7.
//  Copyright © 2015年 熊世裕. All rights reserved.
//
#ifndef Reader_h
#define Reader_h
#include "Basement.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;//读取网页、解析网页、分词的类

class Reader
{
public:
	Reader();
	~Reader();
	void initDictionary(XSY_String filePath);  //载入词库
	void getBadWords(); //载入停用词库
	void readPage(XSY_String fileName); //读取网页，包含解析和分词
	void outputInfo(XSY_String fileName);  //输出歌曲信息
	void outputWords(XSY_String fileName);  //输出词语
	void refresh();  //删除已经存储的所有信息，销毁链表
private:
	void upgradeLyric();  //分词
	void getSongInfo();  //读取歌曲信息
	bool isWord(const XSY_String xHelper);  //判断是否是一个词
	bool isBadWord(const XSY_String xHelper);  //判断是否是停用词
	bool isABC(const XSY_String xHelper);  //判断是否是英文
	XSY_String OriginalData;  //网页原始信息
	XSY_StringLink SongInfo;  //存储歌曲信息的链表
	XSY_StringLink Lyric;  //存储歌词的链表
	XSY_StringLink Words;  //存储词语的链表
	set<XSY_String> Dictionary;  //词库
	set<XSY_String> BadWords;  //停用词库
	set<XSY_String>::iterator it;
	unsigned int MaxLen;  //词库里面最长词的长度
};

#endif /* Reader_h */
