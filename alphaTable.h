#pragma once

//��ĸ����

#include "alpha.h"
#include <string>

class alphaTable
{
public:
	//��ĸ��
	Alpha* alpTab;
	//��ĸ���е���ĸ����
	unsigned alpNum;

public:

	//���캯���������ж������
	alphaTable(const char* filename);

	bool initAlTa();

	//�����ĸ���е���ĸ����
	unsigned getAlpNum();

	//��ĸ����������Ϊ�˽��ͺ����������е�ʱ�临�Ӷ�
	bool sortAlpTab();

	//����ĸ����Ϣ��ͷ���ݣ�д���ļ���
	bool writeToFile(const char* filename);

	//���ַ����л�ȡ��ĸ��
	bool getAlpTab_Str(std::string str);

	//���ļ������ݻ�ȡ��ĸ��
	bool getAlpTab_File(const char* filename);
};

