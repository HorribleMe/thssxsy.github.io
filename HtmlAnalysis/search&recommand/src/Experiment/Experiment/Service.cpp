//
//  Service.h
//  Experiment
//	Haus of Gaga
//  Created by HorribleMe on 15/12/18.
//  Copyright © 2015年 熊世裕. All rights reserved.
//
#include "Basement.h"
#include "BTree.h"
#include "Reader.h"
#include "DicAndDoc.h"
#include <iostream>
#include <io.h>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

void SeachWord_Service(XSY_BTree<Dictionary> &allWords)
{
	cout << endl << "--批量搜索--" << endl;
	cout << "输出说明：(歌名-ID-OccurTimes-词作家/*如果有的话*/-曲作家)" << endl << endl;;
	fstream outFile;
	outFile.open("query1.txt", ios::in);
	XSY_StringLink operationWords;
	string tem;
	while(!outFile.eof())  //打开文件，得到查询
	{
		getline(outFile, tem);
		operationWords.addNode(tem);
	}
	StringNode *travel = operationWords.head;
	DocInfoLink result;
	for(unsigned int i = 0;i < operationWords.getLenth();i++)
	{
		while(travel->data.Size() > 0)//判断当前查询是否结束
		{
			Dictionary temDic;
			temDic.word = travel->data.cutForService();  //把一行查询分成一个一个的词进行，并减掉已经查询过的词
			if(allWords.contained(temDic) == true)  //找到词
			{
				DocInfo *travelDocInfo = allWords[temDic]->m_Docment->head;
				while(travelDocInfo != NULL)  //把文档链表内容全部加到新的文档链表中用于输出
				{
					result.addNode(*travelDocInfo);  //在添加的时候会判断是否重复，并进行相应操作
					travelDocInfo = travelDocInfo->next;
				}
			}
		}
		cout << "查询" << i + 1 << ":" << endl;
		result.display();  //文档链表展示
		cout << endl;
		result.clear();  //清空用于输出的文档链表，进行下一个查询
		travel = travel->next;
		cout << endl;
	}
}
void _SeachWord_Service(XSY_BTree<Dictionary> &allWords, XSY_String target)
{
	DocInfoLink result;  //类似于上一个函数，只不过只有一个查询
	Dictionary temDic;
	temDic.word = target;
	if(allWords.contained(temDic) == true)
	{
		DocInfo *travelDocInfo = allWords[temDic]->m_Docment->head;
		while(travelDocInfo != NULL)
		{
			result.addNode(*travelDocInfo);
			travelDocInfo = travelDocInfo->next;
		}
	}
	cout << "查询结果：" << endl;
	result.display();
	cout << endl;
	result.clear();
}

void RecommendSongs_Service(DocumentLink &allDoc)
{
	cout << endl <<"--批量推荐--" << endl;
	cout << "输出说明：(ID-歌曲名-歌手-专辑名称-发行时间-曲作家/*如果有的话*/-词作家)" << endl << endl;
	fstream outFile;
	outFile.open("query2.txt", ios::in);
	XSY_StringLink operationWords;
	string tem;
	while(!outFile.eof()) //得到查询，用链表存储
	{
		getline(outFile, tem);
		operationWords.addNode(tem);
	}
	StringNode *travel = operationWords.head;
	DocumentLink recommend;
	for(unsigned int i = 0;i < operationWords.getLenth();i++)
	{
		Document *selectedDoc = allDoc.findDocument(travel->data);  //在文档链表中查询该歌曲
		if(selectedDoc->ID == allDoc.tail->ID && selectedDoc->SongInfo.findNode(1) != travel->data)
			cout << "未能找到输入音乐" << endl;
		else
		{   //找到歌曲，用一个链表存储推荐的歌曲信息
			Document *docTravel = allDoc.head;
			while(recommend.getLenth() < 10 && docTravel != NULL)
			{
				if(docTravel->ID != selectedDoc->ID)  //防止推荐同一首歌
				{
					for(int i = 1;i <= 8;i++)
					{
						bool get = false;
						if(i != 1 && i != 3 && i != 6)  //不需要的比较信息
						{
							if(i == 5)  //比较发行年份，去掉了月、日
							{
								if(docTravel->SongInfo.findNode(i).getFrontPart(4) == selectedDoc->SongInfo.findNode(i).getFrontPart(4))
								{
									recommend.addDocument(*docTravel);
									get = true;
								}
							}
							else if(docTravel->SongInfo.findNode(i) == selectedDoc->SongInfo.findNode(i))
							{
								recommend.addDocument(*docTravel);  //比较歌手、词曲作家、专辑
								get = true;
							}
						}
						if(get == true)break;
					}
				}
				docTravel = docTravel->next;
			}
			Document *docTravel1 = selectedDoc->pre;
			Document *docTravel2 = selectedDoc->next;
			XSY_String time = selectedDoc->SongInfo.findNode(5).getFrontPart(4);
			int _time = atoi(time.GetString());  //把发现年份变为int以便比较
			while(recommend.getLenth() < 10)  //推荐的歌少于10个，从目标歌曲开始，向两边寻找时间相近的歌曲
			{
				if(docTravel1 != NULL)
				{
					XSY_String time1 = docTravel1->SongInfo.findNode(5).getFrontPart(4);
					int _time1 = atoi(time1.GetString());
					if(_time1 == _time - 1 || _time1 == _time + 1)
					{
						recommend.addDocument(*docTravel1);
					}
					docTravel1 = docTravel1->pre;
				}
				if(docTravel2 != NULL && recommend.getLenth() < 10)
				{
					XSY_String time2 = docTravel2->SongInfo.findNode(5).getFrontPart(4);
					int _time2 = atoi(time2.GetString());
					if(_time2 == _time - 1 || _time2 == _time + 1)
					{
						recommend.addDocument(*docTravel2);
					}
					docTravel2 = docTravel2->next;
				}
			}
			cout << "第" << i+1 << "首歌的推荐结果："<<endl;
			recommend.display();  //打印结果
			cout << endl;
			recommend.destroy();  //销毁，进行下一个推荐
		}
		travel = travel->next;
	}
}
void _RecommendSongs_Service(DocumentLink &allDoc, XSY_String target)
{
	DocumentLink recommend;  //与上一个函数类似
	Document *selectedDoc = allDoc.findDocument(target);
	if(selectedDoc->ID == allDoc.tail->ID && selectedDoc->SongInfo.findNode(1) != target)
		cout << "未能找到输入音乐" << endl;
	else
	{
		Document *docTravel = allDoc.head;
		while(recommend.getLenth() < 10 && docTravel != NULL)
		{
			if(docTravel->ID != selectedDoc->ID)
			{
				for(int i = 1;i <= 8;i++)
				{
					bool get = false;
					if(i != 1 && i != 3 && i != 6)
					{
						if(i == 5)
						{
							if(docTravel->SongInfo.findNode(i).getFrontPart(4) == selectedDoc->SongInfo.findNode(i).getFrontPart(4))
							{
								recommend.addDocument(*docTravel);
								get = true;
							}
						}
						else if(docTravel->SongInfo.findNode(i) == selectedDoc->SongInfo.findNode(i))
						{
							recommend.addDocument(*docTravel);
							get = true;
						}
					}
					if(get == true)break;
				}
			}
			docTravel = docTravel->next;
		}
		Document *docTravel1 = selectedDoc->pre;
		Document *docTravel2 = selectedDoc->next;
		XSY_String time = selectedDoc->SongInfo.findNode(5).getFrontPart(4);
		int _time = atoi(time.GetString());
		while(recommend.getLenth() < 10)
		{
			if(docTravel1 != NULL)
			{
				XSY_String time1 = docTravel1->SongInfo.findNode(5).getFrontPart(4);
				int _time1 = atoi(time1.GetString());
				if(_time1 == _time - 1 || _time1 == _time + 1)
				{
					recommend.addDocument(*docTravel1);
				}
				docTravel1 = docTravel1->pre;
			}
			if(docTravel2 != NULL && recommend.getLenth() < 10)
			{
				XSY_String time2 = docTravel2->SongInfo.findNode(5).getFrontPart(4);
				int _time2 = atoi(time2.GetString());
				if(_time2 == _time - 1 || _time2 == _time + 1)
				{
					recommend.addDocument(*docTravel2);
				}
				docTravel2 = docTravel2->next;
			}
		}
		cout << endl << "推荐结果："<<endl;
		recommend.display();
		cout << endl;
		recommend.destroy();
	}
}

float f(float x, float y, float z)   //无视我
{
	float a = x * x + 9.0f / 4.0f * y * y + z * z - 1;
	return a * a * a - x * x * z * z * z - 9.0f / 80.0f * y * y * z * z * z;
}

float h(float x, float z) //无视我
{
	for (float y = 1.0f; y >= 0.0f; y -= 0.001f)
		if (f(x, y, z) <= 0.0f)
			return y;
	return 0.0f;
}

void fareWell()
{
	
}

void Tip()
{
	cout << "(1-找词语，2-找歌词，3-歌曲推荐，4-删除词语，5-添加资源，0-退出)" << endl;
	cout << "请输入指令：";
}

void newRow()
{
	cout << endl << "/*----------------------------------------------------------------------*/" << endl;
}

void advertisement()
{
	cout << "Haus of Gaga" << endl;
	cout << "Created by HorribleMe on 15/12/18.  Copyright 2015年 熊世裕. All rights reserved." << endl;
}

void getFiles(string path, XSY_StringLink *files)
{
	long  hFile   =   0;
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			if((fileinfo.attrib &  _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					getFiles( p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files->addNode(p.assign(path).append("\\").append(fileinfo.name));
			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}

void addMaterial(Reader &iReader, XSY_BTree<Dictionary> &allWords, DocumentLink &allDoc, XSY_String path)
{
	string inputPath;  //输入路径
	inputPath = path.GetString();
	XSY_StringLink *inputHelper = new XSY_StringLink;  //存储文件名的链表

	getFiles(inputPath, inputHelper); 

	cout << endl <<"添加网页中……";
	double done, _done;
	_done = done = 0;
	StringNode *travel = inputHelper->head;
	for(unsigned int i = 1,  _i = 0;i <= inputHelper->getLenth();i++, _i++)
	{
		done = ((double)i / (double)inputHelper->getLenth())*100;
		if(i == 1)cout << fixed << setprecision(2) << done << '%';  //进度条
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
		allDoc.addDocument(tem);
		iReader.refresh();  //清空iReader存储里面的信息
		travel = travel->next;
	}
	cout << endl <<"构建新的词语索引中……" << endl;
	creatInvertedFile(allWords, allDoc); //构建新的倒排文档
}

void Gui_Service(XSY_BTree<Dictionary> &allWords, DocumentLink &allDoc, Reader &iReader)
{
	cout << endl << "----交互----" << endl << endl;
	cout << "-----欢迎使用\"歌词王\"-----" << endl;
	advertisement();
	cout << "使用说明：1-找词语，2-找歌词，3-歌曲推荐，4-删除词语，5-添加资源，0-退出" << endl;
	newRow();
	cout << "请输入指令：" << endl;
	int signal = 0;
	XSY_String tem;
	Dictionary temDic;
	cin >> signal;
	while(cin.good())  
	{
		switch (signal)
		{
		case 0:
			fareWell();
			return;
		case 1:
			cout << "请输入查找的词语： ";
			cin >> tem;
			_SeachWord_Service(allWords, tem);
			cout << endl << "--完毕--" << endl;
			break;
		case 2:
			cout << "此服务还未上线" << endl;
			break;
		case 3:
			cout << "请输入歌名：";
			cin >> tem;
			_RecommendSongs_Service(allDoc, tem);
			cout << endl << "--完毕--" << endl;
			break;
		case 4:
			cout << "请输入想要删除的词语：";
			cin >> tem;
			temDic.word = tem;
			allWords.remove(temDic);
			cout << endl << "--完毕--" << endl;
			break;
		case 5:
			cout << "请输入文件夹路径：" << endl;
			cin >> tem;
			addMaterial(iReader, allWords, allDoc, tem);
			cout << endl << "--完毕--" << endl;
			break;
		default:
			cout << endl << "--无效的指令!--" << endl;
			break;
		}
		newRow();
		Tip();
		cin >> signal;
	}
	cout << "-----非法的指令，终止程序（请不要输入中文指令!）-----" << endl;
}