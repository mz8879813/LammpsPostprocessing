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
#include <time.h>
using namespace std;

float StringToFloat(string num) //函数将字符串转化为double
{
	float result = 0.000000;
	istringstream is(num);
	is >> result;
	return result;
}

float Min(float x1, float x2, float x3, float x4)
{
	float min;
	min = x1;
	{
		if (min < x2)
			min = min;
		else
			min = x2;
	}
	{
		if (min < x3)
			min = min;
		else
			min = x3;
	}
	{
		if (min < x4)
			min = min;
		else
			min = x4;
	}
	return min;
}

int intMax(int x1, int x2)
{
	int max;
	if (x1 < x2)
	{
		max = x2;
	}
	else
		max = x1;
	return max;
}




float Max(float x1, float x2, float x3, float x4)
{
	float max;
	max = x1;
	{
		if (max > x2)
			max = max;
		else
			max = x2;
	}
	{
		if (max > x3)
			max = max;
		else
			max = x3;
	}
	{
		if (max > x4)
			max = max;
		else
			max = x4;
	}
	return max;
}





int StringToInt(string num) //函数将字符串转化为int
{
	int result = 0;
	istringstream is(num);
	is >> result;
	return result;
}

string intToString(long num, int length)
{
	char empty[100];
	int i = 0;
	while (i < 100)
	{
		empty[i] = ' ';
		i++;
	}
	string result(empty + 0, empty + length);
	ostringstream nums;
	nums << num;
	string numString(nums.str());
	nums.clear();
	nums.str("");
	i = numString.size();
	while (i >= 0)
	{
		result[i + result.size() - numString.size()] = numString[i];
		i--;
	}
	return result;
}

string shortIntToString(short int num, int length)
{
	char empty[100];
	int i = 0;
	while (i < 100)
	{
		empty[i] = ' ';
		i++;
	}
	string result(empty + 0, empty + length);
	ostringstream nums;
	nums << num;
	string numString(nums.str());
	nums.clear();
	nums.str("");
	i = numString.size();
	while (i >= 0)
	{
		result[i + result.size() - numString.size()] = numString[i];
		i--;
	}
	return result;
}

string doubleToString(double num, int length)
{
	char empty[100];
	int i = 0;
	while (i < 100)
	{
		empty[i] = ' ';
		i++;
	}
	string result(empty + 0, empty + length);
	ostringstream nums;
	nums << setiosflags(ios::fixed) << setprecision(9) << num;
	string numString(nums.str());
	nums.clear();
	nums.str("");
	i = numString.size();
	while (i >= 0)
	{
		result[i + result.size() - numString.size()] = numString[i];
		i--;
	}
	return result;
}



float bonding(float x1, float y1, float z1, float x2, float y2, float z2, float lx, float ly, float lz)
{
	float c1[3], c2[3], l[3], d[3];
	c1[0] = x1; c1[1] = y1; c1[2] = z1; c2[0] = x2; c2[1] = y2; c2[2] = z2; l[0] = lx; l[1] = ly; l[2] = lz;
	int i = 0;
	while (i < 3)
	{
		{
			if ((c2[i] - l[i] - c1[i])*(c2[i] - l[i] - c1[i]) < (c2[i] - c1[i])*(c2[i] - c1[i]))
				d[i] = (c2[i] - l[i] - c1[i])*(c2[i] - l[i] - c1[i]);
			else
				d[i] = (c2[i] - c1[i])*(c2[i] - c1[i]);
		}
		{
			if (d[i] < (c2[i] + l[i] - c1[i])*(c2[i] + l[i] - c1[i]))
				d[i] = d[i];
			else
				d[i] = (c2[i] + l[i] - c1[i])*(c2[i] + l[i] - c1[i]);
		}
		i++;
	}

	float dmin = d[0] + d[1] + d[2];
	return dmin;
}

float newCoor(float c1, float c2, float l)
{
	float newCoord = c2;
	int i = -3;
	while (i < 4)
	{
		{
			if ((c2 - l*i - c1)*(c2 - l*i - c1) < (newCoord - c1)*(newCoord - c1))
				newCoord = c2 - l*i;
			else
				newCoord = newCoord;
		}
		i++;
	}
	return newCoord;
}

void main()
{
	string inFile;//输入文件的文件名
	std::cout << "Welcome using Fragment Analyzer 1.00!" << endl << "Developed by Zheng Mei\nDepartment of chemical engineering\n";
	cout << "Nanjing university of science and technology.\nAny problem please contact E-mail: mz8879813@163.com" << endl;
	cout << "\n====================NOTICE====================\nOnly provide for systems containing C/H/O/N/Al.\nDealing with AT MOST 180,000 atoms and 300 frames.\n";
	cout << "Lammps trajectory format:\nid   element   X   Y   Z\n";
	cout << "For example:\n1 N -1.51098 3.73659 4.86118\n2 C -0.1648 4.19407 4.54932\n3 H 0.506599 3.71699 5.00494\n4 O -0.727043 2.44422 6.50853";
	cout << "\nCorresponding dump command in Lammps script:\ndump 1 all custom xxx dump.txt id element x y z vx vy vz";
	cout << "\n==============================================\n";
	std::cout << endl << "Import the Lammps dump file: ";
	std::cin >> inFile;

	ifstream read;//输入流
	string lines;//每行字符串内容
	short int wordsInLine[300];
	float coordinate[180000][3];//坐标矩阵
	short int type[180000];//type
	int spaceLocation[6];//坐标行前四个空格所在位置
	int lineLocation = 0;//第N行
	int NumOfLines = 0;//总行数
	int numOfAtoms = 0;//总原子个数
	short int NumOfFrames = 0;//总帧数
	short int CurrentFrame = 0;//当前帧数
	int timeLocation = 0;//TIMESTEP所在行
	int timeNum = 0;//第N个TMIESTEP
	int group[180000][300];//碎片编号
	int boxMark = 0;
	float box_cross[3];
	float boxmin[3];
	float boxmax[3];
	bool ElementMark = 0;
	long TimeEnd;
	long TimeStart;
	long TotalTimeLeft = 0;

	string elements[5];
	{
		elements[0] = "C";		elements[1] = "H";		elements[2] = "O";		elements[3] = "N";		elements[4] = "Al";
	}

	float crit[6][6];//原子成键截断距离
	{
		crit[0][0] = 1.4827; crit[0][1] = 1.1017; crit[0][2] = 1.4989; crit[0][3] = 1.4417; crit[0][4] = 2.0368;
		crit[1][0] = 1.1017; crit[1][1] = 0.7905; crit[1][2] = 1.0090; crit[1][3] = 1.0858; crit[1][4] = 1.8544;
		crit[2][0] = 1.4989; crit[2][1] = 1.0090; crit[2][2] = 1.2500; crit[2][3] = 1.3130; crit[2][4] = 1.9158;
		crit[3][0] = 1.4417; crit[3][1] = 1.0858; crit[3][2] = 1.3130; crit[3][3] = 1.3818; crit[3][4] = 2.1219;
		crit[4][0] = 2.0368; crit[4][1] = 1.8544; crit[4][2] = 1.9158; crit[4][3] = 2.1219; crit[4][4] = 2.9240;
	}

	string bond_cutoff = "bond_cutoff.txt";
	read.open(bond_cutoff);
	int useless;
	lineLocation = 0;
	while (getline(read, lines))
	{
		if (lineLocation < 6)
		{
			read >> useless >> crit[lineLocation][0] >> useless >> crit[lineLocation][1] >> useless >> crit[lineLocation][2] >> useless >>
				crit[lineLocation][3] >> useless >> crit[lineLocation][4] >> useless >> crit[lineLocation][5];
			lineLocation++;
		}
		else
			lineLocation++;
	}
	read.close();

	float critScale = 1.0;
	cout << "\nScale Factor of cut-off radius of bonding(recommended value: 1.2)=";
	cin >> critScale;
	{
		int m = 0, n = 0;
		while (m < 6)
		{
			n = 0;
			while (n < 6)
			{
				crit[m][n] = crit[m][n] * critScale;
				n++;
			}
			m++;
		}
	}
	short int minNumOfFrag;
	cout << "\nAt least n fragments will be exported, n(recommended value: 5)=";
	cin >> minNumOfFrag;

	read.open(inFile);
	lineLocation = 0;
	while (getline(read, lines) && lineLocation <= 4)
	{
		if (lineLocation == 3)
		{
			numOfAtoms = StringToInt(lines);
			lineLocation++;
		}
		else if (lineLocation == 4)
		{
			{
				if (lines.size() > 28)
				{
					boxMark = 1;
					cout << "\n>>>>>>>>>>Triclinic box detected.<<<<<<<<<<\n";
				}
				else
				{
					boxMark = 0;
					cout << "\n>>>>>>>>>>Orthorhombic box detected<<<<<<<<<<\n";
				}
			}
			lineLocation++;
		}
		else
			lineLocation++;
	}
	read.close();



	read.open(inFile);
	cout << "Analyzing trajectory file...\n";
	lineLocation = 0;
	while ((getline(read, lines)))
	{
		CurrentFrame = lineLocation / (numOfAtoms + 9);
		{
			if (CurrentFrame % 10 == 0 && lineLocation % (numOfAtoms + 9) == 0)
			{
				cout << intToString(intMax(CurrentFrame, 1), 5) << " frames complete... " << endl;
			}
			else
				CurrentFrame = CurrentFrame;
		}
		lineLocation++;
	}
	NumOfLines = lineLocation;
	read.close();
	
	NumOfFrames = NumOfLines / (numOfAtoms + 9);

	std::cout << "\n\nNumber of Atoms = " << numOfAtoms << " \nNumber of frames = " << NumOfFrames << " " << endl 
		<< "\n\nAssigning fragments into groups...\n################################################################\n    Frames complete                Total time left\n################################################################";

	{
		short int i = 0;
		while (i < 3)
		{
			box_cross[i] = 0.0;
			i++;
		}
	}
	float a; float b; float c;//box size
	read.open(inFile);
	lineLocation = 0;
	TimeStart = clock();
	while (getline(read, lines))
	{
		if ((lineLocation % (numOfAtoms + 9)) >= 4 && (lineLocation % (numOfAtoms + 9)) <= 6) //读取盒子大小
		{
			if (boxMark == 1)
			{
				read >> boxmin[(lineLocation % (numOfAtoms + 9)) - 4]
					>> boxmax[(lineLocation % (numOfAtoms + 9)) - 4]
					>> box_cross[(lineLocation % (numOfAtoms + 9)) - 4];
				if ((lineLocation % (numOfAtoms + 9)) == 6)
				{
					{
						boxmin[0] = boxmin[0] - Min(0.0, box_cross[0], box_cross[1], (box_cross[0] + box_cross[1]));
						boxmax[0] = boxmax[0] - Max(0.0, box_cross[0], box_cross[1], (box_cross[0] + box_cross[1]));
						boxmin[1] = boxmin[1] - Min(0.0, box_cross[2], 100000.0, 100000.0);
						boxmax[1] = boxmax[1] - Max(0.0, box_cross[2], -100000.0, -100000.0);
					}
					{
						a = boxmax[0] - boxmin[0];
						b = pow(((boxmax[1] - boxmin[1])*(boxmax[1] - boxmin[1]) + box_cross[0] * box_cross[0]), 0.5);
						c = pow(((boxmax[2] - boxmin[2])*(boxmax[2] - boxmin[2]) + box_cross[1] * box_cross[1] + box_cross[2] * box_cross[2]), 0.5);
					}
					lineLocation++;
				}
				else
					lineLocation++;
			}
			else
			{
				read >> boxmin[(lineLocation % (numOfAtoms + 9)) - 4]
					>> boxmax[(lineLocation % (numOfAtoms + 9)) - 4];
				if ((lineLocation % (numOfAtoms + 9)) == 6)
				{
					{
						boxmin[0] = boxmin[0] - Min(0.0, box_cross[0], box_cross[1], (box_cross[0] + box_cross[1]));
						boxmax[0] = boxmax[0] - Max(0.0, box_cross[0], box_cross[1], (box_cross[0] + box_cross[1]));
						boxmin[1] = boxmin[1] - Min(0.0, box_cross[2], 100000.0, 100000.0);
						boxmax[1] = boxmax[1] - Max(0.0, box_cross[2], -100000.0, -100000.0);
					}
					{
						a = boxmax[0] - boxmin[0];
						b = pow(((boxmax[1] - boxmin[1])*(boxmax[1] - boxmin[1]) + box_cross[0] * box_cross[0]), 0.5);
						c = pow(((boxmax[2] - boxmin[2])*(boxmax[2] - boxmin[2]) + box_cross[1] * box_cross[1] + box_cross[2] * box_cross[2]), 0.5);
					}
					lineLocation++;
				}
				else
					lineLocation++;
			}
		}

		else if ((lineLocation % (numOfAtoms + 9)) >= 8 && (lineLocation % (numOfAtoms + 9)) < numOfAtoms + 8)
		{
			int atomNum = 0;
			float x, y, z;
			string element;
			read >> atomNum >> element >> x >> y >> z;
			coordinate[atomNum - 1][0] = x;
			coordinate[atomNum - 1][1] = y;
			coordinate[atomNum - 1][2] = z;
			{//注入type CHONAl==>01234
				if (ElementMark == 0)
				{
					if (element == "C")
						type[atomNum - 1] = 0;
					else if (element == "H")
						type[atomNum - 1] = 1;
					else if (element == "O")
						type[atomNum - 1] = 2;
					else if (element == "N")
						type[atomNum - 1] = 3;
					else if (element == "Al")
						type[atomNum - 1] = 4;
					else
						type[atomNum - 1] = 5;
				}
				else
					ElementMark = ElementMark;
			}

			if ((lineLocation % (numOfAtoms + 9)) == numOfAtoms + 7)
			{
				CurrentFrame = lineLocation / (numOfAtoms + 9);
				int l, m, n, o;
				l = 0;
				while (l < numOfAtoms)
				{
					group[l][CurrentFrame] = l;
					l++;
				}
				l = 0;
				while (l < numOfAtoms)
				{
					if (group[l][CurrentFrame] == l)
					{
						short int nMark[180000];
						m = 0;
						while (m < numOfAtoms)
						{
							nMark[m] = 0;
							m++;
						}
						m = 0;
						int lastJoin = -1, secondLastJoin = -2;
						while (m < 100 && lastJoin != secondLastJoin)//链接次数
						{
							n = 0;
							secondLastJoin = lastJoin;
							while (n < numOfAtoms)
							{
								if (group[n][CurrentFrame] == l && nMark[n] == 0)
								{
									o = 0;
									while (o < numOfAtoms)
									{
										if (group[o][CurrentFrame] == o &&
											bonding(coordinate[n][0], coordinate[n][1], coordinate[n][2], coordinate[o][0], coordinate[o][1], coordinate[o][2]
												, boxmax[0] - boxmin[0], boxmax[1] - boxmin[1], boxmax[2] - boxmin[2]) < crit[type[n]][type[o]] * crit[type[n]][type[o]])
										{
											group[o][CurrentFrame] = group[n][CurrentFrame];
											lastJoin = o;
											o++;
										}
										else
											o++;
									}
									nMark[n] = 1;
									n++;
								}
								else
									n++;
							}
							m++;
						}
						l++;
					}
					else
						l++;
				}
				{
					if (ElementMark == 0)
					{
						TimeEnd = clock();
					}
				}
				{
					if (CurrentFrame % 10 == 0 || CurrentFrame == NumOfFrames)
					{
						TotalTimeLeft = (TimeEnd - TimeStart)*(NumOfFrames * 2 - CurrentFrame) / 1000;
						cout << endl << "     " << shortIntToString(intMax(CurrentFrame, 1), 5) << "/" << NumOfFrames << "     ";
						short int days = TotalTimeLeft / 86400;
						cout << "     " << shortIntToString(days, 3) << " days ";
						short int hours = (TotalTimeLeft - days * 86400) / 3600;
						cout << shortIntToString(hours, 3) << " hours ";
						short int mins = (TotalTimeLeft - days * 86400 - hours * 3600) / 60;
						cout << shortIntToString(mins, 3) << " mins ";
						short int seconds = (TotalTimeLeft - days * 86400 - hours * 3600 - mins * 60);
						cout << shortIntToString(seconds, 3) << " seconds.";
					}
					else
						CurrentFrame = CurrentFrame;
				}
				ElementMark = 1;
				lineLocation++;
			}
			else
				lineLocation++;
		}
		else
			lineLocation++;
	}
	read.close();
	int groupElement[180000][300][5];//碎片组成，第l个group在第k帧含有Type为n的原子的个数
	int l, m, n, o, k;
	l = 0;
	while (l < numOfAtoms)//初始化碎片组成
	{
		k = 0;
		while (k < NumOfFrames)
		{
			m = 0;
			while (m < 5)
			{
				groupElement[l][k][m] = 0;
				m++;
			}
			k++;
		}
		l++;
	}

	k = 0;
	while (k < NumOfFrames)//注入碎片组成
	{
		l = 0;
		while (l < numOfAtoms)
		{
			m = 0;
			int numOfType[5] = { 0,0,0,0,0 };//每种元素的个数
			while (m < numOfAtoms)
			{
				if (group[m][k] == l)
				{
					numOfType[type[m]]++;
					m++;
				}
				else
					m++;
			}
			n = 0;
			while (n < 5)
			{
				groupElement[l][k][n] = numOfType[n];
				n++;
			}
			l++;
		}
		k++;
	}

	string outFile("Fragment data.txt");
	string outFile1 = "Fragment structure.txt";
	ofstream out1;
	ofstream out;
	out.open(outFile);
	

	int numOfFrag[180000][300];
	bool markFrag[180000][300];
	l = 0;
	while (l < numOfAtoms)
	{
		k = 0;
		while (k < NumOfFrames)
		{
			numOfFrag[l][k] = 0;
			markFrag[l][k] = 0;
			k++;
		}
		l++;
	}

	k = 0;
	cout << "\n\n\nCalculating numbers of fragments...\n################################################################\n  Frames calculated                Total time left\n################################################################";
	while (k < NumOfFrames)//注入碎片数量
	{
		l = 0;
		while (l < numOfAtoms)
		{
			if (group[l][k] == l&&markFrag[l][k] == 0)
			{
				m = 0;
				while (m < numOfAtoms)
				{
					if (groupElement[m][k][0] == groupElement[l][k][0]
						&& groupElement[m][k][1] == groupElement[l][k][1]
						&& groupElement[m][k][2] == groupElement[l][k][2]
						&& groupElement[m][k][3] == groupElement[l][k][3]
						&& groupElement[m][k][4] == groupElement[l][k][4])
					{
						numOfFrag[l][k]++;
						{
							if (m == l)
							{
								m = m;
							}
							else
								markFrag[m][k] = 1;
						}
						m++;
					}
					else
						m++;
				}
				l++;
			}
			else
				l++;
		}
		{
			if (k % intMax((NumOfFrames / 2), 1) == 0)
			{
				TotalTimeLeft = (TimeEnd - TimeStart)*NumOfFrames*(1 - 0.1*(k / intMax((NumOfFrames / 2), 1))) / 1000;
				cout << endl << "       " << intMax(k, 1) / intMax((NumOfFrames / 2), 1) << "/" << 4 << "     ";
				short int days = TotalTimeLeft / 86400;					
				cout << "     " << shortIntToString(days, 3) << " days ";
				short int hours = (TotalTimeLeft - days * 86400) / 3600;
				cout << shortIntToString(hours, 3) << " hours ";
				short int mins = (TotalTimeLeft - days * 86400 - hours * 3600) / 60;
				cout << shortIntToString(mins, 3) << " mins ";
				short int seconds = (TotalTimeLeft - days * 86400 - hours * 3600 - mins * 60);
				cout << shortIntToString(seconds, 3) << " seconds.";
			}
			else
			{
				CurrentFrame = CurrentFrame;
			}				
		}
		k++;
	}

	bool kMark[180000][300];
	l = 0;
	while (l < numOfAtoms)
	{
		k = 0;
		while (k < NumOfFrames)
		{
			kMark[l][k] = 0;
			k++;
		}
		l++;
	}

	k = 0;
	while (k < NumOfFrames)
	{
		l = 0;
		while (l < numOfAtoms)
		{
			if (groupElement[l][k][0] == 0 &&
				groupElement[l][k][1] == 0 &&
				groupElement[l][k][2] == 0 &&
				groupElement[l][k][3] == 0 &&
				groupElement[l][k][4] == 0)
				l++;
			else
			{
				kMark[l][k] = 1;
				l++;
			}
		}
		k++;
	}

	bool titleMark[180000][300];
	l = 0;
	while (l < numOfAtoms)
	{
		k = 0;
		while (k < NumOfFrames)
		{
			titleMark[l][k] = 0;
			k++;
		}
		l++;
	}



	short int maxNumOfFrag[180000][300];
	l = 0;
	while (l < numOfAtoms)
	{
		k = 0;
		while (k < NumOfFrames)
		{
			maxNumOfFrag[l][k] = numOfFrag[l][k];
			k++;
		}
		l++;
	}

	l = 0;
	while (l < numOfAtoms)
	{
		k = 0;
		while (k < NumOfFrames)
		{
			if (numOfFrag[l][k] == 0)
			{
				k++;
			}
			else
			{
				m = 0;
				while (m < numOfAtoms)
				{
					n = 0;
					while (n < NumOfFrames)
					{
						if (numOfFrag[m][n] != 0 &&
							groupElement[l][k][0] == groupElement[m][n][0] &&
							groupElement[l][k][1] == groupElement[m][n][1] &&
							groupElement[l][k][2] == groupElement[m][n][2] &&
							groupElement[l][k][3] == groupElement[m][n][3] &&
							groupElement[l][k][4] == groupElement[m][n][4] &&
							numOfFrag[m][n] > maxNumOfFrag[l][k])
						{
							maxNumOfFrag[l][k] = numOfFrag[m][n];
							n++;
						}
						else
							n++;
					}
					m++;
				}
				{
					if (maxNumOfFrag[l][k] < minNumOfFrag)
					{
						kMark[l][k] = 0;
					}
					else
						k = k;
				}
				k++;
			}
		}
		l++;
	}

	bool StructOutMark[180000][300];
	l = 0;
	while (l < numOfAtoms)
	{
		m = 0;
		while (m < NumOfFrames)
		{
			StructOutMark[l][m] = 0;
			m++;
		}
		l++;
	}



	l = 0;
	while (l < numOfAtoms)
	{
		k = 0;
		while (k < NumOfFrames)
		{
			if (numOfFrag[l][k] == 0)
				k++;
			else
			{
				m = 0;
				while (m < numOfAtoms)
				{
					n = 0;
					while (n < NumOfFrames)
					{
						if (titleMark[m][n] == 1 &&
							groupElement[l][k][0] == groupElement[m][n][0] &&
							groupElement[l][k][1] == groupElement[m][n][1] &&
							groupElement[l][k][2] == groupElement[m][n][2] &&
							groupElement[l][k][3] == groupElement[m][n][3] &&
							groupElement[l][k][4] == groupElement[m][n][4])
						{
							kMark[l][k] = 0;
							n++;
						}
						else
							n++;
					}
					m++;
				}

				{
					if (kMark[l][k] == 0)
						k++;
					else
					{
						//cout << "\nExporting fragment: ";
						out << "Fragment ";
						{
							if (groupElement[l][k][0] == 0)
								l = l;
							else
							{
								//cout << "C" << groupElement[l][k][0];
								out << "C" << groupElement[l][k][0];
							}
						}
						{
							if (groupElement[l][k][1] == 0)
								l = l;
							else
							{
								//cout << "H" << groupElement[l][k][1];
								out << "H" << groupElement[l][k][1];
							}
						}
						{
							if (groupElement[l][k][2] == 0)
								l = l;
							else
							{
								//cout << "O" << groupElement[l][k][2];
								out << "O" << groupElement[l][k][2];
							}
						}
						{
							if (groupElement[l][k][3] == 0)
								l = l;
							else
							{
								//cout << "N" << groupElement[l][k][3];
								out << "N" << groupElement[l][k][3];
							}
						}
						{
							if (groupElement[l][k][4] == 0)
								l = l;
							else
							{
								//cout << "Al" << groupElement[l][k][4];
								out << "Al" << groupElement[l][k][4];
							}
						}
						out << endl;



						short int k1 = 0;//逐帧输出碎片数量
						while (k1 < NumOfFrames)
						{
							m = 0;
							bool mMark = 0;
							while (m < numOfAtoms)
							{
								if (markFrag[m][k1] == 0 &&
									groupElement[l][k][0] == groupElement[m][k1][0] &&
									groupElement[l][k][1] == groupElement[m][k1][1] &&
									groupElement[l][k][2] == groupElement[m][k1][2] &&
									groupElement[l][k][3] == groupElement[m][k1][3] &&
									groupElement[l][k][4] == groupElement[m][k1][4])
								{
									out << numOfFrag[m][k1] << endl;
									mMark = 1;
									m++;
								}
								else
									m++;
							}
							{
								if (mMark == 1)
									k1 = k1;
								else
									out << "0\n";
							}
							k1++;
						}

						int l1 = 0;
						while (l1 < numOfAtoms)
						{
							if (group[l1][k] == l)
							{
								StructOutMark[l][k] = 1;
								l1++;
							}
							else
								l1++;
						}
						titleMark[l][k] = 1;
						k++;
					}
				}
			}
		}
		{
		if (l % (numOfAtoms / 2) == 0)
		{
			TotalTimeLeft = (TimeEnd - TimeStart)*NumOfFrames*(0.8 - 0.1*(l / (numOfAtoms / 2))) / 1000;
			cout << endl << "       " << l / (numOfAtoms / 2) + 2 << "/" << 4 << "     ";
			short int days = TotalTimeLeft / 86400;
			cout << "     " << shortIntToString(days, 3) << " days ";
			short int hours = (TotalTimeLeft - days * 86400) / 3600;
			cout << shortIntToString(hours, 3) << " hours ";
			short int mins = (TotalTimeLeft - days * 86400 - hours * 3600) / 60;
			cout << shortIntToString(mins, 3) << " mins ";
			short int seconds = (TotalTimeLeft - days * 86400 - hours * 3600 - mins * 60);
			cout << shortIntToString(seconds, 3) << " seconds.";
		}
		else
			CurrentFrame = CurrentFrame;
		}
		l++;
	}
	out.close();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	read.open(inFile);
	out1.open(outFile1);
	lineLocation = 0;
	{
		short int i = 0;
		while (i < 3)
		{
			box_cross[i] = 0.0;
			i++;
		}
	}

	cout << "\n\n\nCalculating structures of fragments...\n################################################################\n    Frames complete                Total time left\n################################################################";
	while (getline(read, lines))
	{
		if ((lineLocation % (numOfAtoms + 9)) >= 4 && (lineLocation % (numOfAtoms + 9)) <= 6) //读取盒子大小
		{
			if (boxMark == 1)
			{
				read >> boxmin[(lineLocation % (numOfAtoms + 9)) - 4]
					>> boxmax[(lineLocation % (numOfAtoms + 9)) - 4]
					>> box_cross[(lineLocation % (numOfAtoms + 9)) - 4];
				if ((lineLocation % (numOfAtoms + 9)) == 6)
				{
					{
						boxmin[0] = boxmin[0] - Min(0.0, box_cross[0], box_cross[1], (box_cross[0] + box_cross[1]));
						boxmax[0] = boxmax[0] - Max(0.0, box_cross[0], box_cross[1], (box_cross[0] + box_cross[1]));
						boxmin[1] = boxmin[1] - Min(0.0, box_cross[2], 100000.0, 100000.0);
						boxmax[1] = boxmax[1] - Max(0.0, box_cross[2], -100000.0, -100000.0);
					}
					{
						a = boxmax[0] - boxmin[0];
						b = pow(((boxmax[1] - boxmin[1])*(boxmax[1] - boxmin[1]) + box_cross[0] * box_cross[0]), 0.5);
						c = pow(((boxmax[2] - boxmin[2])*(boxmax[2] - boxmin[2]) + box_cross[1] * box_cross[1] + box_cross[2] * box_cross[2]), 0.5);
					}
					lineLocation++;
				}
				else
					lineLocation++;
			}
			else
			{
				read >> boxmin[(lineLocation % (numOfAtoms + 9)) - 4]
					>> boxmax[(lineLocation % (numOfAtoms + 9)) - 4];
				if ((lineLocation % (numOfAtoms + 9)) == 6)
				{
					{
						boxmin[0] = boxmin[0] - Min(0.0, box_cross[0], box_cross[1], (box_cross[0] + box_cross[1]));
						boxmax[0] = boxmax[0] - Max(0.0, box_cross[0], box_cross[1], (box_cross[0] + box_cross[1]));
						boxmin[1] = boxmin[1] - Min(0.0, box_cross[2], 100000.0, 100000.0);
						boxmax[1] = boxmax[1] - Max(0.0, box_cross[2], -100000.0, -100000.0);
					}
					{
						a = boxmax[0] - boxmin[0];
						b = pow(((boxmax[1] - boxmin[1])*(boxmax[1] - boxmin[1]) + box_cross[0] * box_cross[0]), 0.5);
						c = pow(((boxmax[2] - boxmin[2])*(boxmax[2] - boxmin[2]) + box_cross[1] * box_cross[1] + box_cross[2] * box_cross[2]), 0.5);
					}
					lineLocation++;
				}
				else
					lineLocation++;
			}
		}

		else if ((lineLocation % (numOfAtoms + 9)) >= 8 && (lineLocation % (numOfAtoms + 9)) < numOfAtoms + 8)
		{
			int atomNum = 0;
			float x, y, z;
			string element;
			read >> atomNum >> element >> x >> y >> z;
			coordinate[atomNum - 1][0] = x;
			coordinate[atomNum - 1][1] = y;
			coordinate[atomNum - 1][2] = z;
			//cout << "coordcoordcoordcoordcoordcoordcoordcoordcoordcoordcoord\n";
			if ((lineLocation % (numOfAtoms + 9)) == numOfAtoms + 7)
			{
				CurrentFrame = lineLocation / (numOfAtoms + 9);
				int l, m, n, o;
				m = 0; l = 0;
				while (m < numOfAtoms)
				{
					if (StructOutMark[m][CurrentFrame] == 1)
					{
						out1 << "Fragment ";
						{
							if (groupElement[m][CurrentFrame][0] == 0)
								l = l;
							else
							{
								out1 << "C" << groupElement[m][CurrentFrame][0];
							}
						}
						{
							if (groupElement[m][CurrentFrame][1] == 0)
								l = l;
							else
							{
								out1 << "H" << groupElement[m][CurrentFrame][1];
							}
						}
						{
							if (groupElement[m][CurrentFrame][2] == 0)
								l = l;
							else
							{
								out1 << "O" << groupElement[m][CurrentFrame][2];
							}
						}
						{
							if (groupElement[m][CurrentFrame][3] == 0)
								l = l;
							else
							{
								out1 << "N" << groupElement[m][CurrentFrame][3];
							}
						}
						{
							if (groupElement[m][CurrentFrame][4] == 0)
								l = l;
							else
							{
								out1 << "Al" << groupElement[m][CurrentFrame][4];
							}
						}
						out1 << "\nCopy out the data between two '##################################################' lines and save as xxx.mol2 file,\nso it can be opened with Materials Studio 7.0\n\n\n##################################################\n";
						out1 << "@<TRIPOS>MOLECULE\nstructure\n500000 0 0 0 0 \nSMALL\nUSER_CHARGES\n\n\n@<TRIPOS>ATOM\n";
						l = 0; int l2 = 1;
						while (l < numOfAtoms)
						{
							if (group[l][CurrentFrame] == m)
							{
								out1 << l2 << " " << elements[type[l]] << "   " << coordinate[l][0]
									<< "   " << coordinate[l][1]
									<< "   " << coordinate[l][2] << " " << elements[type[l]] << " 0 **** 0" << endl;
								l2++;
								l++;
							}
							else
								l++;
						}
						out1 << "@<TRIPOS>BOND\n@<TRIPOS>CRYSIN\n" << a << " " << b << " " << c << "  "
							<< acos((box_cross[0] * box_cross[1] + (boxmax[1] - boxmin[1])*box_cross[2]) / (b * c)) / 3.141592653 * 180 << " "
							<< acos(box_cross[1] / c) / 3.141592653 * 180 << " " << acos(box_cross[0] / b) / 3.141592653 * 180 << " 1 1\n##################################################\n\n\n\n\n";
						m++;
					}
					else
						m++;
				}
				{
					if (CurrentFrame % 20 == 0 || CurrentFrame == NumOfFrames)
					{
						TotalTimeLeft = (TimeEnd - TimeStart) * 3 / 5 * (NumOfFrames - CurrentFrame) / 1000;
						cout << endl << intToString(intMax(CurrentFrame, 1), 10) << "/" << NumOfFrames << "     ";
						short int days = TotalTimeLeft / 86400;
						cout << "     " << shortIntToString(days, 3) << " days ";
						short int hours = (TotalTimeLeft - days * 86400) / 3600;
						cout << shortIntToString(hours, 3) << " hours ";
						short int mins = (TotalTimeLeft - days * 86400 - hours * 3600) / 60;
						cout << shortIntToString(mins, 3) << " mins ";
						short int seconds = (TotalTimeLeft - days * 86400 - hours * 3600 - mins * 60);
						cout << shortIntToString(seconds, 3) << " seconds.";
					}
					else
						CurrentFrame = CurrentFrame;
				}
				lineLocation++;
			}
			else
				lineLocation++;
		}
		else
			lineLocation++;
	}
	read.close();
	out1.close();
	cout << "\n\nFragment data:\n====================\nFragment data.txt\n"
		<< "Fragment structure.txt\n====================\nare exported in the same folder.\n"
		<< "Press any key to EXIT...";
	_getch();
}
			
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			








	










