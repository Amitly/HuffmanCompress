#pragma once

//哈夫曼树类

#include "alphaTable.h"
#include "HNode.h"
#include <string.h>

class HuffmanTree
{
private:
	//字母表
	alphaTable alT;
	//哈夫曼树表
	HNode *HTree;
	//哈夫曼编码表
	std::string *HCode;
	//哈希数组，建立字符同字母表，树表，编码表下标（三个表同一下标，表示同一字符）的映射
	unsigned hash[270];

public:

	bool initHTree(alphaTable& alT);

	bool buildTree();

	bool buildCode();

	HuffmanTree(alphaTable& alT);

	//bool SelectTwoMin(unsigned &s1,unsigned &s2);

	unsigned char Str01_2_Ch(std::string str01);

	std::string Ch_2_01Str(char ch);

	alphaTable& getAlphaTable();
};

