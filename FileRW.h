#pragma once

//�ļ���д��
/// <summary>
/// ����ԭ���ļ������ĸ��,��������������ֱ�Ӷ��ļ����в�������ñ����ļ���ֱ�ӶԱ����ļ����в�����
/// ���ѹ���ļ����м���̰���ͷ���ݵ�д�롣
/// </summary>

///�������⣺
/// �����ַ��Ľ�������������ļ��Ľ��������

#include "HuffmanTree.h"

class FileRW
{
private:
	HuffmanTree Tree;
	const char* filename;

public:
	//��ʼ�������������ļ�����׺�����ļ�ͷ�������ݻ���ļ����͡��Ӷ������ĸ������
	FileRw(const char* filename);

	//��ʼ������
	bool initFileRW();

	//�����ļ���,Դ���ļ��������ļ�ת��
	bool codeF2decodF(const char* tofile);

	//ȡ��λ��һ���ֽں�������������ļ���ѹ���ļ�ת��
	bool decodF2comF(const char* tofile);

	//һ���ֽڲ�ֳɰ�λ���������ѹ���ļ��������ļ�ת��
	bool comF2decodF(const char* tofile);

	//�����ļ���Դ���ļ�ת��
	bool decodF2codeF(const char* tofile);

	//�����м䲻���������ļ���ֱ��ԭ��תѹ���Ĺ��̡�
	//Դ���ļ���ѹ���ļ�ת����Ĭ��ɾ���м���ת�������ļ�
	bool codeF2decomF(const char* tofile,bool deleteDecodeFile = true);

	//�����м䲻���������ļ���ֱ��ѹ��תԭ��Ĺ��̡�
	//ѹ���ļ���Դ���ļ�ת����Ĭ��ɾ���м���ת�������ļ�
	bool comF2decodF(const char* tofile, bool deleteDecodeFile = true);
};

