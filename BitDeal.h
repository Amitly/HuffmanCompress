#pragma once

//��һ��char���͵�8λ���в����ĺ�������װ��һ����
class BitDeal
{
public:
	unsigned getBit(char& c, int i) {
		return (c >> i) & 1;
	}
	void setBit(char& c, int i, int v) {
		if (v)
			c |= (1 << i);
		else
			c &= ~(1 << i);
	}
};