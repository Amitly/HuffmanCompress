#pragma once

//文件读写类
/// <summary>
/// 利用原码文件获得字母表,建立哈夫曼树，直接对文件进行操作，获得编码文件，直接对编码文件进行操作，
/// 获得压缩文件，中间过程包括头数据的写入。
/// </summary>

///存在问题：
/// 中文字符的解决方案；超长文件的解决方案。

#include "HuffmanTree.h"

class FileRW
{
private:
	HuffmanTree Tree;
	const char* filename;

public:
	//初始化函数，根据文件名后缀，或文件头数据内容获得文件类型。从而获得字母表建树。
	FileRw(const char* filename);

	//初始化函数
	bool initFileRW();

	//返回文件名,源码文件向译码文件转换
	bool codeF2decodF(const char* tofile);

	//取八位做一个字节函数在这里，译码文件向压缩文件转换
	bool decodF2comF(const char* tofile);

	//一个字节拆分成八位函数在这里，压缩文件向译码文件转换
	bool comF2decodF(const char* tofile);

	//译码文件向源码文件转换
	bool decodF2codeF(const char* tofile);

	//考虑中间不创立译码文件，直接原码转压缩的过程。
	//源码文件向压缩文件转换，默认删除中间中转的译码文件
	bool codeF2decomF(const char* tofile,bool deleteDecodeFile = true);

	//考虑中间不创立译码文件，直接压缩转原码的过程。
	//压缩文件向源码文件转换，默认删除中间中转的译码文件
	bool comF2decodF(const char* tofile, bool deleteDecodeFile = true);
};

