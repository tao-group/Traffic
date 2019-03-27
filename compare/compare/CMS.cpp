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
	//删除hash数组 
	for (int i = 0; i < hang; i++)
		delete[] hashtable[i];
	delete[]hashtable;

	//删除minheap数组
	delete[]minheaptree;
}

void CMS::createTable(int l)
{
	hashtable = new int *[hang];
	for (int i = 0; i < hang; i++)
		hashtable[i] = new int[l];

	//数组初始化
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
		if (minheaptree[k - 1].ID == 0)//数组未满
		{
			minheaptree[c].ID = id;
			minheaptree[c].num = num;
			heapsoft(minheaptree);
		}
		else//原数组中包含该流
		{
			minheaptree[c].num = num;
			heapsoft(minheaptree);
		}
	}
	else//数组已满
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
	int currentPos = (k - 2) / 2;                       //临时变量，指向最后一个有叶节点的堆
	while (currentPos >= 0) {
		shifDown(currentPos, k - 1, heap);                    //自底向上(对于整个堆而言)-自上而下(对于局部堆而言)调整为堆
		currentPos--;
	}
}


void CMS::shifDown(int start, int end, cmstable* heap) {
	//私有函数：从结点start开始，到end为止，自上向下比较，如果
	//子女的值小于父节点的值，则关键码小的值上浮，继续向下层比较
	//这样将一个集合局部调整为最小堆
	int i = start;
	int j = 2 * i + 1;                        //指向i的左结点
	int tempId = heap[i].ID;
	int tempValue = heap[i].num;                      //临时保存下标为start结点的值
	while (j <= end) {                             //未达到end结束结点，一直循环
		if (j < end && heap[j].num > heap[j + 1].num)    //如果有右结点，并且右结点小于左结点
			j++;                                    //j就指向右结点
		if (tempValue <= heap[j].num)                 //如果父节点小于等于左右结点，就直接进行下一层循环
			break;
		else {
			heap[i].num = heap[j].num;
			heap[i].ID = heap[j].ID;                //否则将子结点的值赋值给父节点
			i = j;                                   //使i指向子节点
			j = 2 * i + 1;                           //j指向i的子结点
		}
	}
	heap[i].ID = tempId;
	heap[i].num = tempValue;                            //回返
}

void CMS::outputtopk()
{
	for (int i = k - 1; i >= 0; i--)
		cout << minheaptree[i].ID << "     " << minheaptree[i].num << endl;
}

void CMS::outfiletopk(string filename)
{
	ofstream fout(filename+".csv");
	fout << "流号,数量" << endl;
	for (int i = k - 1; i >= 0; i--)
		fout << minheaptree[i].ID << "," << minheaptree[i].num << endl;
}