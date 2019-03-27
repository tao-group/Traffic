#ifndef LC_H
#define LC_H

#include<fstream>

class LC
{
private:
	struct lcNode {
		unsigned int ID;
		int num;
		lcNode * next;
	};

	struct lctable {
		unsigned int ID;
		int num;
	};

	lcNode * first;
	const int w = 100;  //窗口大小w  
	lctable *minheaptree;
	const int k = 35;   //topk流
	int num = 0;


public:
	LC();
	~LC();
	void insert(unsigned int info);//加入一个流
	void delete_one();  //每个窗口结束删除数量为1的流
	void windowsize(unsigned int info);
	void minheap();
	void heapsoft(lctable* heap);
	void shifDown(int start, int end, lctable* heap);
	void outputtopk();//输出最大流
	void outfiletopk(std::string filename);//输出最大流（文件）

};

#endif