#include"LC.h"
#include<iostream>
#include <fstream>
using namespace std;

LC::LC()
{
	first = new lcNode;
	first->ID = -1;
	first->num = -1;
	first->next = NULL;

	minheaptree = new lctable[k];
	for (int i = 0; i < k; i++)
	{
		minheaptree[i].ID = 0;
		minheaptree[i].num = 99999;
	}
}

LC::~LC()
{
	lcNode* tempptr = NULL;
	while (first->next != NULL)
	{
		tempptr = first->next;
		delete first;
		first = tempptr;
	}
	delete first;

	//删除minheap数组
	delete[]minheaptree;
}

void LC::insert(unsigned int info)
{
	bool newflow = true;
	lcNode* temp = NULL;
	temp = first;

	while (temp->next != NULL)
	{
		if (temp->next->ID == info)
		{
			temp->next->num++;
			newflow = false;
			break;
		}
		else
		{
			temp = temp->next;
		}
	}

	if (newflow)
	{
		lcNode* nf = new lcNode;
		nf->ID = info;
		nf->num = 1;
		nf->next = NULL;
		temp->next = nf;
	}
}

void LC::delete_one()
{
	lcNode* temp = NULL;
	lcNode* p = NULL;
	temp = first;
	while (temp->next != NULL)
	{
		p = temp->next;
		if (p->num == 1)
		{
			temp->next = p->next;
			delete p;
			p = NULL;
		}
		else
		{
			temp = temp->next;
		}
	}

}

void LC::windowsize(unsigned int info)
{
	if (num < w)
	{
		insert(info);
		num++;
	}
	else
	{
		delete_one();
		insert(info);
		num = 1;
	}
}


void LC::minheap()
{
	lcNode *temp = first->next;
	int c = 0;
	while (temp != NULL)
	{
		if (c < k)
		{
			minheaptree[c].ID = temp->ID;
			minheaptree[c].num = temp->num;
			heapsoft(minheaptree);
			c++;
		}
		else
		{
			if (minheaptree[0].num < temp->num)
			{
				minheaptree[0].ID = temp->ID;
				minheaptree[0].num = temp->num;
				heapsoft(minheaptree);
			}
		}
		temp = temp->next;
	}
}


void LC::heapsoft(lctable* heap)
{
	int currentPos = (k - 2) / 2;                       //临时变量，指向最后一个有叶节点的堆
	while (currentPos >= 0) {
		shifDown(currentPos, k - 1, heap);                    //自底向上(对于整个堆而言)-自上而下(对于局部堆而言)调整为堆
		currentPos--;
	}
}


void LC::shifDown(int start, int end, lctable* heap) {
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

void LC::outputtopk()
{
	minheap();
	for (int i = k - 1; i >= 0; i--)
		cout << minheaptree[i].ID << "     " << minheaptree[i].num << endl;
}

void LC::outfiletopk(string filename)
{
	ofstream fout(filename+".csv");
	fout << "流号,数量" << endl;
	minheap();
	for (int i = k - 1; i >= 0; i--)
		fout<< minheaptree[i].ID << "," << minheaptree[i].num << endl;
}