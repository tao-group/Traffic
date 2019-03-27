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

	//ɾ��minheap����
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
	int currentPos = (k - 2) / 2;                       //��ʱ������ָ�����һ����Ҷ�ڵ�Ķ�
	while (currentPos >= 0) {
		shifDown(currentPos, k - 1, heap);                    //�Ե�����(���������Ѷ���)-���϶���(���ھֲ��Ѷ���)����Ϊ��
		currentPos--;
	}
}


void LC::shifDown(int start, int end, lctable* heap) {
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

void LC::outputtopk()
{
	minheap();
	for (int i = k - 1; i >= 0; i--)
		cout << minheaptree[i].ID << "     " << minheaptree[i].num << endl;
}

void LC::outfiletopk(string filename)
{
	ofstream fout(filename+".csv");
	fout << "����,����" << endl;
	minheap();
	for (int i = k - 1; i >= 0; i--)
		fout<< minheaptree[i].ID << "," << minheaptree[i].num << endl;
}