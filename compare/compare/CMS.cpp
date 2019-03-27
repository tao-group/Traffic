#include"CMS.h"
#include<iostream>
#include <fstream>
#
using namespace std;

CMS::CMS()
{
	createTable(lie);

	minheaptree = new cmstable[k];
	for (int i = 0; i < k; i++)
	{
		minheaptree[i].ID = 0;
		minheaptree[i].num = 99999;
	}

}

CMS::~CMS()
{
	//ɾ��hash���� 
	for (int i = 0; i < hang; i++)
		delete[] hashtable[i];
	delete[]hashtable;

	//ɾ��minheap����
	delete[]minheaptree;
}

void CMS::createTable(int l)
{
	hashtable = new int *[hang];
	for (int i = 0; i < hang; i++)
		hashtable[i] = new int[l];

	//�����ʼ��
	for (int m = 0; m < hang; m++)
	{
		for (int k = 0; k < lie; k++)
		{
			hashtable[m][k]= 0;
		}
	}
}

int CMS::algorithm1(unsigned int info)
{
	return (info%lie);
}

int CMS::algorithm2(unsigned int info)
{
	return (info/7%lie);
}

int CMS::algorithm3(unsigned int info)
{
	return (info/2%lie);
}


void CMS::storeIn(unsigned int info)
{
	hashtable[0][algorithm1(info)]++;
	hashtable[1][algorithm2(info)]++;
	hashtable[2][algorithm3(info)]++;

	minheap(info, chooseMin(info));
}

int CMS::chooseMin(unsigned int info)
{
	int min = 0;
	min = (hashtable[0][algorithm1(info)] <= hashtable[1][algorithm2(info)]) ? hashtable[0][algorithm1(info)]:hashtable[1][algorithm2(info)];
	min = (min <= hashtable[2][algorithm3(info)]) ? min : hashtable[2][algorithm3(info)];
	return min;
}

void CMS::minheap(unsigned int id, int num)
{
	int c = 0;
	while (minheaptree[c].ID != 0 && minheaptree[c].ID != id)
		c++;
	if (c < k)
	{
		if (minheaptree[k - 1].ID == 0)//����δ��
		{
			minheaptree[c].ID = id;
			minheaptree[c].num = num;
			heapsoft(minheaptree);
		}
		else//ԭ�����а�������
		{
			minheaptree[c].num = num;
			heapsoft(minheaptree);
		}
	}
	else//��������
	{
		if (minheaptree[0].num < num)
		{
			minheaptree[0].ID = id;
			minheaptree[0].num = num;
			heapsoft(minheaptree);
		}
	}
}

void CMS::heapsoft(cmstable* heap)
{
	int currentPos = (k - 2) / 2;                       //��ʱ������ָ�����һ����Ҷ�ڵ�Ķ�
	while (currentPos >= 0) {
		shifDown(currentPos, k - 1, heap);                    //�Ե�����(���������Ѷ���)-���϶���(���ھֲ��Ѷ���)����Ϊ��
		currentPos--;
	}
}


void CMS::shifDown(int start, int end, cmstable* heap) {
	//˽�к������ӽ��start��ʼ����endΪֹ���������±Ƚϣ����
	//��Ů��ֵС�ڸ��ڵ��ֵ����ؼ���С��ֵ�ϸ����������²�Ƚ�
	//������һ�����Ͼֲ�����Ϊ��С��
	int i = start;
	int j = 2 * i + 1;                        //ָ��i������
	int tempId = heap[i].ID;
	int tempValue = heap[i].num;                      //��ʱ�����±�Ϊstart����ֵ
	while (j <= end) {                             //δ�ﵽend������㣬һֱѭ��
		if (j < end && heap[j].num > heap[j + 1].num)    //������ҽ�㣬�����ҽ��С������
			j++;                                    //j��ָ���ҽ��
		if (tempValue <= heap[j].num)                 //������ڵ�С�ڵ������ҽ�㣬��ֱ�ӽ�����һ��ѭ��
			break;
		else {
			heap[i].num = heap[j].num;
			heap[i].ID = heap[j].ID;                //�����ӽ���ֵ��ֵ�����ڵ�
			i = j;                                   //ʹiָ���ӽڵ�
			j = 2 * i + 1;                           //jָ��i���ӽ��
		}
	}
	heap[i].ID = tempId;
	heap[i].num = tempValue;                            //�ط�
}

void CMS::outputtopk()
{
	for (int i = k - 1; i >= 0; i--)
		cout << minheaptree[i].ID << "     " << minheaptree[i].num << endl;
}

void CMS::outfiletopk(string filename)
{
	ofstream fout(filename+".csv");
	fout << "����,����" << endl;
	for (int i = k - 1; i >= 0; i--)
		fout << minheaptree[i].ID << "," << minheaptree[i].num << endl;
}