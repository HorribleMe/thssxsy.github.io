//
//  main.cpp
//  Experiment
//  Haus of Gaga
//  Created by HorribleMe on 15/11/6.
//  Copyright © 2015年 熊世裕. All rights reserved.
//

#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <stdlib.h>
#include "Basement.h"
#include "Reader.h"

using namespace std;  //最后马上截止了来写注释，如果有地方很难读请见谅

XSY_StringLink* getInput(string &inputPath);  //获取某个文件夹里面的所有文件名，以便进行读取

int main()
{
	XSY_String dicPath;
	XSY_String outputPath;
	XSY_String temp1(".info"), temp2(".txt"), finalPath1, finalPath2, finalPath3;
	string inputPath;

	Reader iReader;  //读取网页、解析网页、分词的类
	XSY_StringLink *inputHelper;
	StringNode *travel;

	cout << "请输入三个路径：" << endl;
	cin >> dicPath >> inputPath >> outputPath;
	inputHelper = getInput(inputPath);
	cout << endl << "读取词库中……" << endl;
	iReader.initDictionary(dicPath);  //载入词库
	iReader.getBadWords(); //载入停用词库
	travel = inputHelper->head;
	for(unsigned int i = 1;i < inputHelper->getLenth();i++)
	{
		finalPath1 = outputPath + "\\\\" + travel->data.getFrontPart(4) + temp1;
		finalPath2 = outputPath + "\\\\" + travel->data.getFrontPart(4) + temp2;
		finalPath3 = inputPath + "\\\\" + travel->data.GetString();
		cout << "解析第" << i << "个网页中……" << endl;
		iReader.readPage(finalPath3);  //解析网页，分词
		iReader.outputInfo(finalPath1);  //输出歌曲信息
		iReader.outputWords(finalPath2);  //输出词语
		iReader.refresh();  //清空iReader存储里面的信息
		travel = travel->next;
	}
	cout << "解析完毕"<<endl;
	return 0;
}

XSY_StringLink* getInput(string &inputPath)
{
	string command;
	command = "dir ";
	for(unsigned int i = 0; i < inputPath.size(); i++)
	{
		if (inputPath[i] == '\\')
		{
			inputPath.erase(i,1);
		}
	}
	command += inputPath;
	command += " *.html /B > input.txt";
	system(command.c_str());
	fstream inFile;
	inFile.open("input.txt");
	int j = 0;
	string x;
	while (!inFile.eof())
	{
		getline(inFile, x);
		j++;
	}
	inFile.close();
	inFile.open("input.txt");
	XSY_StringLink *pages = new XSY_StringLink;
	while (!inFile.eof())
	{
		getline(inFile, x);
		XSY_String y;
		y = x;
		pages->addNode(y);
	}
	return pages;
}