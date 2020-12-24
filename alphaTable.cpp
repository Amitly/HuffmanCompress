#include "alphaTable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <map>

#define Size 50

alphaTable::alphaTable(const char* filename, bool isComFile)
{
	this->SIZE = Size + 1;
	this->alpNum = 0;
	this->alpTab = new Alpha[SIZE];
	if (isComFile) {
		if (!getAlpTab_Hdata(filename)) exit(0);
	}
	else 
		if (!getAlpTab_File(filename)) exit(0);
}

bool alphaTable::getAlpTab_File(const char* filename)
{
	//Size过小，会触发程序异常,在print(访问函数)出现异常
	//unsigned hash[257];
	//memset(hash, -1, sizeof(hash));
	std::map<char, int>hash;
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open()) return false;
	char ch;
	while (fin.read(&ch,sizeof(ch))) {
		if (hash[ch] == 0) {
			alpNum++;
			//空间不足，开辟另外的空间
			if (alpNum >= SIZE) {
				Alpha* temp = new Alpha[SIZE + Size];
				for (unsigned i = 1; i < SIZE; ++i) {
					temp[i].ch = alpTab[i].ch;
					temp[i].fre = alpTab[i].fre;
				}
				Alpha* m = alpTab; alpTab = temp; delete m;
				SIZE += Size;
			}
			if (alpNum < SIZE) {
				alpTab[alpNum].fre = 1;
				alpTab[alpNum].ch = (ch);
			}
			hash[ch] = alpNum;
			//alpNum++;
		}
		else {
			alpTab[hash[ch]].fre++;
		}
	}
	return true;
}

unsigned alphaTable::getAlpNum()
{
	return this->alpNum;
}

bool alphaTable::sortAlpTab()
{
	std::sort(this->alpTab, this->alpTab + this->alpNum);
	return true;
}

bool alphaTable::writeHdataToFile(const char* filename)
{
	std::ofstream fout(filename, std::ios::out | std::ios::binary);
	if (!fout.is_open()) return false;
	fout.write((char*)&alpNum,sizeof(alpNum));
	for (unsigned i = 1; i <= alpNum; ++i) {
		fout.write((char*)&alpTab[i], sizeof(Alpha));
	}
	return true;
}

bool alphaTable::getAlpTab_Hdata(const char* filename)
{
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if(!fin.is_open()) return false;
	fin.read((char*)&alpNum, sizeof(alpNum));
	for (int i = 1; i <= alpNum; ++i) {
		fin.read((char*)&alpTab[i], sizeof(Alpha));
	}
	return true;
}

void alphaTable::print()
{
	for (int i = 1; i <= alpNum; ++i) {
		printf("%c", alpTab[i].ch);
		std::cout << "："<<alpTab[i].fre << ' ';
	}
	std::cout << std::endl;
}
