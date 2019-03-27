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
	const int w = 100;  //���ڴ�Сw  
	lctable *minheaptree;
	const int k = 35;   //topk��
	int num = 0;


public:
	LC();
	~LC();
	void insert(unsigned int info);//����һ����
	void delete_one();  //ÿ�����ڽ���ɾ������Ϊ1����
	void windowsize(unsigned int info);
	void minheap();
	void heapsoft(lctable* heap);
	void shifDown(int start, int end, lctable* heap);
	void outputtopk();//��������
	void outfiletopk(std::string filename);//�����������ļ���

};

#endif