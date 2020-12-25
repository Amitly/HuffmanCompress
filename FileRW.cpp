#include "FileRW.h"
#include <fstream>
#include <string>
#include <cstring>
#include "BitDeal.h"


FileRW::FileRW(const char* filename)
{
	if (!initFileRW(filename))
		exit(0);
}

bool FileRW::initFileRW(const char* filename)
{
	this->filename = filename;

	//1为原码文件，2为压缩后文件，3为译码文件，0为未操作文件。
	//怎么分辨文件，是个问题，可能会存在大量的bug,现暂时采用名字后缀和文件头数据的双重方式确认
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return false;

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
		else false;
	}
	else if (namestr == "txt" || namestr == "bmp")
		fileType = 1;
	else 
		return false;

	fin.close();

	if (fileType == 1) {
		Tree.initHTree(*(new alphaTable(filename, false)));
		leaveBitNum = initLeaveBitNum(filename);
		if (leaveBitNum = -1) return false;
	}
	else if (fileType == 2) {
		Tree.initHTree(*(new alphaTable(filename, true, sizeof(a) + sizeof(leaveBitNum))));
	}
	else ;
	return true;
}

int FileRW::initLeaveBitNum(const char* filename)
{
	if (fileType != 1) return -1;

	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return -1;

	char ch;
	int sum_bit = 0;
	while (fin.read(&ch, sizeof(char))) {
		std::string code = this->Tree.Ch_2_01Str(ch);
		sum_bit += code.length();
	}

	fin.close();

	return (sum_bit % sizeof(char));
}

bool FileRW::codeF2decodF(const char* tofile)
{
	std::ofstream fout(tofile, std::ios::out);
	char a[4] = "dec";
	fout.write(a,sizeof(a));
	Tree.getAlphaTable().writeHdataToFile(tofile, sizeof(a));

	std::ifstream fin(filename, std::ios::in);
	if(!fin.is_open())	return false;
	char ch;
	while (fin.get(ch)) {
		std::string code = Tree.Ch_2_01Str(ch);
		for (const auto& it : code) {
			fout.put(it);
		}
	}

	fin.close();
	fout.close();
	return true;
}


bool FileRW::codeF2comF(const char* tofile)
{ //在哪计算剩余bit数????,换句话说，压缩文件里leaveBitNum放在哪？，需要将整个文件都读过，才能知道leavebitnum。
  //先把剩余字节数放在文件后缀之后。
	if (fileType != 1) return false;

	std::ofstream fout(tofile, std::ios::out | std::ios::binary);
	if (!fout.is_open()) return false;
	char a[4] = "cpr";
	fout.write(a, sizeof(a));
	fout.write((char*)&leaveBitNum, sizeof(leaveBitNum));
	Tree.getAlphaTable().writeHdataToFile(tofile, sizeof(a) + sizeof(leaveBitNum));
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
			if (bitnum != 1) leaveBitNum = 0;
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
	if (fileType != 2) return false;

	std::ofstream fout(tofile, std::ios::out | std::ios::binary);
	if (!fout.is_open()) return false;
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return false;
	alphaTable &ALP = Tree.getAlphaTable();
	int indx =	sizeof("cpr") + 
				sizeof(leaveBitNum) +
				sizeof(ALP.getAlpNum()) + 
				ALP.getAlpNum() * (sizeof(ALP.alpTab[0].ch) + sizeof(ALP.alpTab[0].fre));
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
	fin.close();
	fout.close();
	return false;
}
