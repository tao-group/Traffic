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
	const double b = 1.08;  //���ٸ���
	const int k = 35;   //topk��


public:
	HK();
	~HK();
	void createTable(int lie); //����hash����
	int algorithm1(unsigned int info);  //hash�㷨1
	int algorithm2(unsigned int info);  //hash�㷨2
	bool randomRed(int num);   //�ж��Ƿ����num
	void storeIn(unsigned int info);    //��������
	int chooseMax(unsigned int info);  //ѡ��hash����������
	void minheap(unsigned int id, int num);
	void heapsoft(hktable* heap);
	void shifDown(int start,int end,hktable* heap);
	void outputtopk();//��������
	void outfiletopk(std::string filename);//��������(�ļ�)

};

#endif
