#ifndef HK_H
#define HK_H

#include<iostream>

class HK
{
private:
	struct hktable {
		unsigned int ID;
		int num;
	};
	hktable **hashtable;
	hktable *minheaptree;
	const int hang = 2;
	const int lie=500;
	const double b = 1.08;  //减少概率
	const int k = 35;   //topk流


public:
	HK();
	~HK();
	void createTable(int lie); //创建hash数组
	int algorithm1(unsigned int info);  //hash算法1
	int algorithm2(unsigned int info);  //hash算法2
	bool randomRed(int num);   //判断是否减少num
	void storeIn(unsigned int info);    //存入数组
	int chooseMax(unsigned int info);  //选择hash数组中最大的
	void minheap(unsigned int id, int num);
	void heapsoft(hktable* heap);
	void shifDown(int start,int end,hktable* heap);
	void outputtopk();//输出最大流
	void outfiletopk(std::string filename);//输出最大流(文件)

};

#endif
