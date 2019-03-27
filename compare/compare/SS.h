#ifndef SS_H
#define SS_H

#include<iostream>

class SS
{
private:
	struct valueNode {
		int num;
		valueNode * pre;
		valueNode * next;
		int flow;
	};

	struct flowNode{
		unsigned int ID;
		int replace;
		valueNode * fa;
		int bro;
	};

	struct sstable {
		unsigned int ID;
		int num;
	};

	valueNode * head;
	flowNode * flowtable;
	sstable *minheaptree;
	const int m = 35;  //���������������
	const int store = 10*m;



public:
	SS();
	~SS();
	int searchflow(unsigned int info);
	void insertflow(unsigned int info);
	void deleteson(int num);//ɾ����Ͱ
	void changefather(int num); //���ĸ�Ͱ
	void minheap();
	void heapsoft(sstable* heap);
	void shifDown(int start, int end, sstable* heap);
	void outfiletopk();//��������(�ļ�)
	void outmhtopk(std::string filename);//��������(mh)

};

#endif
