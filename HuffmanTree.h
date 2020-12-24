#pragma once

//����������

#include "alphaTable.h"
#include "HNode.h"
#include <string.h>

class HuffmanTree
{
private:
	//��ĸ��
	alphaTable alT;
	//����������
	HNode *HTree;
	//�����������
	std::string *HCode;
	//��ϣ���飬�����ַ�ͬ��ĸ������������±꣨������ͬһ�±꣬��ʾͬһ�ַ�����ӳ��
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

