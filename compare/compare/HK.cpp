#include"HK.h"
#include<iostream>
#include<fstream>
#include<math.h>
#include<time.h>
using namespace std;

HK::HK()
{
	srand(time(NULL)); //�������������
	createTable(lie);

	minheaptree = new hktable[k];
	for (int i = 0; i < k; i++)
	{
		minheaptree[i].ID = 0;
		minheaptree[i].num = 99999;
	}
}

HK::~HK()
{   
	//ɾ��hash���� 
	for (int i = 0; i < hang; i++)
		delete[] hashtable[i];
	delete[]hashtable;

	//ɾ��minheap����
	delete[]minheaptree;

}

void HK::createTable(int lie)
{
	hashtable = new hktable *[hang];
	for (int i = 0; i < hang; i++)
		hashtable[i] = new hktable[lie];

	//�����ʼ��
	for (int m = 0; m < hang; m++)
	{
		for (int k = 0; k < lie; k++)
		{
			hashtable[m][k].ID = 0;
			hashtable[m][k].num = 0;
		}
	}
}

int HK::algorithm1(unsigned int info)
{
	return (info%lie);
}

int HK::algorithm2(unsigned int info)
{
	return (info/3 % lie);
}

bool HK::randomRed(int num)
{
	double p = 100/(pow(b, num));
	//cout << p << endl;
	int randNum; //�����
	randNum = rand() * 100 / (RAND_MAX + 1); //����0-99֮��������
	//cout << randNum << endl << endl;
	if (randNum < p)
		return true;
	else
		return false;
}

void HK::storeIn(unsigned int info)
{
	int a1 = algorithm1(info);
	int a2 = algorithm2(info);
	//hash�㷨1
	if (hashtable[0][a1].num == 0)
	{
		hashtable[0][a1].ID = info;
		hashtable[0][a1].num = 1;
	}
	else if (info == hashtable[0][a1].ID)
	{
		hashtable[0][a1].num++;
	}
	else if ((info != hashtable[0][a1].ID) && (hashtable[0][a1].num > 0))
	{
		if (randomRed(hashtable[0][a1].num))
			hashtable[0][a1].num--;
	}
	//hash�㷨2
	if (hashtable[1][a2].num == 0)
	{
		hashtable[1][a2].ID = info;
		hashtable[1][a2].num = 1;
	}
	else if (info == hashtable[1][a2].ID)
	{
		hashtable[1][a2].num++;
	}
	else if ((info != hashtable[1][a2].ID) && (hashtable[1][a2].num > 0))
	{
		if (randomRed(hashtable[1][a2].num))
			hashtable[1][a2].num--;
	}

	minheap(info, chooseMax(info));
}


int HK::chooseMax(unsigned int info)
{
	if (hashtable[0][algorithm1(info)].ID == hashtable[1][algorithm2(info)].ID)
	{
		int max = ((hashtable[0][algorithm1(info)].num) >= (hashtable[1][algorithm2(info)].num)) ? hashtable[0][algorithm1(info)].num : hashtable[1][algorithm2(info)].num;
		return max;
	}
	else
		return -1;
}

void HK::minheap(unsigned int id, int num)
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
		if ((minheaptree[0].num < num )&&((minheaptree[0].num+1) >= num))
		{
			minheaptree[0].ID = id;
			minheaptree[0].num = num;
			heapsoft(minheaptree);
		}
	}
}

void HK::heapsoft(hktable* heap)
{
	int currentPos = (k - 2) / 2;                       //��ʱ������ָ�����һ����Ҷ�ڵ�Ķ�
	while (currentPos >= 0) {
		shifDown(currentPos, k - 1,heap);                    //�Ե�����(���������Ѷ���)-���϶���(���ھֲ��Ѷ���)����Ϊ��
		currentPos--;
	}
}


void HK::shifDown(int start ,int end,hktable* heap) {
	//˽�к������ӽ��start��ʼ����endΪֹ���������±Ƚϣ����
	//��Ů��ֵС�ڸ��ڵ��ֵ����ؼ���С��ֵ�ϸ����������²�Ƚ�
	//������һ�����Ͼֲ�����Ϊ��С��
	int i = start;
	int j = 2 * i + 1;                        //ָ��i������
	int tempId = heap[i].ID;
	int tempValue = heap[i].num;                      //��ʱ�����±�Ϊstart����ֵ
	while (j <=end) {                             //δ�ﵽend������㣬һֱѭ��
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

void HK::outputtopk()
{
	for (int i = k - 1; i >= 0; i--)
		cout << minheaptree[i].ID << "     " << minheaptree[i].num << endl;
}

void HK::outfiletopk(string filename)
{
	ofstream fout(filename+".csv");
	fout << "����,����" << endl;
	for (int i = k - 1; i >= 0; i--)
		fout<< minheaptree[i].ID << "," << minheaptree[i].num << endl;
}