// ConsoleApplication4.cpp : 定义控制台应用程序的入口点。
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
	double result = 0.000000;
	istringstream is(num);
	is >> result;
	return result;
}

double Min(double x1, double x2, double x3, double x4)
{
	double min;
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

double Max(double x1, double x2, double x3, double x4)
{
	double max;
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
	std::cout << "Welcome using Lammps Trajectory Analyzer(LTA_V1.58)!" << endl << "Developed by Zheng Mei\nDepartment of chemical engineering\n";
	cout<<"Nanjing university of science and technology.\nAny problem please contact E-mail: mz8879813@163.com" << endl;
	cout << "\n====================NOTICE====================\nOnly provide for systems containing C/H/O/N/Al.\n";
	cout<<"Lammps trajectory format:\nid   element   X   Y   Z\n";
	cout << "For example:\n1 N -1.51098 3.73659 4.86118\n2 C -0.1648 4.19407 4.54932\n3 H 0.506599 3.71699 5.00494\n4 O -0.727043 2.44422 6.50853";
	cout << "\nCorresponding dump command in Lammps script:\ndump 1 all custom xxx dump.txt id element x y z";
	cout << "\n==============================================\n";
	std::cout << endl << "Import the Lammps trajectory file: ";
	std::cin >> inFile;
	cout << "Analyzing trajectory file...";
	ifstream read(inFile);//输入流
	string lines;//每行字符串内容
	short int wordsInLine[300];
	float coordinate[40000][3][300];//坐标矩阵
	short int type[40000];//type
	int spaceLocation[6];//坐标行前四个空格所在位置
	int lineLocation = 0;//第N行
	int NumOfLines = 0;//总行数
	int numOfAtoms = 0;//原子个数
	int timeLocation = 0;//TIMESTEP所在行
	int timeNum = 0;//第N个TMIESTEP
	int boxMark = 0;
	double box_cross[3][300];
	double boxmin[3][300];
	double boxmax[3][300];
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
	
	std::cout << "\n\nNumber of Atoms = " << numOfAtoms << " (At most 40,000)  \nNumber of frames = " << NumOfLines / (numOfAtoms + 9) << " (At most 300)" << endl << "Importing coordinate matrix...";
	read.close();
	{
		int i = 0;
		while (i < 300)
		{
			int j = 0;
			while (j < 3)
			{
				box_cross[j][i] = 0.0;
				j++;
			}
			i++;
		}
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
			int atomNum=0;
			float x, y, z;
			string element;
			read >> atomNum >> element >> x >> y >> z;
			coordinate[atomNum - 1][0][lineLocation / (numOfAtoms + 9)] = x;
			coordinate[atomNum - 1][1][lineLocation / (numOfAtoms + 9)] = y;
			coordinate[atomNum - 1][2][lineLocation / (numOfAtoms + 9)] = z;
			{//注入type CHONAl==>01234
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

	{
		int k = 0;
		while (k < NumOfLines / (numOfAtoms + 9))
		{
			boxmin[0][k] = boxmin[0][k] - Min(0.0, box_cross[0][k], box_cross[1][k], (box_cross[0][k] + box_cross[1][k]));
			boxmax[0][k] = boxmax[0][k] - Max(0.0, box_cross[0][k], box_cross[1][k], (box_cross[0][k] + box_cross[1][k]));
			boxmin[1][k] = boxmin[1][k] - Min(0.0, box_cross[2][k],100000.0,100000.0);
			boxmax[1][k] = boxmax[1][k] - Max(0.0, box_cross[2][k], -100000.0, -100000.0);
			k++;
		}
	}



	double a[300]; double b[300]; double c[300];
	{
		int k = 0;
		while (k < NumOfLines / (numOfAtoms + 9))
		{
			a[k] = boxmax[0][k] - boxmin[0][k]; 
			b[k] = pow(((boxmax[1][k] - boxmin[1][k])*(boxmax[1][k] - boxmin[1][k]) + box_cross[0][k] * box_cross[0][k]), 0.5);
			c[k] = pow(((boxmax[2][k] - boxmin[2][k])*(boxmax[2][k] - boxmin[2][k]) + box_cross[1][k] * box_cross[1][k] + box_cross[2][k] * box_cross[2][k]), 0.5);
			k++;
		}
	}


	string elements[5];
	{
		elements[0] = "C";
		elements[1] = "H";
		elements[2] = "O";
		elements[3] = "N";
		elements[4] = "Al";
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
	while(getline(read,lines))
	{
		if (lineLocation < 6)
		{
			read >> useless >> crit[lineLocation][0] >> useless >> crit[lineLocation][1] >> useless >> crit[lineLocation][2] >> useless >>
				crit[lineLocation][3] >> useless >> crit[lineLocation][4] >> useless >> crit[lineLocation][5];
			//cout << "crit[" << lineLocation << "][0]=" << crit[lineLocation][0];
			lineLocation++;
		}
		else
			lineLocation++;		
	}
	read.close();

	double critScale = 1.0;
	cout << "\nCoordinates and frames imported successfully.\n\nScale Factor of cut-off radius of bonding(recommended value 1.1-1.3)=";
	cin >> critScale;
	{
		int m = 0, n = 0;
		while (m < 6)
		{
			n = 0;
			while (n < 6)
			{
				crit[m][n] = crit[m][n] * critScale;
				//cout << "crit[" << m << "][" << n << "]=" << crit[m][n] << endl;
				n++;
			}
			m++;
		}
	}

	int choice[3];//输入选项变量
	while (choice[0]==choice[0])
	{
		cout<< "\n\n\nStart to analysis:\n" << "1. Product analysis." << endl << "2. Diffusion analysis.\n3. Export in-file of Material Studio or Gaussian\n=====>";
		cin >> choice[0];
		if (choice[0] == 1)//若选择产物分析
		{
			cout << "\n1. Bonding analysis.\n2. Local density analysis.(Only applying for an orthorhombic box)\n3. Fragment analysis.\n=====>";
			cin >> choice[1];
			//cout << "crit[4][4]=" << crit[4][4] << endl;
			if (choice[1] == 1)
			{
				//Bonding analysis
				double sumOfBonds[5][5][300];//各种化学键总长度
				int numOfBonds[5][5][300];//各种化学键个数
				memset(sumOfBonds, 0, sizeof(sumOfBonds));
				memset(numOfBonds, 0, sizeof(numOfBonds));
				int i = 0, j = 0, k = 0;
				
				while (k < NumOfLines / (numOfAtoms + 9))
				{
					i = 0;
					while (i < 5)
					{
						j = 0;
						while (j < 5)
						{
							sumOfBonds[i][j][k] = 0.0;
							numOfBonds[i][j][k] = 0;							
							j++;
						}
						i++;
					}
					k++;
				}
				
				{
					int i = 0, j = 0, k = 0;
					while (k < NumOfLines / (numOfAtoms + 9))
					{
						i = 0;
						while (i < numOfAtoms)
						{
							j = 0;
							while (j < numOfAtoms)
							{
								if (i == j)
								{
									j++;
								}
								else
								{
									float dis;
									dis = bonding(coordinate[i][0][k], coordinate[i][1][k], coordinate[i][2][k], coordinate[j][0][k], coordinate[j][1][k],
										coordinate[j][2][k], boxmax[0][k] - boxmin[0][k], boxmax[1][k] - boxmin[1][k], boxmax[2][k] - boxmin[2][k]);
									if (dis< (crit[type[i]][type[j]] * crit[type[i]][type[j]]))
									{										
										sumOfBonds[type[i]][type[j]][k] = sumOfBonds[type[i]][type[j]][k] + sqrt(dis);										
										numOfBonds[type[i]][type[j]][k] = numOfBonds[type[i]][type[j]][k] + 1;										
										j++;
									}
									else
									{
										j++;
									}
								}																	
							}
							i++;
						}
						k++;
						{
							if (k % 10 == 0||k==1||k== NumOfLines / (numOfAtoms + 9))
							{
								cout << endl << k << "/" << NumOfLines / (numOfAtoms + 9) << " complete...";
							}
							else
								k = k;
						}
					}
				}

				string outFile("Average bond length.txt");
				string outFile1("Number of bonds.txt");
				ofstream out;
				ofstream out1;
				out.open(outFile);
				out1.open(outFile1);
				float averBond[5][5][300];//平均键长
				{
					int i = 0, j = 0, k = 0;
					while (k < NumOfLines / (numOfAtoms + 9))
					{
						i = 0;
						while (i < 5)
						{
							j = 0;
							while (j < 5)
							{
								averBond[i][j][k] = (sumOfBonds[i][j][k] + sumOfBonds[j][i][k]) / (numOfBonds[i][j][k] + numOfBonds[j][i][k]);
								j++;
							}
							i++;
						}
						k++;
					}
				}//求出平均键长

				int numOfType[5] = { 0,0,0,0,0 };
				{//判断存在元素个数					
					i = 0;
					while (i < numOfAtoms)
					{
						if (type[i] == 0)
						{
							numOfType[0]++;
							i++;
						}
						else if (type[i] == 1)
						{
							numOfType[1]++;
							i++;
						}
						else if (type[i] == 2)
						{
							numOfType[2]++;
							i++;
						}
						else if (type[i] == 3)
						{
							numOfType[3]++;
							i++;
						}
						else 
						{
							numOfType[4]++;
							i++;
						}
					}
				}

				i = 0, j = 0, k = 0;
				while (i < 5)
				{
					j = 0;
					while (j < 5)
					{
						if (numOfType[i] == 0 || numOfType[j] == 0)
						{
							j++;
						}
						else
						{
							out << "Average bond length of " << elements[i] << "-" << elements[j] << "(1-" << NumOfLines / (numOfAtoms + 9) << " frames):" << endl;
							out1 << "Number of bonds of " << elements[i] << "-" << elements[j] << "(1-" << NumOfLines / (numOfAtoms + 9) << " frames):" << endl;
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								if (numOfBonds[i][j][k] == 0)
								{
									out << "No such bond exist." << endl;
									out1 << (numOfBonds[i][j][k] + numOfBonds[j][i][k])/2 << endl;
									k++;
								}
								else
								{
									out << averBond[i][j][k] << endl;
									out1 << (numOfBonds[i][j][k] + numOfBonds[j][i][k])/2 << endl;
									k++;
								}								
							}
							j++;
						}						
					}
					i++;
				}				
				out.close();
				out1.close();
				cout << "\n\nBonding data:\n====================\nAverage bond length.txt\n"
					<< "Number of bonds.txt\n====================\nare generated successfully.\n"
					<< "Press any key to continute analysis...";
				_getch();
			}
			else if (choice[1] == 2)
			{
				//Local density analysis
				cout << "\nChose an aera to calculate its density:\n1. [C]   2. [H]   3. [O]   4. [N]   5. [Al]   6. Al-Oxide   7. All\n=====>";
				float minCoor[3][300];//最小坐标
				float maxCoor[3][300];//最大坐标
				int numOfElement[5] = { 0,0,0,0,0 };
				cin >> choice[2];
				{
					if (choice[2] == 7)
					{
						int i, j, k;
						j = 0;
						while (j < 3)
						{//初始化最小/最大坐标
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								minCoor[j][k] = coordinate[0][j][k];
								maxCoor[j][k] = coordinate[0][j][k];
								k++;
							}
							j++;
						}
						
						j = 0;
						while (j < 3)//导入最小坐标
						{
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								i = 0;
								while (i < numOfAtoms)
								{
									if (minCoor[j][k] > coordinate[i][j][k])
									{
										minCoor[j][k] = coordinate[i][j][k] - 0.001;
										i++;
									}
									else
										i++;
								}
								k++;
							}
							j++;
						}

						j = 0;
						while (j < 3)//导入最大坐标
						{
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								i = 0;
								while (i < numOfAtoms)
								{
									if (maxCoor[j][k] < coordinate[i][j][k])
									{
										maxCoor[j][k] = coordinate[i][j][k] + 0.001;
										i++;
									}
									else
										i++;
								}
								k++;
							}
							j++;
						}

						double volume[300] ;//区域体积
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							volume[k] = (maxCoor[0][k] - minCoor[0][k])*(maxCoor[1][k] - minCoor[1][k])*(maxCoor[2][k] - minCoor[2][k]);
							k++;
						}
						
						double mass[300];//区域质量
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))//初始化区域质量
						{
							mass[k] = 0.0;
							k++;
						}

						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))//注入区域质量
						{
							i = 0;
							while (i < numOfAtoms)
							{
								if (coordinate[i][0][k] > minCoor[0][k] && coordinate[i][0][k]<maxCoor[0][k]
									&& coordinate[i][1][k]>minCoor[1][k] && coordinate[i][1][k]<maxCoor[1][k]
									&& coordinate[i][2][k]>minCoor[2][k] && coordinate[i][2][k] < maxCoor[2][k])
								{
									if (type[i] == 0)
									{
										mass[k] = mass[k] + 12.0110;
										i++;
									}
									else if (type[i] == 1)
									{
										mass[k] = mass[k] + 1.0080;
										i++;
									}
									else if (type[i] == 2)
									{
										mass[k] = mass[k] + 15.9990;
										i++;
									}
									else if (type[i] == 3)
									{
										mass[k] = mass[k] + 14.0070;
										i++;
									}
									else
									{
										mass[k] = mass[k] + 26.9820;
										i++;
									}										
								}
								else
									i++;
							}
							k++;
						}

						string outFile("Local density.txt");
						ofstream out;
						out.open(outFile);
						out << "Local density of all atoms area(1-"<< NumOfLines / (numOfAtoms + 9) <<" frames):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << mass[k] / volume[k] / 0.602214129 << endl;
							k++;
						}

						out << "Size of all area(X):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << maxCoor[0][k] - minCoor[0][k] << endl;
							k++;
						}
						out << "Size of all area(Y):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << maxCoor[1][k] - minCoor[1][k] << endl;
							k++;
						}
						out << "Size of all area(Z):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << maxCoor[2][k] - minCoor[2][k] << endl;
							k++;
						}
						out << "Volume of all area:\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << volume[k] << endl;
							k++;
						}
						out.close();
						cout << "\n\nLocal density data:\n====================\nLocal density.txt\n"
							<< "====================\nis exported in the same folder.\n"
							<< "Press any key to continute analysis...";
						_getch();
					}

					else if (choice[2] == 6)
					{
						cout << "Initial point along Z axis:";
						float ZPoint;
						cin >> ZPoint;
						short int atomNumTolerance = 0;
						cout << "Atom number tolerance = ";
						cin >> atomNumTolerance;
						cout << "Analyzing...";
						float minCoorOfO[3][300];
						float maxCoorOfO[3][300];
						float minCoorOfAl[3][300];
						float maxCoorOfAl[3][300];
						int i, j, k;
						float atomToleranceOMin[3][300];
						float atomToleranceOMax[3][300];
						float atomToleranceAlMin[3][300];
						float atomToleranceAlMax[3][300];
						j = 0;
						while (j < 3)
						{
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								atomToleranceOMin[j][k] = 0.0;
								atomToleranceOMax[j][k] = 10000.0;
								atomToleranceAlMin[j][k] = 0.0;
								atomToleranceAlMax[j][k] = 10000.0;
								k++;
							}
							j++;
						}

						j = 0;
						while (j < 3)
						{//初始化最小/最大Al坐标
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								i = 0;
								while (i < numOfAtoms)
								{
									if (type[i] == 4 && coordinate[i][2][k]>ZPoint)
									{
										minCoorOfAl[j][k] = coordinate[i][j][k];
										maxCoorOfAl[j][k] = coordinate[i][j][k];
										i++;
									}
									else
										i++;
								}
								k++;
							}
							j++;
						}

						{
							int l = 0;
							while (l <= atomNumTolerance)
							{
								j = 0;
								while (j < 3)
								{//初始化最小/最大O坐标
									k = 0;
									while (k < NumOfLines / (numOfAtoms + 9))
									{
										i = 0;
										while (i < numOfAtoms)
										{
											if (type[i] == 2 && coordinate[i][2][k] > ZPoint && coordinate[i][j][k] > atomToleranceOMin[j][k] && coordinate[i][j][k] < atomToleranceOMax[j][k])
											{
												minCoorOfO[j][k] = coordinate[i][j][k];
												maxCoorOfO[j][k] = coordinate[i][j][k];
												i++;
											}
											else
												i++;
										}
										k++;
									}
									j++;
								}
								j = 0;
								while (j < 3)//导入O最小坐标
								{
									k = 0;
									while (k < NumOfLines / (numOfAtoms + 9))
									{
										i = 0;
										while (i < numOfAtoms)
										{
											if (minCoorOfO[j][k] > coordinate[i][j][k] && type[i] == 2 && coordinate[i][2][k] > ZPoint && coordinate[i][j][k] > atomToleranceOMin[j][k])
											{
												minCoorOfO[j][k] = coordinate[i][j][k];
												i++;
											}
											else
												i++;
										}
										atomToleranceOMin[j][k] = minCoorOfO[j][k];
										k++;
									}
									j++;
								}
								
								j = 0;
								while (j < 3)//导入O最大坐标
								{
									k = 0;
									while (k < NumOfLines / (numOfAtoms + 9))
									{
										i = 0;
										while (i < numOfAtoms)
										{
											if (maxCoorOfO[j][k] < coordinate[i][j][k] && type[i] == 2 && coordinate[i][2][k]>ZPoint && coordinate[i][j][k] < atomToleranceOMax[j][k])
											{
												maxCoorOfO[j][k] = coordinate[i][j][k];
												i++;
											}
											else
												i++;
										}
										atomToleranceOMax[j][k] = maxCoorOfO[j][k];
										k++;
									}
									j++;
								}
								l++;
							}
						}


						{
							int l = 0;
							while (l <= atomNumTolerance)
							{
								j = 0;
								while (j < 3)
								{//初始化最小/最大Al坐标
									k = 0;
									while (k < NumOfLines / (numOfAtoms + 9))
									{
										i = 0;
										while (i < numOfAtoms)
										{
											if (type[i] == 4 && coordinate[i][2][k] > ZPoint && coordinate[i][j][k] > atomToleranceAlMin[j][k] && coordinate[i][j][k] < atomToleranceAlMax[j][k])
											{
												minCoorOfAl[j][k] = coordinate[i][j][k];
												maxCoorOfAl[j][k] = coordinate[i][j][k];
												i++;
											}
											else
												i++;
										}
										k++;
									}
									j++;
								}
								j = 0;
								while (j < 3)//导入Al最小坐标
								{
									k = 0;
									while (k < NumOfLines / (numOfAtoms + 9))
									{
										i = 0;
										while (i < numOfAtoms)
										{
											if (minCoorOfAl[j][k] > coordinate[i][j][k] && type[i] == 4 && coordinate[i][2][k] > ZPoint && coordinate[i][j][k] > atomToleranceAlMin[j][k])
											{
												minCoorOfAl[j][k] = coordinate[i][j][k];
												i++;
											}
											else
												i++;
										}
										atomToleranceAlMin[j][k] = minCoorOfAl[j][k];
										k++;
									}
									j++;
								}

								j = 0;
								while (j < 3)//导入Al最大坐标
								{
									k = 0;
									while (k < NumOfLines / (numOfAtoms + 9))
									{
										i = 0;
										while (i < numOfAtoms)
										{
											if (maxCoorOfAl[j][k] < coordinate[i][j][k] && type[i] == 4 && coordinate[i][2][k]>ZPoint && coordinate[i][j][k] < atomToleranceAlMax[j][k])
											{
												maxCoorOfAl[j][k] = coordinate[i][j][k];
												i++;
											}
											else
												i++;
										}
										atomToleranceAlMax[j][k] = maxCoorOfAl[j][k];
										k++;
									}
									j++;
								}
								l++;
							}
						}


						j = 0;
						while (j < 3)//注入最小坐标
						{
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								if (minCoorOfAl[j][k]< minCoorOfO[j][k])
								{
									minCoor[j][k] = minCoorOfO[j][k] - 0.001;
									k++;
								}
								else
								{
									minCoor[j][k] = minCoorOfAl[j][k] - 0.001;
									k++;
								}
							}
							j++;
						}
						j = 0;
						while (j < 3)//注入最大坐标
						{
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								if (maxCoorOfAl[j][k]> maxCoorOfO[j][k])
								{
									maxCoor[j][k] = maxCoorOfO[j][k] + 0.001;
									k++;
								}
								else
								{
									maxCoor[j][k] = maxCoorOfAl[j][k] + 0.001;
									k++;
								}
							}
							j++;
						}


					
						lineLocation = 0;
						read.open(inFile);
						while (getline(read, lines))
						{
							{
								if (lineLocation % (numOfAtoms + 9) == 5)
								{
									for (unsigned int i = 0; i < (lines.size()) + 1; i++)//坐标行字符串注入字符数组
									{
										wordsInLine[i] = lines[i];
									}

									spaceLocation[0] = 0;
									i = 0;
									while (i < lines.size())
									{
										if (lines[i] == ' ')
										{
											spaceLocation[0] = i;
											i++;
										}
										else
											i++;
									}
									string minBoxStr(wordsInLine + 0, wordsInLine + spaceLocation[0]);
									string maxBoxStr(wordsInLine + spaceLocation[0], wordsInLine + lines.size());
									minCoor[0][lineLocation / (numOfAtoms + 9)] = StringToFloat(minBoxStr);
									maxCoor[0][lineLocation / (numOfAtoms + 9)] = StringToFloat(maxBoxStr);
									lineLocation++;
								}
								else if (lineLocation % (numOfAtoms + 9) == 6)
								{
									for (unsigned int i = 0; i < (lines.size()) + 1; i++)//坐标行字符串注入字符数组
									{
										wordsInLine[i] = lines[i];
									}

									spaceLocation[0] = 0;
									i = 0;
									while (i < lines.size())
									{
										if (lines[i] == ' ')
										{
											spaceLocation[0] = i;
											i++;
										}
										else
											i++;
									}
									string minBoxStr(wordsInLine + 0, wordsInLine + spaceLocation[0]);
									string maxBoxStr(wordsInLine + spaceLocation[0], wordsInLine + lines.size());
									minCoor[1][lineLocation / (numOfAtoms + 9)] = StringToFloat(minBoxStr);
									maxCoor[1][lineLocation / (numOfAtoms + 9)] = StringToFloat(maxBoxStr);
									lineLocation++;
								}
								else
									lineLocation++;
							}
							{
								if (lineLocation % (NumOfLines / 10) == 0)
								{
									cout << endl << lineLocation / (NumOfLines / 10) * 10 << "% complete...";
								}
								else
									lineLocation = lineLocation;
							}
						}
						read.close();





						double volume[300];//区域体积
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							volume[k] = (maxCoor[0][k] - minCoor[0][k])*(maxCoor[1][k] - minCoor[1][k])*(maxCoor[2][k] - minCoor[2][k]);
							k++;
						}

						double mass[300];//区域质量
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))//初始化区域质量
						{
							mass[k] = 0.0;
							k++;
						}
						short int numOfAtom[5][300];
						i = 0;
						while (i < 5)
						{
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								numOfAtom[i][k] = 0;
								k++;
							}
							i++;
						}

						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))//注入区域质量
						{
							i = 0;
							while (i < numOfAtoms)
							{
								if (coordinate[i][0][k] > minCoor[0][k] && coordinate[i][0][k]<maxCoor[0][k]
									&& coordinate[i][1][k]>minCoor[1][k] && coordinate[i][1][k]<maxCoor[1][k]
									&& coordinate[i][2][k]>minCoor[2][k] && coordinate[i][2][k] < maxCoor[2][k])
								{
									if (type[i] == 0)
									{
										mass[k] = mass[k] + 12.0110;
										numOfAtom[0][k]++;
										i++;
									}
									else if (type[i] == 1)
									{
										mass[k] = mass[k] + 1.0080;
										numOfAtom[1][k]++;
										i++;
									}
									else if (type[i] == 2)
									{
										mass[k] = mass[k] + 15.9990;
										numOfAtom[2][k]++;
										i++;
									}
									else if (type[i] == 3)
									{
										mass[k] = mass[k] + 14.0070;
										numOfAtom[3][k]++;
										i++;
									}
									else
									{
										mass[k] = mass[k] + 26.9820;
										numOfAtom[4][k]++;
										i++;
									}										
								}
								else
									i++;
							}
							k++;
						}
						string outFile("Local density.txt");
						ofstream out;
						out.open(outFile);
						out << "Local density of Al-Oxide area(1-" << NumOfLines / (numOfAtoms + 9) << " frames):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << mass[k] / volume[k] / 0.602214129 << endl;
							k++;
						}
						out << "Size of Al-Oxide area(X):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << maxCoor[0][k] - minCoor[0][k] << endl;
							k++;
						}
						out << "Size of Al-Oxide area(Y):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << maxCoor[1][k] - minCoor[1][k] << endl;
							k++;
						}
						out << "Size of Al-Oxide area(Z):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << maxCoor[2][k] - minCoor[2][k] << endl;
							k++;
						}
						out << "Volume of Al-Oxide area:\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << volume[k] << endl;
							k++;
						}
						i = 0;
						while (i < 5)
						{
							out << "Number of " << elements[i] << endl;
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								out << numOfAtom[i][k] << endl;
								k++;
							}
							i++;
						}


						
						out.close();
						cout << "\n\nLocal density data:\n====================\nLocal density.txt\n"
							<< "====================\nis exported in the same folder.\n"
							<< "Press any key to continute analysis...";
						_getch();
					}

					else//若不选择全部区域
					{
						int i, j, k;
						j = 0;
						while (j < 3)
						{//初始化最小/最大坐标
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								i = 0;
								while (i < numOfAtoms)
								{
									if (type[i] == choice[2] - 1)
									{
										minCoor[j][k] = coordinate[0][j][k];
										maxCoor[j][k] = coordinate[0][j][k];
										i++;
									}
									else
										i++;
								}
								k++;
							}
							j++;
						}

						j = 0;
						while (j < 3)//导入最小坐标
						{
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								i = 0;
								while (i < numOfAtoms)
								{
									if (minCoor[j][k] > coordinate[i][j][k] && type[i] == choice[2] - 1)
									{
										minCoor[j][k] = coordinate[i][j][k] - 0.001;
										i++;
									}
									else
										i++;
								}
								k++;
							}
							j++;
						}

						j = 0;
						while (j < 3)//导入最大坐标
						{
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								i = 0;
								while (i < numOfAtoms)
								{
									if (maxCoor[j][k] < coordinate[i][j][k] && type[i] == choice[2] - 1)
									{
										maxCoor[j][k] = coordinate[i][j][k] + 0.001;
										i++;
									}
									else
										i++;
								}
								k++;
							}
							j++;
						}

						double volume[300];//区域体积
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							volume[k] = (maxCoor[0][k] - minCoor[0][k])*(maxCoor[1][k] - minCoor[1][k])*(maxCoor[2][k] - minCoor[2][k]);
							k++;
						}

						double mass[300];//区域质量
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))//初始化区域质量
						{
							mass[k] = 0.0;
							k++;
						}

						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))//注入区域质量
						{
							i = 0;
							while (i < numOfAtoms)
							{
								if (coordinate[i][0][k] > minCoor[0][k] && coordinate[i][0][k]<maxCoor[0][k]
									&& coordinate[i][1][k]>minCoor[1][k] && coordinate[i][1][k]<maxCoor[1][k]
									&& coordinate[i][2][k]>minCoor[2][k] && coordinate[i][2][k] < maxCoor[2][k])
								{
									if (type[i] == 0)
									{
										mass[k] = mass[k] + 12.0110;
										i++;
									}
									else if (type[i] == 1)
									{
										mass[k] = mass[k] + 1.0080;
										i++;
									}
									else if (type[i] == 2)
									{
										mass[k] = mass[k] + 15.9990;
										i++;
									}
									else if (type[i] == 3)
									{
										mass[k] = mass[k] + 14.0070;
										i++;
									}
									else
									{
										mass[k] = mass[k] + 26.9820;
										i++;
									}										
								}
								else
									i++;
							}
							k++;
						}

						string outFile("Local density.txt");
						ofstream out;
						out.open(outFile);
						out << "Local density of " << elements[choice[2] - 1] << " atoms area(1-" << NumOfLines / (numOfAtoms + 9) << " frames):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << mass[k] / volume[k] / 0.602214129 << endl;
							k++;
						}
						out << "Size of " << elements[choice[2] - 1] << " atoms area(X):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << maxCoor[0][k] - minCoor[0][k] << endl;
							k++;
						}
						out << "Size of " << elements[choice[2] - 1] << " atoms area(Y):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << maxCoor[1][k] - minCoor[1][k] << endl;
							k++;
						}
						out << "Size of " << elements[choice[2] - 1] << " atoms area(Z):\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << maxCoor[2][k] - minCoor[2][k] << endl;
							k++;
						}
						out << "Volume of " << elements[choice[2] - 1] << " atoms area:\n";
						k = 0;
						while (k < NumOfLines / (numOfAtoms + 9))
						{
							out << volume[k] << endl;
							k++;
						}
						out.close();
						cout << "\n\nLocal density data:\n====================\nLocal density.txt\n"
							<< "====================\nis exported in the same folder.\n"
							<< "Press any key to continute analysis...";
						_getch();
					}
				}
			}

			else//fragment analysis
			{
				short int group[40000][300];//碎片编号
				int l, m, n, o, k;
				k = 0;
				while (k < NumOfLines / (numOfAtoms + 9))//初始化group
				{
					l = 0;
					while (l < numOfAtoms)
					{
						group[l][k] = l;
						l++;
					}
					k++;
				}
				short int minNumOfFrag;
				cout << "\nAt least n fragments will be exported, n=";
				cin >> minNumOfFrag;
				cout << "\nPerforming fragment analysis, this may cost a moment...";
				k = 0;
				while (k < NumOfLines / (numOfAtoms + 9))
				{
					l = 0;
					while (l < numOfAtoms)
					{
						if (group[l][k] == l)
						{
							short int nMark[40000];
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
									if (group[n][k] == l && nMark[n] == 0)
									{
										o = 0;
										while (o < numOfAtoms)
										{											
											if (group[o][k] == o && 
												bonding(coordinate[n][0][k],coordinate[n][1][k],coordinate[n][2][k],coordinate[o][0][k],coordinate[o][1][k],coordinate[o][2][k]
													,boxmax[0][k]-boxmin[0][k],boxmax[1][k]-boxmin[1][k],boxmax[2][k]-boxmin[2][k]) < crit[type[n]][type[o]]* crit[type[n]][type[o]])
											{
												group[o][k] = group[n][k];
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
					k++;
					{
						if (k == 1 || k % 10 == 0 || k == NumOfLines / (numOfAtoms + 9))
						{
							cout << endl << k << "/" << NumOfLines / (numOfAtoms + 9) << " frames complete...";
						}
						else
							k = k;
					}
				}

				short int groupElement[40000][300][5];//碎片组成

				l = 0;
				while (l < numOfAtoms)//初始化碎片组成
				{
					k = 0;
					while (k < NumOfLines / (numOfAtoms + 9))
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
				while (k < NumOfLines / (numOfAtoms + 9))//注入碎片组成
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
				out1.open(outFile1);

				short int numOfFrag[40000][300];
				short int markFrag[40000][300];
				l = 0;
				while (l < numOfAtoms)
				{
					k = 0;
					while (k < NumOfLines / (numOfAtoms + 9))
					{
						numOfFrag[l][k] = 0;
						markFrag[l][k] = 0;
						k++;
					}
					l++;
				}

				k = 0;
				while (k < NumOfLines / (numOfAtoms + 9))//注入碎片数量
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
									&&groupElement[m][k][1] == groupElement[l][k][1] 
									&&groupElement[m][k][2] == groupElement[l][k][2] 
									&&groupElement[m][k][3] == groupElement[l][k][3] 
									&&groupElement[m][k][4] == groupElement[l][k][4])
								{
									numOfFrag[l][k]++;
									{
										if (m == l)
											m = m;
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
					k++;
				}

				short int kMark[40000][300];
				l = 0;
				while (l < numOfAtoms)
				{
					k = 0;
					while (k < NumOfLines / (numOfAtoms + 9))
					{
						kMark[l][k] = 0;
						k++;
					}					
					l++;
				}

				k = 0;
				while (k < NumOfLines / (numOfAtoms + 9))
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
				
				short int titleMark[40000][300];
				l = 0;
				while (l < numOfAtoms)
				{
					k = 0;
					while (k < NumOfLines / (numOfAtoms + 9))
					{
						titleMark[l][k] = 0;
						k++;
					}
					l++;
				}


				
				short int maxNumOfFrag[40000][300];
				l = 0;
				while (l < numOfAtoms)
				{
					k = 0;
					while (k < NumOfLines / (numOfAtoms + 9))
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
					while (k < NumOfLines / (numOfAtoms + 9))
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
								while (n < NumOfLines / (numOfAtoms + 9))
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

				l = 0;
				while (l < numOfAtoms)
				{
					k = 0;
					while (k < NumOfLines / (numOfAtoms + 9))
					{
						if (numOfFrag[l][k] == 0)
							k++;
						else
						{
							m = 0;
							while (m < numOfAtoms)
							{
								n = 0;
								while (n < NumOfLines / (numOfAtoms + 9))
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
									cout << "\nExporting fragment: ";
									out << "Fragment ";
									out1 << "Fragment ";
									{
										if (groupElement[l][k][0] == 0)
											l = l;
										else
										{
											cout << "C" << groupElement[l][k][0];
											out << "C" << groupElement[l][k][0];
											out1 << "C" << groupElement[l][k][0];
										}
									}
									{
										if (groupElement[l][k][1] == 0)
											l = l;
										else
										{
											cout << "H" << groupElement[l][k][1];
											out << "H" << groupElement[l][k][1];
											out1 << "H" << groupElement[l][k][1];
										}
									}
									{
										if (groupElement[l][k][2] == 0)
											l = l;
										else
										{
											cout << "O" << groupElement[l][k][2];
											out << "O" << groupElement[l][k][2];
											out1 << "O" << groupElement[l][k][2];
										}
									}
									{
										if (groupElement[l][k][3] == 0)
											l = l;
										else
										{
											cout << "N" << groupElement[l][k][3];
											out << "N" << groupElement[l][k][3];
											out1 << "N" << groupElement[l][k][3];
										}
									}
									{
										if (groupElement[l][k][4] == 0)
											l = l;
										else
										{
											cout << "Al" << groupElement[l][k][4];
											out << "Al" << groupElement[l][k][4];
											out1 << "Al" << groupElement[l][k][4];
										}
									}
									out << endl;
									out1 << endl;
									out1 << "@<TRIPOS>MOLECULE\nstructure\n50000 0 0 0 0 \nSMALL\nUSER_CHARGES\n\n\n@<TRIPOS>ATOM\n";



									int k1 = 0;//逐帧输出碎片数量
									while (k1 < NumOfLines / (numOfAtoms + 9))
									{
										m = 0;
										int mMark = 0;
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
									int l2 = 1;//碎片原子序号
									while (l1 < numOfAtoms)
									{
										if (group[l1][k] == l)
										{
											out1 << l2 << " " << elements[type[l1]] << "   " << coordinate[l1][0][k]
												<< "   " << coordinate[l1][1][k]
												<< "   " << coordinate[l1][2][k] << " " << elements[type[l1]] << " 0 **** 0" << endl;
											l2++;
											l1++;
										}
										else
											l1++;
									}
									out1 << "@<TRIPOS>BOND\n@<TRIPOS>CRYSIN\n" << a[k] << " " << b[k] << " " << c[k] << "  "
										<< acos((box_cross[0][k] * box_cross[1][k] + (boxmax[1][k] - boxmin[1][k])*box_cross[2][k]) / (b[k]*c[k])) / 3.141592653 * 180 << " "
										<< acos(box_cross[1][k] / c[k]) / 3.141592653 * 180 << " " << acos(box_cross[0][k] / b[k]) / 3.141592653 * 180 << " 1 1\n";
									titleMark[l][k] = 1;
									k++;
						        }						
							}
						}						
					}
					l++;
				}
				out.close();
				out1.close();
				cout << "\n\nFragment data:\n====================\nFragment data.txt\n"
					<< "Fragment structure.txt\n====================\nare exported in the same folder.\n"
					<< "Press any key to continute analysis...";
				_getch();
			}				
		}

		else if (choice[0] == 2)//若选择扩散分析
		{						
			int i = 0, j = 0, k = 1, startFrame = 0, axisId = 0;
			while (k < NumOfLines / (numOfAtoms + 9))
			{
				j = 0;
				while (j < 3)
				{
					i = 1;
					while (i < numOfAtoms)
					{
						coordinate[i][j][k] = newCoor(coordinate[i][j][k-1], coordinate[i][j][k], boxmax[j][k] - boxmin[j][k]);
						i++;
					}
					j++;
				}
				k++;
			}

			i = 0; k = 0; j = 0;
			cout << "\nDiffusion start from n_st(1-" << NumOfLines / (numOfAtoms + 9) << ") frame, n= ";
			cin >> startFrame;
			cout << "\nAnalysis along axis:\n1. X   2. Y   3. Z   4. All axis\n=====>";
			cin >> axisId;
			string axis;
			{
				if (axisId == 1)
					axis = "x";
				else if (axisId == 2)
					axis = "y";
				else if (axisId == 3)
					axis = "z";
				else
					axis = "all";
			}
			cout << "\nPick a diffusion mode:\n1. Mean squire displacement(MSD)\n2. Normal mean squire displacement(NMSD)\n=====>";
			cin >> choice[1];
			{
				if (choice[1] == 1)
				{
					float displacement[40000][3][300];
					k = 0;
					while (k < NumOfLines / (numOfAtoms + 9))
					{
						j = 0;
						while (j < 3)
						{
							i = 0;
							while (i < numOfAtoms)
							{
								displacement[i][j][k] = coordinate[i][j][k + startFrame - 1] - coordinate[i][j][startFrame - 1];
								i++;
							}
							j++;
						}
						k++;
					}
					cout << "\nPick a group to analyze:\n1. [C]   2. [H]   3. [O]   4. [N]   5. [Al]   6. All atoms\n=====>";
					cin >> choice[2];
					{
						if (choice[2] == 6)//若选择所有原子
						{
							float MSD[300];
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								MSD[k] = 0;
								k++;
							}
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9) + 1 - startFrame)
							{
								i = 0;
								while (i < numOfAtoms)
								{
									if (axisId == 1)
									{
										MSD[k] = MSD[k] + displacement[i][0][k] * displacement[i][0][k];
										i++;
									}
									else if (axisId == 2)
									{
										MSD[k] = MSD[k] + displacement[i][1][k] * displacement[i][1][k];
										i++;
									}
									else if (axisId == 3)
									{
										MSD[k] = MSD[k] + displacement[i][2][k] * displacement[i][2][k];
										i++;
									}
									else
									{
										MSD[k] = MSD[k] + displacement[i][0][k] * displacement[i][0][k] + displacement[i][1][k] * displacement[i][1][k] + displacement[i][2][k] * displacement[i][2][k];
										i++;
									}									
								}
								MSD[k] = MSD[k] / numOfAtoms;
								k++;
							}
							string outFile("MSD.txt");
							ofstream out;
							out.open(outFile);
							out << "MSD data of all atoms from " << startFrame << "_st frame along " << axis << " axis:" << endl;
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9) + 1 - startFrame)
							{
								out << MSD[k] << endl;
								k++;
							}
							out.close();
							cout << "\n\nMSD data:\n====================\nMSD.txt\n"
								<< "====================\nis exported in the same folder.\n"
								<< "Press any key to continute analysis...";
							_getch();
						}
						else//若选择某单一原子
						{
							float elementMSD[300];
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								elementMSD[k] = 0;
								k++;
							}
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9) + 1 - startFrame)
							{
								i = 0;
								int numOfElement = 0;
								while (i < numOfAtoms)
								{
									if (type[i] == choice[2]-1)
									{
										if (axisId == 1)
										{
											elementMSD[k] = elementMSD[k] + displacement[i][0][k] * displacement[i][0][k];
											i++;
										}
										else if (axisId == 2)
										{
											elementMSD[k] = elementMSD[k] + displacement[i][1][k] * displacement[i][1][k];
											i++;
										}
										else if (axisId == 3)
										{
											elementMSD[k] = elementMSD[k] + displacement[i][2][k] * displacement[i][2][k];
											i++;
										}
										else
										{
											elementMSD[k] = elementMSD[k] + displacement[i][0][k] * displacement[i][0][k] + displacement[i][1][k] * displacement[i][1][k] + displacement[i][2][k] * displacement[i][2][k];
											i++;
										}
										numOfElement++;
									}
									else
										i++;
								}
								elementMSD[k] = elementMSD[k] / numOfElement;
								k++;
							}
							string outFile("MSD.txt");
							ofstream out;
							out.open(outFile);
							out << "MSD data of "<<elements[choice[2]-1]<<" atoms from " << startFrame << "_st frame along " << axis << " axis:" << endl;
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9) + 1 - startFrame)
							{
								out << elementMSD[k] << endl;
								k++;
							}
							out.close();
							cout << "\n\nMSD data:\n====================\nMSD.txt\n"
								<< "====================\nis exported in the same folder.\n"
								<< "Press any key to continute analysis...";
							_getch();
						}
					}
				}
				else if (choice[1] == 2)//若选择NMSD分析
				{
					
					float center[300][3];
					cout << "\nPick a group to analyze:\n1. [C]   2. [H]   3. [O]   4. [N]   5. [Al]   6. All atoms\n=====>";
					cin >> choice[2];
					{
						if (choice[2] == 6)//选择所有原子
						{

							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								j = 0;
								while (j < 3)
								{
									center[k][j] = 0;
									j++;
								}
								k++;
							}//初始化坐标平均值矩阵
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								j = 0;
								while (j < 3)
								{
									i = 0;
									while (i < numOfAtoms)
									{
										center[k][j] = center[k][j] + coordinate[i][j][k];
										i++;
									}
									center[k][j] = center[k][j] / numOfAtoms;
									j++;
								}								
								k++;
							}//导入坐标平均值矩阵

							float displacement[40000][3][300];
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								j = 0;
								while (j < 3)
								{
									i = 0;
									while (i < numOfAtoms)
									{
										displacement[i][j][k] = (coordinate[i][j][k + startFrame - 1] - center[k + startFrame - 1][j]) - (coordinate[i][j][startFrame - 1] - center[startFrame - 1][j]);
										i++;
									}
									j++;
								}
								k++;
							}//导入位移矩阵
							float MSD[300];
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								MSD[k] = 0;
								k++;
							}
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9) + 1 - startFrame)
							{
								i = 0;
								while (i < numOfAtoms)
								{
									if (axisId == 1)
									{
										MSD[k] = MSD[k] + displacement[i][0][k] * displacement[i][0][k];
										i++;
									}
									else if (axisId == 2)
									{
										MSD[k] = MSD[k] + displacement[i][1][k] * displacement[i][1][k];
										i++;
									}
									else if (axisId == 3)
									{
										MSD[k] = MSD[k] + displacement[i][2][k] * displacement[i][2][k];
										i++;
									}
									else
									{
										MSD[k] = MSD[k] + displacement[i][0][k] * displacement[i][0][k] + displacement[i][1][k] * displacement[i][1][k] + displacement[i][2][k] * displacement[i][2][k];
										i++;
									}
								}
								MSD[k] = MSD[k] / numOfAtoms;
								k++;
							}
							string outFile("NMSD.txt");
							ofstream out;
							out.open(outFile);
							out << "NMSD data of all atoms from " << startFrame << "_st frame along " << axis << " axis:" << endl;
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9) + 1 - startFrame)
							{
								out << MSD[k] << endl;
								k++;
							}
							out.close();
							cout << "\n\nNMSD data:\n====================\nNMSD.txt\n"
								<< "====================\nis exported in the same folder.\n"
								<< "Press any key to continute analysis...";
							_getch();
						}
						else
						{
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								j = 0;
								while (j < 3)
								{
									center[k][j] = 0;
									j++;
								}
								k++;
							}//初始化坐标平均值
							k = 0;
							int numOfElement = 0;
							i = 0;
							while (i < numOfAtoms)
							{
								if (type[i] == choice[2] - 1)
								{
									numOfElement++;
									i++;
								}
								else
									i++;
							}//得到该元素个数
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								j = 0;
								while (j < 3)
								{
									i = 0;
									while (i < numOfAtoms)
									{
										if (type[i] == choice[2] - 1)
										{
											center[k][j] = center[k][j] + coordinate[i][j][k];
											i++;
										}
										else
											i++;
									}
									center[k][j] = center[k][j] / numOfElement;
									j++;
								}								
								k++;
							}//导入坐标平均数矩阵

							float displacement[40000][3][300];
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								j = 0;
								while (j < 3)
								{
									i = 0;
									while (i < numOfAtoms)
									{
										if (type[i] == choice[2] - 1)
										{
											displacement[i][j][k] = (coordinate[i][j][k + startFrame - 1] - center[k + startFrame - 1][j])
												- (coordinate[i][j][startFrame - 1] - center[startFrame - 1][j]);
											i++;
										}
										else
											i++;
									}
									j++;
								}
								k++;
							}//导入位移矩阵



							float elementMSD[300];
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9))
							{
								elementMSD[k] = 0;
								k++;
							}
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9) + 1 - startFrame)
							{
								i = 0;
								while (i < numOfAtoms)
								{
									if (type[i] == choice[2] - 1)
									{
										if (axisId == 1)
										{
											elementMSD[k] = elementMSD[k] + displacement[i][0][k] * displacement[i][0][k];
											i++;
										}
										else if (axisId == 2)
										{
											elementMSD[k] = elementMSD[k] + displacement[i][1][k] * displacement[i][1][k];
											i++;
										}
										else if (axisId == 3)
										{
											elementMSD[k] = elementMSD[k] + displacement[i][2][k] * displacement[i][2][k];
											i++;
										}
										else
										{
											elementMSD[k] = elementMSD[k] + displacement[i][0][k] * displacement[i][0][k] + displacement[i][1][k] * displacement[i][1][k] + displacement[i][2][k] * displacement[i][2][k];
											i++;
										}
									}
									else
										i++;
								}
								elementMSD[k] = elementMSD[k] / numOfElement;
								k++;
							}
							string outFile("NMSD.txt");
							ofstream out;
							out.open(outFile);
							out << "NMSD data of " << elements[choice[2] - 1] << " atoms from " << startFrame << "_st frame along "<<axis<<" axis:" << endl;
							k = 0;
							while (k < NumOfLines / (numOfAtoms + 9) + 1 - startFrame)
							{
								out << elementMSD[k] << endl;
								k++;
							}
							out.close();
							cout << "\n\nNMSD data:\n====================\nNMSD.txt\n"
								<< "====================\nis exported in the same folder.\n"
								<< "Press any key to continute analysis...";
							_getch();
						}
					}
				}
			}
		}
		else if (choice[0] == 3)
		{
			float minBox[3][300];//盒子最小值
			float maxBox[3][300];//盒子最大值
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

			cout << "\n1. Material Studio in-file\n2. Gaussian in-file\n3. Lammps data file\n=====>";
			cin >> choice[1];
			cout << "Export n_st (1-" << NumOfLines / (numOfAtoms + 9) << ") frame, n=";
			int kMark = 0;
			cin >> kMark;
			{
				if (choice[1] == 1)
				{
					
					string outFile("MS_inFile.mol2");
					ofstream out;
					out.open(outFile);
					out << "@<TRIPOS>MOLECULE\nstructure\n" << numOfAtoms << " 0 0 0 0 \nSMALL\nUSER_CHARGES\n\n\n@<TRIPOS>ATOM\n";
					int i = 0;
					while (i < numOfAtoms)
					{
						out << i + 1 << " " << elements[type[i]] << " " << coordinate[i][0][kMark - 1]-minBox[0][kMark-1] << " " 
							<< coordinate[i][1][kMark - 1] - minBox[1][kMark - 1] << " " << coordinate[i][2][kMark - 1] - minBox[2][kMark - 1]
							<< " " << elements[type[i]] << " 0 **** 0\n";
						i++;
					}
					out << "@<TRIPOS>BOND\n@<TRIPOS>CRYSIN\n" << a[kMark-1] << " " << b[kMark-1] << " " << c[kMark-1] << "  "
						<< acos((box_cross[0][kMark-1] * box_cross[1][kMark-1] + (boxmax[1][kMark-1] - boxmin[1][kMark-1])*box_cross[2][kMark-1]) / (b[kMark-1] * c[kMark-1])) / 3.141592653 * 180 << " "
						<< acos(box_cross[1][kMark-1] / c[kMark-1]) / 3.141592653 * 180 << " " << acos(box_cross[0][kMark-1] / b[kMark-1]) / 3.141592653 * 180 << " 1 1\n";
					out.close();
					cout << "\n\nMaterial Studio in-file:\n====================\nMS_inFile.mol2\n"
						<< "====================\nis exported in the same folder.\n"
						<< "Press any key to continute analysis...";
					_getch();
				}
				else if (choice[1] == 2)
				{
					string outFile("Gaussian_inFile.gjf");
					ofstream out;
					out.open(outFile);
					out << "# opt b3lyp/6-311++g(d,p)\n\ntitle\n\n0 1\n";
					int i = 0;
					while (i < numOfAtoms)
					{
						out << elements[type[i]] << "     " << coordinate[i][0][kMark - 1] << "     " << coordinate[i][1][kMark - 1] << "     " << coordinate[i][2][kMark - 1] << endl;
						i++;
					}
					out.close();
					cout << "\n\nGaussian in-file:\n====================\nGaussian_inFile.gjf\n"
						<< "====================\nis exported in the same folder.\n"
						<< "Press any key to continute analysis...";
					_getch();
				}
				else
				{
					string outFile("Lammps.data");
					ofstream out;
					out.open(outFile);
					out << "Lammps Data\n\n  " << numOfAtoms << " atoms\n\n" << "  5 atom types\n\n";
					out << "  0.000000000   " << doubleToString((maxBox[0][kMark - 1] - minBox[0][kMark - 1]), 13) << " xlo xhi\n";
					out << "  0.000000000   " << doubleToString((maxBox[1][kMark - 1] - minBox[1][kMark - 1]), 13) << " ylo yhi\n";
					out << "  0.000000000   " << doubleToString((maxBox[2][kMark - 1] - minBox[2][kMark - 1]), 13) << " zlo zhi\n";
					{
						{
							if (boxMark == 0)
								boxMark = 0;
							else
								out << " " << doubleToString(box_cross[0][kMark-1], 13) << " " << doubleToString(box_cross[1][kMark - 1], 13) << " " 
								<< doubleToString(box_cross[2][kMark - 1], 13) << " xy xz yz\n";
						}
					}
					out << "\nMasses\n\n" << "  1  12.011150 # c\n  2   1.007970 # h\n  3  15.999400 # o\n  4  14.006700 # n\n  5  26.982000 # al\n"
						<< "\n\nAtoms # full\n\n";
					int i = 0;
					while (i < numOfAtoms)
					{
						out << intToString(i+1, 7) << intToString(type[i]+1, 10) << "  0.000000" << doubleToString(coordinate[i][0][kMark - 1] - minBox[0][kMark - 1], 16)
							<< doubleToString(coordinate[i][1][kMark - 1] - minBox[1][kMark - 1], 16) << doubleToString(coordinate[i][2][kMark - 1] - minBox[2][kMark - 1], 16) << " \n";
						i++;
					}
					out << "\n";
					out.close();
					cout << "\n\nLammps data file:\n====================\nLammps.data\n"
						<< "====================\nis exported in the same folder.\n"
						<< "Press any key to continute analysis...";
					_getch();
				}
			}
		}
	}
	cin >> inFile;
}
