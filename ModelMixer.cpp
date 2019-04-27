// ModelMixer.cpp : 定义控制台应用程序的入口点。
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
#include<iomanip>
using namespace std;

string intToString(int num, int length)
{
	char empty[100];
	int i = 0;
	while (i < 100)
	{
		empty[i]=' ';
		i++;
	}
	string result(empty+0,empty+length);
	ostringstream nums;
	nums <<  num;
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




int main()
{
	cout << "Welcome using Model Mixer(V1.25)!\nProgramed by Cui-fang Li\nDepartment of chemcal engineering\n";
	cout << "Nanjing university of science and technology.\nAny problem please contact E-mail: mz8879813@163.com\n\n";
	cout << "========================NOTICE========================\nThis program will embed SECOND model into FIRST model!\n";
	cout << "Only provide for Lammps data file!\n======================================================\n\n";
	string inFile1, inFile2;
	cout << "Import first model : ";
	cin >> inFile1;
	ifstream read1(inFile1);
	string line;
	int numOfAtoms[3];
	int lineLocation = 0;
	int massLine[2];
	int atomLine[2];
	int boxLine[2];
	int atomsLine[2];
	int newType[10][2];
	int boxMark = 0;
	{
		int i = 0;
		while (i < 10)
		{
			newType[i][0] = 0;
			newType[i][1] = 0;
			i++;
		}
	}

	while (getline(read1, line))
	{
		if (line[0] == 'M')
		{
			massLine[0] = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'A')
		{
			atomLine[0] = lineLocation;
			lineLocation++;
		}
		else if (line.size() > 5)
		{
			if (line[line.size() - 1] == 'i'&&line[line.size() - 2] == 'h'&&line[line.size() - 3] == 'x')
			{
				boxLine[0] = lineLocation;
				lineLocation++;
			}
			else if (line[line.size() - 1] == 's'&&line[line.size() - 2] == 'm'&&line[line.size() - 3] == 'o'&&line[line.size() - 4] == 't'&&line[line.size() - 5] == 'a')
			{
				atomsLine[0] = lineLocation;
				lineLocation++;
			}
			else if (line[line.size() - 1] == 'z'&&line[line.size() - 2] == 'y'&&line[line.size() - 3] == ' '&&line[line.size() - 4] == 'z'&&line[line.size() - 5] == 'x')
			{
				boxMark = 1;
				lineLocation++;
			}
			else
				lineLocation++;
		}
		else
			lineLocation++;
	}
	read1.close();
	read1.open(inFile1);
	lineLocation = 0;
	while (getline(read1, line))
	{
		if (lineLocation > massLine[0] && lineLocation < atomLine[0] && line.size()>5)
		{
			if (line[line.size()-1] == 'c')
			{
				int i = line.size();
				int oldType = 0;
				while (i >= 0)
				{
					if (line[i] > 48 && line[i] < 58)
					{
						oldType = line[i] - 48;
						i--;
					}
					else
					{
						i--;
					}
				}
				newType[oldType][0] = 1;
				lineLocation++;
			}
			else if (line[line.size()-1] == 'h')
			{
				int i = line.size();
				int oldType = 0;
				while (i >= 0)
				{
					if (line[i] > 48 && line[i] < 58)
					{
						oldType = line[i] - 48;
						i--;
					}
					else
					{
						i--;
					}
				}
				newType[oldType][0] = 2;
				lineLocation++;
			}
			else if (line[line.size()-1] == 'o')
			{
				int i = line.size();
				int oldType = 0;
				while (i >= 0)
				{
					if (line[i] > 48 && line[i] < 58)
					{
						oldType = line[i] - 48;
						i--;
					}
					else
					{
						i--;
					}
				}
				newType[oldType][0] = 3;
				lineLocation++;
			}
			else if (line[line.size()-1] == 'n')
			{
				int i = line.size();
				int oldType = 0;
				while (i >= 0)
				{
					if (line[i] > 48 && line[i] < 58)
					{
						oldType = line[i] - 48;
						i--;
					}
					else
					{
						i--;
					}
				}
				newType[oldType][0] = 4;
				lineLocation++;
			}
			else if (line[line.size()-1] == 'l')
			{
				int i = line.size();
				int oldType = 0;
				while (i >= 0)
				{
					if (line[i] > 48 && line[i] < 58)
					{
						oldType = line[i] - 48;
						i--;
					}
					else
					{
						i--;
					}
				}
				newType[oldType][0] = 5;
				lineLocation++;
			}
			else
				lineLocation++;
		}
		else
			lineLocation++;
	}
	read1.close();


	double boxMin[3][3];
	double boxMax[3][3];
	double box_xy = 0.0; double box_yz = 0.0; double box_xz = 0.0; 
	int startCoor = 100000;
	float noneUse;
	int type[100000][3];
	double coordinate[100000][3][3];
	read1.open(inFile1);
	lineLocation = 0;
	while (getline(read1, line))
	{
		if (lineLocation == atomsLine[0]-1)
		{
			read1 >> numOfAtoms[0];
			lineLocation++;
		}
		else if (lineLocation == boxLine[0] - 1)
		{
			read1 >> boxMin[0][0] >> boxMax[0][0];
			lineLocation++;
		}
		else if (lineLocation == boxLine[0])
		{
			read1 >> boxMin[1][0] >> boxMax[1][0];
			lineLocation++;
		}
		else if (lineLocation == boxLine[0] + 1)
		{
			read1 >> boxMin[2][0] >> boxMax[2][0];
			lineLocation++;
		}
		else if (boxMark == 1 && (lineLocation == boxLine[0] + 2))
		{
			read1 >> box_xy >> box_xz >> box_yz;
			lineLocation++;
		}
		else if (line[0] == 'A')
		{
			startCoor = lineLocation + 1;
			lineLocation++;
		}
		else if (lineLocation >= startCoor && lineLocation < startCoor + numOfAtoms[0])
		{
			read1 >> noneUse >> type[lineLocation - startCoor][0] >> noneUse >> coordinate[lineLocation - startCoor][0][0]
				>> coordinate[lineLocation - startCoor][1][0] >> coordinate[lineLocation - startCoor][2][0];
			lineLocation++;
		}
		else
		{
			lineLocation++;
		}			
	}
	read1.close();


	cout << "Import second model : ";
	cin >> inFile2;
	ifstream read2(inFile2);
	lineLocation = 0;

	while (getline(read2, line))
	{
		if (line[0] == 'M')
		{
			massLine[1] = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'A')
		{
			atomLine[1] = lineLocation;
			lineLocation++;
		}
		else if (line.size() > 5)
		{
			if (line[line.size() - 1] == 'i'&&line[line.size() - 2] == 'h'&&line[line.size() - 3] == 'x')
			{
				boxLine[1] = lineLocation;
				lineLocation++;
			}
			else if (line[line.size() - 1] == 's'&&line[line.size() - 2] == 'm'&&line[line.size() - 3] == 'o'&&line[line.size() - 4] == 't'&&line[line.size() - 5] == 'a')
			{
				atomsLine[1] = lineLocation;
				lineLocation++;
			}
			else
				lineLocation++;
		}
		else
			lineLocation++;
	}
	read2.close();
	read2.open(inFile2);
	lineLocation = 0;
	while (getline(read2, line))
	{
		if (lineLocation > massLine[1] && lineLocation < atomLine[1] && line.size()>5)
		{
			if (line[line.size()-1] == 'c')
			{
				int i = line.size();
				int oldType = 0;
				while (i >= 0)
				{
					if (line[i] > 48 && line[i] < 58)
					{
						oldType = line[i] - 48;
						i--;
					}
					else
					{
						i--;
					}
				}
				newType[oldType][1] = 1;
				lineLocation++;
			}
			else if (line[line.size()-1] == 'h')
			{
				int i = line.size();
				int oldType = 0;
				while (i >= 0)
				{
					if (line[i] > 48 && line[i] < 58)
					{
						oldType = line[i] - 48;
						i--;
					}
					else
					{
						i--;
					}
				}
				newType[oldType][1] = 2;
				lineLocation++;
			}
			else if (line[line.size()-1] == 'o')
			{
				int i = line.size();
				int oldType = 0;
				while (i >= 0)
				{
					if (line[i] > 48 && line[i] < 58)
					{
						oldType = line[i] - 48;
						i--;
					}
					else
					{
						i--;
					}
				}
				newType[oldType][1] = 3;
				lineLocation++;
			}
			else if (line[line.size()-1] == 'n')
			{
				int i = line.size();
				int oldType = 0;
				while (i >= 0)
				{
					if (line[i] > 48 && line[i] < 58)
					{
						oldType = line[i] - 48;
						i--;
					}
					else
					{
						i--;
					}
				}
				newType[oldType][1] = 4;
				lineLocation++;
			}
			else if (line[line.size()-1] == 'l')
			{
				int i = line.size();
				int oldType = 0;
				while (i >= 0)
				{
					if (line[i] > 48 && line[i] < 58)
					{
						oldType = line[i] - 48;
						i--;
					}
					else
					{
						i--;
					}
				}
				newType[oldType][1] = 5;
				lineLocation++;
			}
			else
				lineLocation++;
		}
		else
			lineLocation++;
	}
	read2.close();




	lineLocation = 0;
	read2.open(inFile2);
	startCoor = 100000;
	while (getline(read2, line))
	{
		if (lineLocation == atomsLine[1]-1)
		{
			read2 >> numOfAtoms[1];
			lineLocation++;
		}
		else if (lineLocation == boxLine[1]-1)
		{
			read2 >> boxMin[0][1] >> boxMax[0][1];
			lineLocation++;
		}
		else if (lineLocation == boxLine[1])
		{
			read2 >> boxMin[1][1] >> boxMax[1][1];
			lineLocation++;
		}
		else if (lineLocation == boxLine[1]+1)
		{
			read2 >> boxMin[2][1] >> boxMax[2][1];
			lineLocation++;
		}
		else if (line[0] == 'A')
		{
			startCoor = lineLocation + 1;
			lineLocation++;
		}
		else if (lineLocation >= startCoor && lineLocation < startCoor + numOfAtoms[1])
		{
			read2 >> noneUse >> type[lineLocation - startCoor][1] >> noneUse >> coordinate[lineLocation - startCoor][0][1]
				>> coordinate[lineLocation - startCoor][1][1] >> coordinate[lineLocation - startCoor][2][1];
			lineLocation++;
		}
		else
		{
			lineLocation++;
		}
	}
	read2.close();

	double a = boxMax[0][0] - boxMin[0][0]; double b = pow(((boxMax[1][0] - boxMin[1][0])*(boxMax[1][0] - boxMin[1][0]) + box_xy*box_xy), 0.5);
	double c = pow(((boxMax[2][0] - boxMin[2][0])*(boxMax[2][0] - boxMin[2][0]) + box_xz*box_xz + box_yz*box_yz), 0.5);

	cout << "Keep molecules perfectly?\n1. Yes\n2. No\n";
	int choice;
	cin >> choice;
	int group[100000];
	{
		int i = 0;
		while (i < numOfAtoms[0])
		{
			group[i] = i;
			i++;
		}
	}
	{
		if (choice == 1)
		{
			double crit[6][6];//原子成键截断距离
			{
				crit[0][0] = 1.5351; crit[0][1] = 1.0940; crit[0][2] = 1.4246; crit[0][3] = 1.4710; crit[0][4] = 1.9600;
				crit[1][0] = 1.0940; crit[1][1] = 0.7414; crit[1][2] = 0.9575; crit[1][3] = 1.0120; crit[1][4] = 1.6482;
				crit[2][0] = 1.4246; crit[2][1] = 0.9575; crit[2][2] = 1.4750; crit[2][3] = 1.4530; crit[2][4] = 1.8422;
				crit[3][0] = 1.4710; crit[3][1] = 1.0120; crit[3][2] = 1.4530; crit[3][3] = 1.4490; crit[3][4] = 1.9225;
				crit[4][0] = 1.9600; crit[4][1] = 1.6482; crit[4][2] = 1.8422; crit[4][3] = 1.9225; crit[4][4] = 2.8524;
			}
			double scaleFactor;
			cout << "Scale factor of bonding radius (Recommended value: 1.2) : ";
			cin >> scaleFactor;
			{
				int i = 0, j = 0;
				while (i < 6)
				{
					j = 0;
					while (j < 6)
					{
						crit[i][j] = crit[i][j] * scaleFactor;
						j++;
					}
					i++;
				}

			}
			
			int l = 0;
			while (l < numOfAtoms[0])
			{
				if (group[l] == l)
				{
					short int nMark[100000];
					int m = 0;
					while (m < numOfAtoms[0])
					{
						nMark[m] = 0;
						m++;
					}
					m = 0;
					while (m < 100)//链接次数
					{
						int n = 0;
						while (n < numOfAtoms[0])
						{
							if (group[n] == l && nMark[n] == 0)
							{
								int o = 0;
								while (o < numOfAtoms[0])
								{
									float distance;
									distance = bonding(coordinate[n][0][0], coordinate[n][1][0], coordinate[n][2][0], 
										coordinate[o][0][0], coordinate[o][1][0], coordinate[o][2][0], 
										boxMax[0][0] - boxMin[0][0], boxMax[1][0] - boxMin[1][0], boxMax[2][0] - boxMin[2][0]);
									if (group[o] == o && distance < crit[newType[type[n][0]][0] - 1][newType[type[o][0]][0] - 1] * crit[newType[type[n][0]][0] - 1][newType[type[o][0]][0] - 1])
									{
										group[o] = group[n];
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
		}
		else
			cout << "\n";	
	}
	

	cout << "Thickness of vacuum layer (angstrom) : ";
	double vac;
	cin >> vac;

	
	{
		int i = 0;
		while (i < numOfAtoms[0])
		{
			int j = 0;
			while(j<3)
			{
				coordinate[i][j][0] = coordinate[i][j][0] - boxMin[j][0];
				j++;
			}
			i++;
		}
	}
	{
		int i = 0;
		while (i < numOfAtoms[1])
		{
			int j = 0;
			while (j<3)
			{
				coordinate[i][j][1] = coordinate[i][j][1] - boxMin[j][1];
				j++;
			}
			i++;
		}
	}
	int delGroup[100000];
	{
		int i = 0;
		while (i < numOfAtoms[0])
		{
			delGroup[i] = 0;
			i++;
		}
	}
	{
		int i = 0, j = 0;
		while (i < numOfAtoms[0])
		{
			j = 0;
			while (j < numOfAtoms[1])
			{
				double dis;
				dis = bonding(coordinate[i][0][0], coordinate[i][1][0], coordinate[i][2][0],
					coordinate[j][0][1], coordinate[j][1][1], coordinate[j][2][1],
					boxMax[0][0] - boxMin[0][0], boxMax[1][0] - boxMin[1][0], boxMax[2][0] - boxMin[2][0]);
				if (dis < vac*vac)
				{
					delGroup[i] = 1;
					j++;
				}
				else
					j++;
			}
			i++;
		}
	}
	{
		int i = 0;
		while (i < numOfAtoms[0])
		{
			if (delGroup[i] == 1)
			{
				int j = 0;
				while (j < numOfAtoms[0])
				{
					if (group[j] == group[i] && delGroup[j] == 0)
					{
						delGroup[j] = 1;
						j++;
					}
					else
						j++;
				}
				i++;
			}
			else
				i++;
		}
	}



	{
		int i = 0, j = 0;
		while (i < numOfAtoms[0])
		{
			if (delGroup[i] == 1)
				i++;
			else
			{
				j++;
				i++;
			}
		}
		numOfAtoms[2] = j + numOfAtoms[1];
	}
	string element[100000][2];
	{
		int i = 0;
		while (i < numOfAtoms[0])
		{
			if (newType[type[i][0]][0] == 1)
			{
				element[i][0] = "C";
				i++;
			}
			else if (newType[type[i][0]][0] == 2)
			{
				element[i][0] = "H";
				i++;
			}
			else if (newType[type[i][0]][0] == 3)
			{
				element[i][0] = "O";
				i++;
			}
			else if (newType[type[i][0]][0] == 4)
			{
				element[i][0] = "N";
				i++;
			}
			else
			{
				element[i][0] = "Al";
				i++;
			}
		}
		i = 0;
		while (i < numOfAtoms[1])
		{
			if (newType[type[i][1]][1] == 1)
			{
				element[i][1] = "C";
				i++;
			}
			else if (newType[type[i][1]][1] == 2)
			{
				element[i][1] = "H";
				i++;
			}
			else if (newType[type[i][1]][1] == 3)
			{
				element[i][1] = "O";
				i++;
			}
			else if (newType[type[i][1]][1] == 4)
			{
				element[i][1] = "N";
				i++;
			}
			else
			{
				element[i][1] = "Al";
				i++;
			}
		}
	}
	int numOfTypes[6] = { 0,0,0,0,0,0 };
	{
		int i = 0;
		while (i < numOfAtoms[0])
		{
			if (delGroup[i] == 1)
				i++;
			else
			{
				numOfTypes[newType[type[i][0]][0]]++;
				i++;
			}
		}
		i = 0;
		while (i < numOfAtoms[1])
		{
			numOfTypes[newType[type[i][1]][1]]++;
			i++;
		}
	}
	string elementOfType[6] = { " ","C","H","O","N","Al" };



	string outFile("mix.data");
	string outMSfile("mix.mol2");
	ofstream out(outFile);
	ofstream outMS(outMSfile);
	outMS << "@<TRIPOS>MOLECULE\nstructure\n" << numOfAtoms[2] << " 0 0 0 0 \nSMALL\nUSER_CHARGES\n\n\n@<TRIPOS>ATOM\n";
	out << "LAMMPS     ";
	{
		int i = 1;
		while (i < 6)
		{
			if (numOfTypes[i] == 0)
				i++;
			else
			{
				out << elementOfType[i] << " " << numOfTypes[i] << "  ";
				i++;
			}				
		}
	}
	out << "\n\n  " << numOfAtoms[2] << " atoms\n\n" << "  5 atom types\n\n";
	out << "  0.000000000   " << doubleToString(boxMax[0][0] - boxMin[0][0], 13) << " xlo xhi\n";
	out << "  0.000000000   " << doubleToString(boxMax[1][0] - boxMin[1][0], 13) << " ylo yhi\n";
	out << "  0.000000000   " << doubleToString(boxMax[2][0] - boxMin[2][0], 13) << " zlo zhi\n";
	{
		if (boxMark == 0)
			boxMark = 0;
		else
			out << " " << doubleToString(box_xy, 13) << " " << doubleToString(box_xz, 13) << " " << doubleToString(box_yz, 13) << " xy xz yz\n";
	}
	out	<< "\nMasses\n\n" << "  1  12.011150 #c\n  2  1.007970 #h\n  3  15.999400 #o\n  4  14.006700 #n\n  5  26.982000 #al\n"
		<< "\n\nAtoms # full\n\n";
	int newNumOfAtom = 0;
	{//注入第一个模型坐标
		int i = 0, j = 1;
		while (i < numOfAtoms[0])
		{
			if (delGroup[i] == 1)
				i++;
			else
			{
				out << intToString(j, 7) << intToString(newType[type[i][0]][0], 10) << "  0.000000" << doubleToString(coordinate[i][0][0], 16)
					<< doubleToString(coordinate[i][1][0], 16) << doubleToString(coordinate[i][2][0],16) << " \n";
				outMS << j << " " << element[i][0] << " " << coordinate[i][0][0] << " " << coordinate[i][1][0] << " " << coordinate[i][2][0]
					<< " " << element[i][0] << " 0 **** 0\n";
				i++;
				j++;
			}				
		}
		newNumOfAtom = j;
	}

	{//注入第二个模型坐标
		int i = 0, j = newNumOfAtom;
		while (i < numOfAtoms[1])
		{
			out << intToString(j, 7) << intToString(newType[type[i][1]][1], 10) << "  0.000000" << doubleToString(coordinate[i][0][1], 16)
				<< doubleToString(coordinate[i][1][1], 16) << doubleToString(coordinate[i][2][1],16) << " \n";
			outMS << j << " " << element[i][1] << " " << coordinate[i][0][1] << " " << coordinate[i][1][1] << " " << coordinate[i][2][1]
				<< " " << element[i][1] << " 0 **** 0\n";
			j++;
			i++;
		}
	}
	
	outMS << "@<TRIPOS>BOND\n@<TRIPOS>CRYSIN\n" << boxMax[0][0] - boxMin[0][0] << " "
		<< pow(((boxMax[1][0] - boxMin[1][0])*(boxMax[1][0] - boxMin[1][0]) + box_xy*box_xy), 0.5)
		<< " " << pow(((boxMax[2][0] - boxMin[2][0])*(boxMax[2][0] - boxMin[2][0]) + box_xz*box_xz + box_yz*box_yz), 0.5)
		<< "  " << acos((box_xy*box_xz + (boxMax[1][0] - boxMin[1][0])*box_yz) / (b*c)) / 3.141592653 * 180 << " "
		<< acos(box_xz / c) / 3.141592653 * 180 << " " << acos(box_xy / b) / 3.141592653 * 180 << " 1 1\n";
	out << "\n";
	out.close();
	outMS.close();
	cout << "\nOut file:\n<mix.data>\n<mix.mol2>\nexported successfully!\n";



	system("pause");
    return 0;
}

