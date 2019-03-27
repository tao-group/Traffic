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
	if (charge == -1)//新的元素
	{
		if (flowtable[store - 1].ID == 0)//元素未满
		{
			int count = 0;
			while (flowtable[count].ID != 0)
				count++;
			flowtable[count].ID = info;

			if (head->next == NULL)//父桶为空
			{
				valueNode * nf = new valueNode;
				nf->next = NULL;
				nf->pre = head;
				head->next = nf;
				nf->num = 1;
				nf->flow = count;
				flowtable[count].fa = nf;
			}
			else if (head->next->num == 1)//父桶有值为1的桶
			{
				flowtable[count].bro = head->next->flow;
				flowtable[count].fa = head->next;
				head->next->flow = count;
			}
			else//父桶没有值为1的桶
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
		else//元素已满
		{
			valueNode * temp = head->next;

			//寻找被替换的元素
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

			//替换元素
			flowtable[re].ID = info;
			flowtable[re].replace = temp->num;
			deleteson(re);
			changefather(re);
			
		}

	}
	else//原有的元素
	{
		//子桶删除操作
		deleteson(charge);
		//父桶操作
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
	int currentPos = (m - 2) / 2;                       //临时变量，指向最后一个有叶节点的堆
	while (currentPos >= 0) {
		shifDown(currentPos, m - 1, heap);                    //自底向上(对于整个堆而言)-自上而下(对于局部堆而言)调整为堆
		currentPos--;
	}
}


void SS::shifDown(int start, int end, sstable* heap) {
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

void SS::outfiletopk()
{
	ofstream fout("SS.csv");
	fout << "流号,最低数量" << endl;

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
	fout << "流号,最低数量" << endl;

	minheap();
	for (int i = m - 1; i >= 0; i--)
		fout << minheaptree[i].ID << "," << minheaptree[i].num << endl;
}