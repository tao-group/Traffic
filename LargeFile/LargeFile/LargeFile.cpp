// LargeFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>        //读取文件数据的函数fin的头文件
#include <sstream>        //istringstream 必须包含这个头文件
#include <string>
#define IP_MARK  "."
using namespace std;
unsigned int IPtoINT(const string & strIP)
{
	unsigned int nRet = 0;

	char chBuf[16] = "";
	memcpy_s(chBuf, 15, strIP.c_str(), 15);

	char* szBufTemp = NULL;
	char* szBuf = strtok_s(chBuf, IP_MARK, &szBufTemp);

	int i = 0;//计数
	while (NULL != szBuf)//取一个
	{
		nRet += atoi(szBuf) << ((3 - i) * 8);
		szBuf = strtok_s(NULL, IP_MARK, &szBufTemp);
		i++;
	}
	return nRet;
}

unsigned int PORTtoINT(const string & strPORT)
{
	unsigned int port = 0;

	char chBuf[5] = "";
	memcpy_s(chBuf, 5, strPORT.c_str(), 5);

	port=strtoul(chBuf, NULL, 10);
	return port;
}


unsigned int dealstring(string input[4]) {
	unsigned int  sourceip, desip, sourceport, desport,conport,xorresult;

	//cout << input[0] << endl;
	//cout << input[1] << endl;
	sourceip = IPtoINT(input[0]);
	desip = IPtoINT(input[1]);
	//cout << sourceip << endl;
	//cout << desip << endl;

	conport = PORTtoINT(input[2])*256+PORTtoINT(input[3]);

	//cout << conport << endl;

	xorresult = (sourceip^desip)^conport;
	//cout << xorresult;

	return xorresult;
}
int readTCPflow(const string siteFile) {
	string value[4];
	ifstream fin;
	ofstream fout;
	fout.open("D:\\10FoldResult.txt");
	fin.open(siteFile, ios::in);



	if (!fin.is_open())
	{
		cout << "read file error: " << siteFile << endl;
		return 0;
	}

	while(1){
		if (rand() <= 3276) {
			getline(fin, value[0], ',');
			getline(fin, value[1], ',');
			getline(fin, value[2], ',');
			getline(fin, value[3]);
			fout << dealstring(value) << endl;
		}
		else {
			getline(fin, value[0]);
		}
		if (fin.eof())break;
	}
	fin.close();
	fin.clear();
	fout.close();
	fout.clear();
	cout << "success";
	return 0;
}

int main()
{
	readTCPflow("D:\\results\\data.csv");
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
