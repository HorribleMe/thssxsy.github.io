//
//  Reader.cpp
//  Experiment
//	Haus of Gaga
//  Created by HorribleMe on 15/11/7.
//  Copyright © 2015年 熊世裕. All rights reserved.
//
#include "Basement.h"
#include "Reader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

Reader::Reader()
{
	MaxLen = 0;
}

Reader::~Reader()
{
	refresh();
}

void Reader::initDictionary(XSY_String filePath)
{
	fstream outFile;
	string temp;
	XSY_String word;
	outFile.open(filePath.GetString(), ios::in);
	while(!outFile.eof())
	{
		getline(outFile,temp);
		word = temp;
		if(temp.size() > MaxLen)
			MaxLen = temp.size();
		Dictionary.insert(word);
	}
}

void Reader::getBadWords(XSY_String badWordPath)
{
	fstream outFile;
	string temp;
	XSY_String word;
	outFile.open(badWordPath.GetString(), ios::in);
	while(!outFile.eof())
	{
		getline(outFile,temp);
		word = temp;
		BadWords.insert(word);
	}
}

void Reader::readPage(XSY_String fileName)
{
	fstream outFile;
	outFile.open(fileName.GetString(), ios::in);
	string info,temp;
	while(!outFile.eof())
	{
		getline(outFile,temp);
		info += temp;
	}
	OriginalData = info;
	unsigned int start, end;
	start = OriginalData.indexOf("<div class=\"song_info_area\">");
	end = OriginalData.indexOf("<div class=\"music_list_area\">") + 29;
	OriginalData.subString(start, end);
	getSongInfo();
	betterInfo();
	upgradeLyric();
}

void Reader::getSongInfo()
{
	XSY_Stack<XSY_String> signalCan;
	char temp;
	XSY_String info, signal;
	unsigned int lenth = OriginalData.Size();
	bool isFake = false;
	for(unsigned int i = 0;i < lenth;i++)
	{
		temp = OriginalData[i];
		if(temp == '<')
		{
			signal += '<';
			do 
			{
				i++;
				temp = OriginalData[i];
				signal += temp;
			} while(signal != "<div" && signal != "<h2" && signal != "<img" && signal != "</div>" && signal != "<a" &&signal != "</a>" && signal != "</h2>" && signal != "<ul" && signal != "</ul>" && signal != "<li>" && signal != "</li>"
				&& signal != "<span>" && signal != "</span>" && signal != "<p" && signal != "</p>" && signal != "<span" && signal != "<textarea" &&signal != "</textarea>" && signal != "<script>" && signal != "</script>");

			if(signal != "<img" && signal != "</div>" && signal != "</a>" && signal != "</h2>" && signal != "</ul>" && signal != "</li>" && signal != "</span>" && signal != "</p>" && signal != "</textarea>" && signal != "</script>")
				signalCan.Push(signal);

			if(signal == "</a>" && signalCan.Top() == "<a")
			{
				isFake = true;
				signalCan.Pop();
			}
			if(signal == "</div>" && signalCan.Top() == "<div")
				signalCan.Pop();
			if(signal == "</h2>" && signalCan.Top() == "<h2")
				signalCan.Pop();
			if(signal == "</ul>" && signalCan.Top() == "<ul")
				signalCan.Pop();
			if(signal == "</span>" && signalCan.Top() == "<span>")
				signalCan.Pop();
			if(signal == "</span>" && signalCan.Top() == "<span")
				signalCan.Pop();
			if(signal == "</script>" && signalCan.Top() == "<script>")
				signalCan.Pop();
			if(signal == "</textarea>" && signalCan.Top() == "<textarea")
				signalCan.Pop();

			if(signal == "</li>")
			{
				if(signalCan.Top() == "<li>")
				{
					SongInfo.addNode(info);
					signalCan.Pop();
				}
			}
			if(signal == "</p>")
			{
				if(isFake == false)
					if(signalCan.Top() == "<p")
					{
						SongInfo.addNode(info);
						Lyric.addNode(info);
						signalCan.Pop();
					}
			}
			if(signal == "<div" || signal == "<h2" || signal == "<a" || signal == "<ul"|| signal == "<p" || signal == "<img" || signal == "<span" || signal == "<textarea")
			{
				isFake = false;
				info.clear();
				do 
				{
					i++;
					temp = OriginalData[i];
				} while (temp != '>');
			}
			if(signal == "<h2")
			{
				i++;
				temp = OriginalData[i];
				while(temp != '<')
				{
					if(temp != '\t')
						info += temp;
					i++;
					temp = OriginalData[i];
				}
				SongInfo.addNode(info);
				info.clear();
				i--;
			}
			if(signal == "<li>" || signal == "<span>")
				info.clear();
			signal.clear();
		}
		else if(temp != '\t' && temp != '（' && temp != '~' && temp != '）' && temp != '(' && temp != ')')
			info += temp;
	}
}

void  Reader::betterInfo()
{
	if(Lyric.tail->data == "本站歌词来自互联网")
		Lyric.deleteTail();
}

void Reader::upgradeLyric()
{
	XSY_String xHelper, xHelperSaver;
	for(unsigned int i = 0;i < 3;i++)
		Lyric.deleteNode(1);
	unsigned int lenth = Lyric.getLenth();
	StringNode *travel;
	travel = Lyric.head;
	for(unsigned int i = 0;i < lenth;i++)
	{
		while(travel->data.Size() > 0)
		{
			if(MaxLen >= travel->data.Size())
			{
				xHelper = travel->data;
				travel->data.clear();
			}
			else
			{
				xHelper = travel->data.getFrontPart(MaxLen);
				travel->data.subString(MaxLen);
			}
			xHelperSaver = xHelper;
			while(xHelper.Size() > 1)
			{
				if(isBadWord(xHelper) == true)
					break;
				if(isWord(xHelper) == true || isABC(xHelper) == true)
				{
					Words.addNode(xHelper);
					break;
				}
				xHelper.deleteTail();
			}
			xHelperSaver.subString(xHelper.Size());
			if(xHelperSaver.Size() > 0)
				travel->data.addFrontPart(xHelperSaver);
		}
		travel = travel->next;
	}
}

void Reader::outputInfo(XSY_String fileName)
{
	ofstream inFile;
	inFile.open(fileName.GetString(), ios::trunc);
	StringNode *travel = SongInfo.head;
	for(unsigned int i = 0;i < SongInfo.getLenth();i++)
	{
		inFile << travel->data << endl;
		travel = travel->next;
	}
}

void Reader::outputWords(XSY_String fileName)
{
	ofstream inFile;
	inFile.open(fileName.GetString(), ios::trunc);
	StringNode *travel = Words.head;
	for(unsigned int i = 0;i < Words.getLenth();i++)
	{
		inFile << travel->data << endl;
		travel = travel->next;
	}
}

bool Reader::isWord(const XSY_String xHelper)
{
	it = Dictionary.find(xHelper);
	if(it != Dictionary.end())
		return true;
	else
		return false;
}

bool Reader::isBadWord(const XSY_String xHelper)
{
	it = BadWords.find(xHelper);
	if(it != BadWords.end())
		return true;
	else
		return false;
}

bool Reader::isABC(const XSY_String xHelper)
{
	for(unsigned int i = 0;i < xHelper.Size();i++)
		if(xHelper[i] < 'a' || xHelper[i] > 'z')
			return false;
	return true;
}

void Reader::refresh()//用于刷新以读取下一个文件
{
	SongInfo.clear();
	Lyric.clear();
	Words.clear();
}
