#pragma once

//��ĸ�ṹ��

typedef struct Alpha{

	//��ʾ�ַ�
	unsigned char ch;
	//�ַ�����Ƶ��
	unsigned fre;

	//��С�ȽϹ����������Ϊ�˺�����������Ľ���
	bool operator < (const Alpha& other) {
		if (fre != other.fre) return fre < other.fre;
		return ch < other.ch;
	}

}Alpha;