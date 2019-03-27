#ifndef CMS_H
#define CMS_H

#include<fstream>

class CMS
{
private:
	struct cmstable
	{
		unsigned int ID;
		int num;
	};
	int **hashtable;
	const int hang = 3;
	const int lie=500;
	cmstable *minheaptree;
	const int k = 35;   //topk流


public:
	CMS();
	~CMS();
	void createTable(int l); //创建hash数组
	int algorithm1(unsigned int info);  //hash算法1
	int algorithm2(unsigned int info);  //hash算法2
	int algorithm3(unsigned int info);  //hash算法3
	void storeIn(unsigned int info);    //存入数组
	int chooseMin(unsigned int info);  //选择hash数组中最小的
	void minheap(unsigned int id, int num);
	void heapsoft(cmstable* heap);
	void shifDown(int start, int end, cmstable* heap);
	void outputtopk();//输出最大流
	void outfiletopk(std::string filename);//输出最大流(文件)

};

#endif
