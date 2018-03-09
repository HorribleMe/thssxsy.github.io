//
//  Service.h
//  Experiment
//	Haus of Gaga
//  Created by HorribleMe on 15/12/18.
//  Copyright © 2015年 熊世裕. All rights reserved.
//
#ifndef Service_h
#define Service_h
#include "Basement.h"
#include "BTree.h"
#include "Reader.h"
#include "DicAndDoc.h"
#include <iostream>
#include <stdio.h>

void SeachWord_Service(XSY_BTree<Dictionary>&);//批量查找
void _SeachWord_Service(XSY_BTree<Dictionary>&, XSY_String);//GUI中的查找

void RecommendSongs_Service(DocumentLink &);//批量推荐
void _RecommendSongs_Service(DocumentLink &, XSY_String);//GUI中的推荐

void Gui_Service(XSY_BTree<Dictionary>&, DocumentLink &, Reader &);//GUI

void searchSong(DocumentLink &, XSY_String);//寻找歌曲

void addMaterial(Reader &, XSY_BTree<Dictionary>&, DocumentLink &);//添加网页资源

void fareWell();//当我不存在

void Tip();//for GUI

void newRow();//for GUI

void advertisement();//for GUI

void getFiles(string path, XSY_StringLink *files);//获取某个文件夹里面的所有文件名，以便进行读取
#endif /* Service_h */