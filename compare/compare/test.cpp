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

	//top100读入
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

	//算法结果读入
	for (int i = 1; i < 9; i++)
	{
		int count = -1;
		while (getline(fin[i], lineStr)) //getline来自sstream
		{
			stringstream ss(lineStr);
			string str;
			//按照逗号分隔
			getline(ss, str, ',');
			if (count >= 0 && count < datanum)
			{
				c[i][count] = str;
				//cout << c1[count] << endl;
			}
			count++;
		}
	}

	//抽样与非抽样的比较

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

	cout << "SS抽样与非抽样算法相同个数：" << num1 << endl;
	cout << "LC抽样与非抽样算法相同个数：" << num2 << endl;
	cout << "CMS抽样与非抽样算法相同个数：" << num3 << endl;
	cout << "HK抽样与非抽样算法相同个数：" << num4 << endl << endl << endl;


	//结果与真实数据比较
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

	cout << "SS算法相同个数：" << num[0] << endl;
	cout << "SS-part算法相同个数：" << num[1] << endl;
	cout << "LC算法相同个数：" << num[2] << endl;
	cout << "LC-part算法相同个数：" << num[3] << endl;
	cout << "CMS算法相同个数：" << num[4] << endl;
	cout << "CMS-part算法相同个数：" << num[5] << endl;
	cout << "HK算法相同个数：" << num[6] << endl;
	cout << "HK-part算法相同个数：" << num[7] << endl;


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

	//全部数据测试
	int count = 0;
	while (!fin.eof())
	{
		fin >> a;
        //ss测试
		sstest.insertflow(a);
		//LC测试
		lctest.windowsize(a);
		//CMS测试
		cmstest.storeIn(a);
		//HK测试
		hktest.storeIn(a);

		count++;
		if (count %10000 == 0)
			cout << "已跑完" << count << endl;
	}
	
	sstest.outmhtopk("SS");
	lctest.outfiletopk("LC");
	cmstest.outfiletopk("CMS");
	hktest.outfiletopk("HK");

	//抽样数据测试
	count = 0;
	while (!fin_part.eof())
	{
		fin_part >> a;
		//ss测试
		sstest_part.insertflow(a);
		//LC测试
		lctest_part.windowsize(a);
		//CMS测试
		cmstest_part.storeIn(a);
		//HK测试
		hktest_part.storeIn(a);

		count++;
		if (count % 10000 == 0)
			cout << "已跑完" << count << endl;
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

