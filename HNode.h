#pragma once

//�����������

class HNode
{
//��Ϊ����Ȩ�ޣ���������Ϊ�����п��ܶ�ȫ�����ݽ����޸ĺͻ�á���ʱ��������
public:
	//����Ȩ��
	unsigned weight;
	//���Һ��ӽ��
	unsigned lch, rch;
	//˫�׽��
	unsigned par;

public:
	//���캯��
	HNode(unsigned wei = 0, unsigned l = 0, unsigned r = 0, unsigned par = 0);

	//��ʼ������
	bool initHNode(unsigned wei = 0, unsigned l = 0, unsigned r = 0, unsigned par = 0);

	//���ϲ�����
	HNode mergeHNode(const HNode& other,unsigned l = 0,unsigned r = 0,unsigned par = 0);

	//��С�ȽϹ�����趨�������ں�������Ľ��С�
	bool operator< (const HNode& other);

};

