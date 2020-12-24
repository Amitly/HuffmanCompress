#include "FileRW.h"
#include <fstream>
#include <string>
#include <cstring>
#include "BitDeal.h"

//�����
//ȡchar���͵ĵڼ�λ
#define 
//��char���͵ĵڼ�λ��ֵΪ0��1
#define 

FileRW::FileRW(const char* filename)
{
	//��ô�ֱ��ļ����Ǹ����⣬���ܻ���ڴ�����bug,����ʱ�������ֺ�׺���ļ�ͷ���ݵ�˫�ط�ʽȷ��
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

	//���벢ѹ������
	BitDeal BD;
	char ch;
	char value;
	int bitnum = 1;
	while (fin.read(&ch,sizeof(char))) {
		std::string code = this->Tree.Ch_2_01Str(ch);
		for (const auto& it : code) {
			//����bitnumλת����it;
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
	//bitnum�ĺ���:ȡch�ĵڼ�λ
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
	//ʣ���ַ�Ҳ�����ˣ�����û�е��ԣ��Ϳ���ô�ӹ������������ַ���
	/*���ݹ�����������,�ҵ��Ǹ��ַ�*/
	/*˼·�ǹ�����������һ���ַ�����Ȼ�󷵻�һ����������ض�Ӧ���ַ����������ַ�����������
	* ����ǽ��ļ���������Ļ����Ͳ��翪ʼ��ʱ���ֱ�Ӱ��ļ������ࣨ��ȡ���ļ���Ĳ�����
	* ����ǽ�����ָ�봫�����Ļ�����ô�൱�ڽ�����������У������ķ�װ�Ծ�ʧ���ˡ�
	*/
	return false;
}
