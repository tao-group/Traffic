#include"SS.h"
#include<iostream>
#include<fstream>
using namespace std;

SS::SS()
{
	flowtable = new flowNode[store];
	for (int i = 0; i < store; i++)
	{
		flowtable[i].ID = 0;
		flowtable[i].replace = 0;
		flowtable[i].fa = NULL;
		flowtable[i].bro = -1;
	}

	head = new valueNode;
	head->num = 0;
	head->pre = NULL;
	head->next = NULL;
	head->flow = -1;

	minheaptree = new sstable[m];
	for (int i = 0; i < m; i++)
	{
		minheaptree[i].ID = 0;
		minheaptree[i].num = 99999;
	}
}

SS::~SS()
{
	valueNode* tempptr = NULL;
	while (head->next != NULL)
	{
		tempptr = head->next;
		delete head;
		head = tempptr;
	}
	delete head;
	delete flowtable;
}

int SS::searchflow(unsigned int info)
{
	for (int i = 0; i < m; i++)
	{
		if (flowtable[i].ID == info)
			return i;
	}
	return -1;
}

void SS::deleteson(int num)
{
	valueNode * temp = flowtable[num].fa;
	if (temp->flow == num)
	{
		temp->flow = flowtable[num].bro;
	}
	else
	{
		int t = temp->flow;
		while (flowtable[t].bro != num)
		{
			t = flowtable[t].bro;
		}
		flowtable[t].bro = flowtable[num].bro;
	}
}

void SS::changefather(int num)
{
	valueNode * temp = flowtable[num].fa;
	if (temp->next == NULL)
	{
		valueNode * nf = new valueNode;
		nf->next = temp->next;
		nf->pre = temp;
		temp->next = nf;
		nf->num = temp->num + 1;
		nf->flow = num;
		flowtable[num].bro = -1;
		flowtable[num].fa = nf;
	}
	else if (temp->next->num == temp->num + 1)
	{
		flowtable[num].bro = temp->next->flow;
		flowtable[num].fa = temp->next;
		temp->next->flow = num;
	}
	else
	{
		valueNode * nf = new valueNode;
		nf->next = temp->next;
		nf->pre = temp;
		temp->next = nf;
		nf->next->pre = nf;
		nf->num = temp->num + 1;
		nf->flow = num;
		flowtable[num].bro = -1;
		flowtable[num].fa = nf;
	}

	if (temp->flow == -1)
	{
		temp->pre->next = temp->next;
		temp->next->pre = temp->pre;
		delete temp;
	}
}

void SS::insertflow(unsigned int info)
{
	int charge = searchflow(info);
	if (charge == -1)//�µ�Ԫ��
	{
		if (flowtable[store - 1].ID == 0)//Ԫ��δ��
		{
			int count = 0;
			while (flowtable[count].ID != 0)
				count++;
			flowtable[count].ID = info;

			if (head->next == NULL)//��ͰΪ��
			{
				valueNode * nf = new valueNode;
				nf->next = NULL;
				nf->pre = head;
				head->next = nf;
				nf->num = 1;
				nf->flow = count;
				flowtable[count].fa = nf;
			}
			else if (head->next->num == 1)//��Ͱ��ֵΪ1��Ͱ
			{
				flowtable[count].bro = head->next->flow;
				flowtable[count].fa = head->next;
				head->next->flow = count;
			}
			else//��Ͱû��ֵΪ1��Ͱ
			{
				valueNode * nf = new valueNode;
				nf->next = head->next;
				nf->pre = head;
				head->next = nf;
				nf->next->pre = nf;
				nf->num = 1;
				nf->flow = count;
				flowtable[count].fa = nf;
			}
		}
		else//Ԫ������
		{
			valueNode * temp = head->next;

			//Ѱ�ұ��滻��Ԫ��
			int re = temp->flow;
			int wt = flowtable[re].bro;
			int max = flowtable[re].replace;
			while (wt != -1)
			{
				if (flowtable[wt].replace > max)
				{
					max = flowtable[wt].replace;
					re = wt;
				}
				wt = flowtable[wt].bro;
			}

			//�滻Ԫ��
			flowtable[re].ID = info;
			flowtable[re].replace = temp->num;
			deleteson(re);
			changefather(re);
			
		}

	}
	else//ԭ�е�Ԫ��
	{
		//��Ͱɾ������
		deleteson(charge);
		//��Ͱ����
		changefather(charge);
	}
}

void SS::minheap()
{
	int c = 0;
	for (int i = 0; i < store;i++)
	{
		if (c < m)
		{
			minheaptree[c].ID = flowtable[i].ID;
			minheaptree[c].num = flowtable[i].fa->num - flowtable[i].replace;
			heapsoft(minheaptree);
			c++;
		}
		else
		{
			if (minheaptree[0].num < (flowtable[i].fa->num - flowtable[i].replace))
			{
				minheaptree[0].ID = flowtable[i].ID;
				minheaptree[0].num = flowtable[i].fa->num - flowtable[i].replace;
				heapsoft(minheaptree);
			}
		}
	}
}


void SS::heapsoft(sstable* heap)
{
	int currentPos = (m - 2) / 2;                       //��ʱ������ָ�����һ����Ҷ�ڵ�Ķ�
	while (currentPos >= 0) {
		shifDown(currentPos, m - 1, heap);                    //�Ե�����(���������Ѷ���)-���϶���(���ھֲ��Ѷ���)����Ϊ��
		currentPos--;
	}
}


void SS::shifDown(int start, int end, sstable* heap) {
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

void SS::outfiletopk()
{
	ofstream fout("SS.csv");
	fout << "����,�������" << endl;

	valueNode * temp = head->next;
	while (temp->next != NULL)
		temp = temp->next;
	
	int count = 0;
	while (temp != head &&count<m)
	{
		int out = temp->flow;
		while (out != -1)
		{
			count++;
			fout << flowtable[out].ID << "," << (temp->num-flowtable[out].replace )<< endl;
			out = flowtable[out].bro;
		}
		temp = temp->pre;
	}
}

void SS::outmhtopk(string filename)
{
	ofstream fout(filename+".csv");
	fout << "����,�������" << endl;

	minheap();
	for (int i = m - 1; i >= 0; i--)
		fout << minheaptree[i].ID << "," << minheaptree[i].num << endl;
}