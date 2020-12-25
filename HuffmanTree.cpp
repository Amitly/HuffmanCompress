//#pragma warning(disable:6385 6386)

#include "HuffmanTree.h"

bool HuffmanTree::initHTree(alphaTable& alT)
{
	if (alT.alpNum < 1) return false;
	this->alT = alT;
	HTree = new HNode[alT.alpNum + 1];
	if (!HTree) return false;
	HCode = new std::string[alT.alpNum + 1];
	if (!HCode) return false;
	this->alT.sortAlpTab();
	for (unsigned i = 1; i <= alT.alpNum; ++i) {
		Alpha temp = alT.alpTab[i];
		hash[temp.ch] = i;
		HTree[i].initHNode((unsigned)temp.fre);
	}
	if (!buildTree()) return false;
	if (!buildCode()) return false;
	return true;
}

bool HuffmanTree::buildCode()
{//O(n)：遍历二叉树的时间复杂度，函数待测试
	if (alT.alpNum == 1) {
		HCode[1] = "0";
		return true;
	}
	std::string str = "\0";
	unsigned root = 2 * alT.alpNum - 1;
	for (unsigned i = 1; i <= root; ++i) {
		HTree[i].weight = 0;
	}
	unsigned p = root;
	while (p) {
		if (HTree[p].weight == 0) {
			HTree[p].weight = 1;
			if (HTree[p].lch != 0) {
				p = HTree[p].lch;
				str.push_back('0');
			}
			else if (HTree[p].rch == 0) {
				HCode[p] = str;
			}
		}
		else if (HTree[p].weight == 1) {
			HTree[p].weight = 2;
			if (HTree[p].rch != 0) {
				p = HTree[p].rch;
				str.push_back('1');
			}
		}
		else {
			HTree[p].weight = 0;
			p = HTree[p].par;
			str.pop_back();
		}
	}
	return true;
}

HuffmanTree::HuffmanTree(alphaTable& alT)
{
	if(!initHTree(alT))
		exit(0);
}

HNode* HuffmanTree::getTree()
{
	return HTree;
}

std::string HuffmanTree::Ch_2_01Str(char ch)
{
	return HCode[hash[ch]];
}

alphaTable& HuffmanTree::getAlphaTable()
{
	return this->alT;
}
