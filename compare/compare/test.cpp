#include<iostream>
#include <fstream>
#include<string>
#include <sstream>
#include"CMS.h"
#include"HK.h"
#include"LC.h"
#include"SS.h"
using namespace std;

void check()
{
	const int datanum = 35;
	ifstream fin[9];
	fin[0].open("top100.txt");
	fin[1].open("SS.csv", ios::in);
	fin[2].open("SS-part.csv", ios::in);
	fin[3].open("LC.csv", ios::in);
	fin[4].open("LC-part.csv", ios::in);
	fin[5].open("CMS.csv", ios::in);
	fin[6].open("CMS-part.csv", ios::in);
	fin[7].open("HK.csv", ios::in);
	fin[8].open("HK-part.csv", ios::in);
	string lineStr;
	string c[9][datanum];

	//top100����
	unsigned int a;
	int count = 0;
	while (!fin[0].eof())
	{
		fin[0] >> a;
		stringstream ss;
		if (count >= 0 && count < datanum)
		{
			ss << a;
			ss >> c[0][count];
		}
		count++;
	}

	//�㷨�������
	for (int i = 1; i < 9; i++)
	{
		int count = -1;
		while (getline(fin[i], lineStr)) //getline����sstream
		{
			stringstream ss(lineStr);
			string str;
			//���ն��ŷָ�
			getline(ss, str, ',');
			if (count >= 0 && count < datanum)
			{
				c[i][count] = str;
				//cout << c1[count] << endl;
			}
			count++;
		}
	}

	//������ǳ����ıȽ�

	int num1 = 0;
	for (int m = 0; m < datanum; m++)
	{
		for (int k = 0; k < datanum; k++)
		{
			if (c[1][m] == c[2][k])
			{
				num1++;
				break;
			}
		}
	}

	int num2 = 0;
	for (int m = 0; m < datanum; m++)
	{
		for (int k = 0; k < datanum; k++)
		{
			if (c[3][m] == c[4][k])
			{
				num2++;
				break;
			}
		}
	}

	int num3 = 0;
	for (int m = 0; m < datanum; m++)
	{
		for (int k = 0; k < datanum; k++)
		{
			if (c[5][m] == c[6][k])
			{
				num3++;
				break;
			}
		}
	}

	int num4 = 0;
	for (int m = 0; m < datanum; m++)
	{
		for (int k = 0; k < datanum; k++)
		{
			if (c[7][m] == c[8][k])
			{
				num4++;
				break;
			}
		}
	}

	cout << "SS������ǳ����㷨��ͬ������" << num1 << endl;
	cout << "LC������ǳ����㷨��ͬ������" << num2 << endl;
	cout << "CMS������ǳ����㷨��ͬ������" << num3 << endl;
	cout << "HK������ǳ����㷨��ͬ������" << num4 << endl << endl << endl;


	//�������ʵ���ݱȽ�
	int num[8];
	for (int i = 0; i < 8; i++)
	{
		num[i] = 0;
	}

	for (int i = 1; i < 8; i++)
	{
		for (int m = 0; m < datanum; m++)
		{
			for (int k = 0; k < datanum; k++)
			{
				if (c[0][m] == c[i][k])
				{
					num[i - 1]++;
					break;
				}
			}
		}
	}

	cout << "SS�㷨��ͬ������" << num[0] << endl;
	cout << "SS-part�㷨��ͬ������" << num[1] << endl;
	cout << "LC�㷨��ͬ������" << num[2] << endl;
	cout << "LC-part�㷨��ͬ������" << num[3] << endl;
	cout << "CMS�㷨��ͬ������" << num[4] << endl;
	cout << "CMS-part�㷨��ͬ������" << num[5] << endl;
	cout << "HK�㷨��ͬ������" << num[6] << endl;
	cout << "HK-part�㷨��ͬ������" << num[7] << endl;


	for (int i = 0; i < 9; i++)
	{
		fin[i].close();
	}

	cin.get();
}


void main()
{
	
	unsigned int a;
	
	
	ifstream fin("dataresult.txt");
	ifstream fin_part("dataresult-part1.txt");

	
	SS sstest, sstest_part;
	LC lctest, lctest_part;
	CMS cmstest, cmstest_part;
	HK hktest, hktest_part;

	//ȫ�����ݲ���
	int count = 0;
	while (!fin.eof())
	{
		fin >> a;
        //ss����
		sstest.insertflow(a);
		//LC����
		lctest.windowsize(a);
		//CMS����
		cmstest.storeIn(a);
		//HK����
		hktest.storeIn(a);

		count++;
		if (count %10000 == 0)
			cout << "������" << count << endl;
	}
	
	sstest.outmhtopk("SS");
	lctest.outfiletopk("LC");
	cmstest.outfiletopk("CMS");
	hktest.outfiletopk("HK");

	//�������ݲ���
	count = 0;
	while (!fin_part.eof())
	{
		fin_part >> a;
		//ss����
		sstest_part.insertflow(a);
		//LC����
		lctest_part.windowsize(a);
		//CMS����
		cmstest_part.storeIn(a);
		//HK����
		hktest_part.storeIn(a);

		count++;
		if (count % 10000 == 0)
			cout << "������" << count << endl;
	}

	sstest_part.outmhtopk("SS-part");
	lctest_part.outfiletopk("LC-part");
	cmstest_part.outfiletopk("CMS-part");
	hktest_part.outfiletopk("HK-part");

	fin.close();
	fin_part.close();
	cout << endl << endl;


	//check
	check();
	cin.get();
}

