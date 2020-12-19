#pragma once

//字母表类

#include "alpha.h"
#include <string>

class alphaTable
{
public:
	//字母表
	Alpha* alpTab;
	//字母表中的字母数量
	unsigned alpNum;

public:

	//构造函数，可能有多个重载
	alphaTable(const char* filename);

	bool initAlTa();

	//获得字母表中的字母数量
	unsigned getAlpNum();

	//字母表排序函数，为了降低后序建树过程中的时间复杂度
	bool sortAlpTab();

	//将字母表信息（头数据）写到文件里
	bool writeToFile(const char* filename);

	//从字符串中获取字母表
	bool getAlpTab_Str(std::string str);

	//从文件的内容获取字母表
	bool getAlpTab_File(const char* filename);
};

