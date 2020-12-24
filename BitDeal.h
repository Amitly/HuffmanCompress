#pragma once

//对一个char类型的8位进行操作的函数，封装成一个类
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