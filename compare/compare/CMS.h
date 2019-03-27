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
	const int k = 35;   //topk��


public:
	CMS();
	~CMS();
	void createTable(int l); //����hash����
	int algorithm1(unsigned int info);  //hash�㷨1
	int algorithm2(unsigned int info);  //hash�㷨2
	int algorithm3(unsigned int info);  //hash�㷨3
	void storeIn(unsigned int info);    //��������
	int chooseMin(unsigned int info);  //ѡ��hash��������С��
	void minheap(unsigned int id, int num);
	void heapsoft(cmstable* heap);
	void shifDown(int start, int end, cmstable* heap);
	void outputtopk();//��������
	void outfiletopk(std::string filename);//��������(�ļ�)

};

#endif
