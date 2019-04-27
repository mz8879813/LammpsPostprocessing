// DiffusionCoefficientCalculator.cpp : 定义控制台应用程序的入口点。
//

#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<cassert>
#include<string>
#include<sstream>
#include<cstdlib>
#include<iomanip>
#include<math.h>
#include <stdlib.h>
#include<conio.h>
using namespace std;

double StringToFloat(string num) //函数将字符串转化为double
{
	long double result = 0.000000;
	istringstream is(num);
	is >> result;
	return result;
}
int StringToInt(string num) //函数将字符串转化为int
{
	int result = 0;
	istringstream is(num);
	is >> result;
	return result;
}



int main()
{
	string inFile;//输入文件的文件名
	cout << "Import MDS file:";
	cin >> inFile;
	double timeStep = 1;
	cout << "Timestep (ps) = ";
	cin >> timeStep;
	int demension = 3;
	cout << "Diffusion demension = ";
	cin >> demension;

	{
		if (inFile[0] == '\"')
		{
			inFile = inFile.substr(1, inFile.length() - 1);
			inFile = inFile.substr(0, inFile.length() - 1);
		}
		else
			inFile = inFile;
	}

	ifstream read(inFile);//输入流
	int lineLocation = 0;
	double MSD[1000];
	string lines;
	while ((getline(read, lines)))
	{
		if (lineLocation > 0)
		{
			MSD[lineLocation - 1] = StringToFloat(lines);
			lineLocation++;
		}
		else
			lineLocation++;
	}
	read.close();
	int numOfFrame = lineLocation;
	double var;
	int i = 0, j = 0, k = 0;
	int bestJ[1000];	
	while (i < numOfFrame)
	{
		if (i == 0)
		{
			bestJ[i] = 0;
			i++;
		}			
		else
		{
			j = 0;
			bestJ[i] = 0;
			double minVar = 1000000.0;
			while (j < 1000)
			{
				k = 1;
				var = 0;
				while (k <= i)
				{
					var = var + abs(MSD[k] - k*(0.1 + 0.1*j));
					k++;
				}
				{
					if (var < minVar)
					{
						minVar = var;
						bestJ[i] = j;
						j++;
					}
					else
						j++;						
				}
			}
			i++;
			{
				if (i % (numOfFrame / 5) == 0)
				{
					cout << endl << i * 10 / (numOfFrame / 5) << "% complete...";
				}
				else
					i = i;
			}
		}
		
	}
	int bestJ2[1000];
	int j2;
	i = 0;
	while (i < numOfFrame)
	{
		if (i == 0)
		{
			bestJ[i] = 0;
			i++;
		}
		else
		{
			j2 = -1000;
			bestJ2[i] = 0;
			double minVar = 1000000.0;
			while (j2 < 1000)
			{
				k = 1;
				var = 0;
				while (k <= i)
				{
					var = var + abs(MSD[k] - k*(0.1 + 0.1*bestJ[i]+0.0001*j2));
					k++;
				}
				{
					if (var < minVar)
					{
						minVar = var;
						bestJ2[i] = j2;
						j2++;
					}
					else
						j2++;
				}
			}
			i++;
			{
				if (i % (numOfFrame / 5) == 0)
				{
					cout << endl << i * 10 / (numOfFrame / 5) + 50 << "% complete...";
				}
				else
					i = i;
			}
		}
	}
	string outFile("Diffusion Coefficient.txt");
	ofstream out(outFile);
	out << "Diffusion Coefficient (Angstrom^2/ps):\n0\n";
	i = 1;
	while (i < numOfFrame-1)
	{
		out << (0.1 + 0.1*bestJ[i] + 0.0001*bestJ2[i])/2/demension/timeStep << endl;
		i++;
	}
	out.close();
	cout << "\n\nDiffusion Data:\n====================\nDiffusion Coefficient.txt\n====================\nis exported in the same folder\n";
	cout << "Press any key to exit.";
	_getch();
    return 0;
}

