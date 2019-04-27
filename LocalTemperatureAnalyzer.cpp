// LocalTemperatureAnalyzer.cpp : 定义控制台应用程序的入口点。
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
#include<stdlib.h>
#include<conio.h>
using namespace std;

double StringToFloat(string num) //函数将字符串转化为double
{
	double result = 0.000000;
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

string intToString(int num, int length)
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
	std::cout << "Welcome using Local Temperature Analyzer(1.50)!" << endl << "Developed by Zheng Mei\nDepartment of chemical engineering\n";
	cout << "Nanjing university of science and technology.\nAny problem please contact E-mail: mz8879813@163.com" << endl;
	cout << "\n====================NOTICE====================\nOnly provide for systems containing C/H/O/N/Al.\n";
	cout << "Lammps trajectory format:\n";
	cout << "dump 1 all custom xxx dump.txt id element x y z vx vy vz";
	cout << "\n==============================================\n";
	std::cout << endl << "Import the Lammps trajectory file: ";
	std::cin >> inFile;
	cout << "Scale factor of distribution = ";
	float scaleFactor;
	cin >> scaleFactor;
	cout << "Analyzing trajectory file...";
	ifstream read(inFile);//输入流
	string lines;//每行字符串内容
	short int wordsInLine[400];
	float coordinate[30000][3][400];//坐标矩阵
	double kineticEnergy[30000][400];//动能
	short int type[30000];//type
	int spaceLocation[6];//坐标行前四个空格所在位置
	int lineLocation = 0;//第N行
	int NumOfLines = 0;//总行数
	int numOfAtoms = 0;//原子个数
	int timeLocation = 0;//TIMESTEP所在行
	int timeNum = 0;//第N个TMIESTEP
	int boxMark = 0;
	double box_cross[3][400];
	double boxmin[3][400];
	double boxmax[3][400];
	while ((getline(read, lines)))
	{
		lineLocation++;
	}
	NumOfLines = lineLocation;
	read.close();
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
					cout << "\nTriclinic box detected.\n";
				}					
				else
				{
					boxMark = 0;
					cout << "\nOrthorhombic box detected\n";
				}					
			}
			lineLocation++;
		}
		else
			lineLocation++;
	}

	std::cout << "\n\nNumber of Atoms = " << numOfAtoms << " (At most 30,000)  \nNumber of frames = " << NumOfLines / (numOfAtoms + 9) << " (At most 400)" << endl << "Importing coordinate matrix...";
	read.close();

	float mass[5];
	{
		mass[0] = 12.011150;
		mass[1] = 1.007970;
		mass[2] = 15.999400;
		mass[3] = 14.006700;
		mass[4] = 26.982000;
	}

	read.open(inFile);
	lineLocation = 0;
	while (getline(read, lines))
	{		
		if ((lineLocation % (numOfAtoms + 9)) >= 4 && (lineLocation % (numOfAtoms + 9)) <= 6) //读取盒子大小
		{
			if (boxMark == 1)
			{
				read >> boxmin[(lineLocation % (numOfAtoms + 9)) - 4][lineLocation / (numOfAtoms + 9)]
					>> boxmax[(lineLocation % (numOfAtoms + 9)) - 4][lineLocation / (numOfAtoms + 9)]
					>> box_cross[(lineLocation % (numOfAtoms + 9)) - 4][lineLocation / (numOfAtoms + 9)];
				lineLocation++;
			}
			else
			{
				read >> boxmin[(lineLocation % (numOfAtoms + 9)) - 4][lineLocation / (numOfAtoms + 9)]
					>> boxmax[(lineLocation % (numOfAtoms + 9)) - 4][lineLocation / (numOfAtoms + 9)];
				lineLocation++;
			}
			
		}

		else if ((lineLocation % (numOfAtoms + 9)) >= 8 && (lineLocation % (numOfAtoms + 9)) < numOfAtoms + 8)
		{
			int atomNum = 0;
			double x, y, z, vx, vy, vz;
			string element;
			read >> atomNum >> element >> x >> y >> z >> vx >> vy >> vz;
			coordinate[atomNum - 1][0][lineLocation / (numOfAtoms + 9)] = x;
			coordinate[atomNum - 1][1][lineLocation / (numOfAtoms + 9)] = y;
			coordinate[atomNum - 1][2][lineLocation / (numOfAtoms + 9)] = z;
			{//注入type CHONAl==>01234
				if (element == "C")
				{
					type[atomNum - 1] = 0;
					kineticEnergy[atomNum - 1][lineLocation / (numOfAtoms + 9)] = 12.011150*(vx*vx + vy*vy + vz*vz);
				}					
				else if (element == "H")
				{
					type[atomNum - 1] = 1;
					kineticEnergy[atomNum - 1][lineLocation / (numOfAtoms + 9)] = 1.007970*(vx*vx + vy*vy + vz*vz);
				}
				else if (element == "O")
				{
					type[atomNum - 1] = 2;
					kineticEnergy[atomNum - 1][lineLocation / (numOfAtoms + 9)] = 15.999400*(vx*vx + vy*vy + vz*vz);
				}
				else if (element == "N")
				{
					type[atomNum - 1] = 3;
					kineticEnergy[atomNum - 1][lineLocation / (numOfAtoms + 9)] = 14.006700*(vx*vx + vy*vy + vz*vz);
				}
				else if (element == "Al")
				{
					type[atomNum - 1] = 4;
					kineticEnergy[atomNum - 1][lineLocation / (numOfAtoms + 9)] = 26.982000*(vx*vx + vy*vy + vz*vz);
				}
				else
				{
					type[atomNum - 1] = 5;
					kineticEnergy[atomNum - 1][lineLocation / (numOfAtoms + 9)] = 12.011150*(vx*vx + vy*vy + vz*vz);
				}
			}
			{
				if (lineLocation % (NumOfLines / 10) == 0)
				{
					cout << endl << lineLocation / (NumOfLines / 10) * 10 << "% complete...";
					lineLocation++;
				}
				else
					lineLocation++;
			}
		}
		else
			lineLocation++;
	}
	read.close();

	string elements[5];
	{
		elements[0] = "C";
		elements[1] = "H";
		elements[2] = "O";
		elements[3] = "N";
		elements[4] = "Al";
	}
	float minBox[3][400];//盒子最小值
	float maxBox[3][400];//盒子最大值
	{//初始化盒子
		int i = 0, j = 0;
		while (j < 3)
		{
			i = 0;
			while (i < NumOfLines / (numOfAtoms + 9))
			{
				minBox[j][i] = boxmin[j][i];
				maxBox[j][i] = boxmax[j][i];
				i++;
			}
			j++;
		}
	}

	
	double totalKE[400];
	{
		int k = 0;
		while (k < NumOfLines / (numOfAtoms + 9))
		{
			totalKE[k] = 0;
			k++;
		}
	}

	{
		int k = 0;
		while (k < NumOfLines / (numOfAtoms + 9))
		{
			int i = 0;
			while (i < numOfAtoms)
			{
				totalKE[k] = totalKE[k] + kineticEnergy[i][k];
				i++;
			}
			k++;
		}		
	}

	{
		int k = 0;
		while (k < NumOfLines / (numOfAtoms + 9))
		{
			int i = 0;
			while (i < numOfAtoms)
			{
				if (totalKE[k] == 0)
				{
					i++;
				}
				else
				{
					kineticEnergy[i][k] = pow(kineticEnergy[i][k] * numOfAtoms / totalKE[k], scaleFactor);
					i++;
				}				
			}
			k++;
		}		
	}
	{
		string outFile("Temperature Distribution.data");
		ofstream out;
		cout << "\nCoordinate imported, exporting data file:";
		out.open(outFile);
		int k = 0;
		while (k < NumOfLines / (numOfAtoms + 9))
		{
			out << "ITEM: TIMESTEP\n" << k << "\nITEM: NUMBER OF ATOMS\n" << numOfAtoms << "\n";
			{
				if (boxMark == 1)
					out << "ITEM: BOX BOUNDS xy xz yz pp pp pp\n";
				else
					out << "ITEM: BOX BOUNDS pp pp pp\n";
			}
			out << doubleToString((minBox[0][k]), 13) << " " << doubleToString((maxBox[0][k]), 13);
			{
				if (boxMark == 1)
					out << " " << doubleToString(box_cross[0][k], 13) << "\n";
				else
					out << "\n";				
			}
			out << doubleToString((minBox[1][k]), 13) << " " << doubleToString((maxBox[1][k]), 13);
			{
				if (boxMark == 1)
					out << " " << doubleToString(box_cross[1][k], 13) << "\n";
				else
					out << "\n";
			}
			out << doubleToString((minBox[2][k]), 13) << " " << doubleToString((maxBox[2][k]), 13);
			{
				if (boxMark == 1)
					out << " " << doubleToString(box_cross[2][k], 13) << "\n";
				else
					out << "\n";
			}
			out << "ITEM: ATOMS id element x y z vx \n";
			
			

			int i = 0;
			while (i < numOfAtoms)
			{
				out << intToString(i + 1, 7) << "  " << elements[type[i]] << doubleToString(coordinate[i][0][k], 16)
					<< doubleToString(coordinate[i][1][k], 16) << doubleToString(coordinate[i][2][k], 16)
					<< doubleToString(kineticEnergy[i][k], 20) << " \n";
				i++;
			}
			{
				if (k % ((NumOfLines / (numOfAtoms + 9) / 10) + 1) == 0)
				{
					cout << endl << k / (NumOfLines / (numOfAtoms + 9) / 10 + 1) * 10 << "% complete...";
					k++;
				}
				else
					k++;
			}
		}		
		out.close();
		cout << "\n\nDump file:\n====================\nTemperature Distribution.data\n"
			<< "====================\nis exported in the same folder.\n"
			<< "Press any key to exit...";
		_getch();
	}
}
