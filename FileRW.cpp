#include "FileRW.h"
#include <fstream>
#include <string>
#include <cstring>
#include "BitDeal.h"

//定义宏
//取char类型的第几位
#define 
//将char类型的第几位赋值为0或1
#define 

FileRW::FileRW(const char* filename)
{
	//怎么分辨文件，是个问题，可能会存在大量的bug,现暂时采用名字后缀和文件头数据的双重方式确认
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) exit(0);

	char a[4] = { 0 };
	fin.read(a, sizeof(a));
	std::string namestr(filename);
	namestr = namestr.substr(namestr.length() - 4, 3);
	std::string headstr(a);
	if (headstr == namestr) {
		if (headstr == "cpr")
			fileType = 2;
		else if (headstr == "dec")
			fileType = 3;
		else exit(0);
	}
	else if (namestr == "txt" || namestr == "bmp")
		fileType = 1;
	else exit(0);

	fin.close();

	if (fileType == 1) {
		Tree.initHTree(*(new alphaTable(filename, false)));
	}
	else if (fileType == 2) {
		Tree.initHTree(*(new alphaTable(filename, true, sizeof(a))));
	}
	else;
}

bool FileRW::decodF2comF(const char* tofile)
{
	return false;
}

bool FileRW::codeF2comF(const char* tofile)
{
	if (fileType != 1) return false;
	std::ofstream fout(tofile, std::ios::out | std::ios::binary);
	if (!fout.is_open()) return false;
	char a[4] = "cpr";
	fout.write(a, sizeof(a));
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return false;

	//编码并压缩过程
	BitDeal BD;
	char ch;
	char value;
	int bitnum = 1;
	while (fin.read(&ch,sizeof(char))) {
		std::string code = this->Tree.Ch_2_01Str(ch);
		for (const auto& it : code) {
			//将第bitnum位转化成it;
			BD.setBit(value, bitnum, it - '0');
			if (bitnum++ == 8) {
				fout.write(&value, sizeof(value));
				bitnum = 1;
			}
		}
		if (fin.eof()) {
			if (bitnum != 1)) leaveBitNum = 0;
			else {
				fout.write(&value, sizeof(value));
				leaveBitNum = 9 - bitnum;
			}
			break;
		}
	}

	fin.close();
	fout.close();
	return true;
}

bool FileRW::comF2codF(const char* tofile)
{
	if (fileType != 3) return false;

	std::ofstream fout(tofile, std::ios::out | std::ios::binary);
	if (!fout.is_open()) return false;
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return false;
	alphaTable &ALP = Tree.getAlphaTable();
	int indx =	sizeof("cpr") + 
				sizeof(ALP.getAlpNum()) + 
				ALP.getAlpNum() * (sizeof(ALP.alpTab[0].ch) + 
				sizeof(ALP.alpTab[0].fre));
	fin.seekg(indx);

	BitDeal BD;
	char ch;
	//bitnum的含义:取ch的第几位
	int bitnum = 9;
	unsigned num;
	HNode* tree = Tree.getTree(); int n = Tree.getAlphaTable().alpNum;
	int p = 2 * n - 1;
	while (!fin.eof() || (bitnum <= sizeof(char) - leaveBitNum)) {
		if (bitnum > 8) {
			fin.read(&ch, sizeof(char));
			bitnum = 1;
		}
		num = BD.getBit(ch, bitnum++);
		if (num)
			p = tree[p].rch ? tree[p].rch : p;
		else
			p = tree[p].lch ? tree[p].lch : p;
		if ((!tree[p].lch) && (!tree[p].rch)) {
			char c = Tree.getAlphaTable().alpTab[p].ch;
			fout.write(&c, sizeof(c));
			p = 2 * n - 1;
		}
	}
	//剩余字符也考虑了，但是没有调试，就看怎么从哈夫曼树里获得字符了
	/*根据哈夫曼树回溯,找到那个字符*/
	/*思路是哈夫曼树类获得一个字符串，然后返回一个结果，返回对应的字符，或异类字符（？？？）
	* 如果是将文件名给树类的话，就不如开始的时候就直接把文件给树类（即取消文件类的操作）
	* 如果是将树的指针传出来的话，那么相当于解码在树外进行，对树的封装性就失败了。
	*/
	return false;
}
