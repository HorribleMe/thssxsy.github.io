//
//  main.cpp
//  Experiment
//  Haus of Gaga
//  Created by HorribleMe on 15/11/6.
//  Copyright © 2015年 熊世裕. All rights reserved.
//

#include <iostream>
#include <io.h>
#include <string>
#include <set>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include "Basement.h"
#include "Reader.h"
#include "DicAndDoc.h"
#include "BTree.h"
#include "Service.h"

using namespace std;

int main(int argc, const char * argv[])
{
	int selectService = 2;
	string configPath;  //配置文件路径
	XSY_String dicPath, badWordPath;  //两个词典路径
	string _dicPath, _badWordPath;  //词典辅助路径
	string inputPath;  //输入路径
	XSY_StringLink *inputHelper = new XSY_StringLink;  //存储文件名的链表
	clock_t start, end;  //时钟
	//大的功能类：
	Reader iReader;  //读取网页、解析网页、分词的类
	DocumentLink allDoc;  //文档链表

	configPath = "Dictionary.config";
	inputPath = "pages_300";
	
	getFiles(inputPath, inputHelper);  //得到文件夹下所有文件名

	fstream outFile;
	outFile.open(configPath, ios::in);  //读取配置文件
	getline(outFile, _dicPath);
	getline(outFile, _badWordPath);
	dicPath = _dicPath;  //替换辅助路径
	badWordPath = _badWordPath;
	
	start = clock();
	cout << endl << "读取词库中……" << endl;
	iReader.initDictionary(dicPath);  //载入词库
	iReader.getBadWords(badWordPath); //载入停用词库
	StringNode *travel = inputHelper->head;
	cout << "解析网页中……";
	double done, _done;
	_done = done = 0;
	for(unsigned int i = 1,  _i = 0;i <= inputHelper->getLenth();i++, _i++)
	{
		done = ((double)i / (double)inputHelper->getLenth())*100;
		if(i == 1)cout << fixed << setprecision(2) << done << '%';
		else
		{
			int len = 5;
			if(_done >= 10)len = 6;
			for(int i = 0;i < len;i++)
				cout << '\b';
			cout << done << '%';
		}
		_done = done;
		iReader.readPage(travel->data);  //解析网页，分词
		Document tem(i, iReader.SongInfo, iReader.Words);
		allDoc.addDocument(tem);  //将文档存储到文档链表中
		iReader.refresh();  //清空iReader存储里面的信息
		travel = travel->next;
	}
	cout << endl;
	XSY_BTree<Dictionary> allWords;
	switch (selectService)
	{
	case 0:
		cout << "构建词库索引中……" << endl;  //批量搜索
		creatInvertedFile(allWords, allDoc);
		SeachWord_Service(allWords);
		break;
	case 1:
		RecommendSongs_Service(allDoc);  //批量推荐
		break;
	case 2:
		cout << "构建词库索引中……" << endl;
		creatInvertedFile(allWords, allDoc);  //GUI
		Gui_Service(allWords, allDoc, iReader);
		break;
	default:
		break;
	}
	end = clock();
	cout << endl << "--完毕--"<<endl;
	cout << "总耗时：" << (double)(end - start)/CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}
