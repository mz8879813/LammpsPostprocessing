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
	nums << setiosflags(ios::fixed) << setprecision(4) << num;
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

int max(int num1, int num2)
{
	if (num1 < num2)
	{
		return num2;
	}
	else
		return num1;
}



int main()
{
	string ParaFile;//输入文件的文件名
	string unuse;
	string inFile1;
	double pbo1; bool pbo1mark = 0; int pbo1line = 1000;
	double pbo2; bool pbo2mark = 0; int pbo2line = 1000;
	double r0sigma; bool r0sigmamark = 0; int r0sigmaline = 1000;
	double pbe1; bool pbe1mark = 0; int pbe1line = 1000;
	double pbe2; bool pbe2mark = 0; int pbe2line = 1000;
	double Desigma; bool Desigmamark = 0; int Desigmaline = 1000;
	double rvdW; bool rvdWmark = 0; int rvdWline = 1000;
	double pvdW1; bool pvdW1mark = 0; int pvdW1line = 1000;
	double gammaw; bool gammawmark = 0; int gammawline = 1000;
	double Dij; bool Dijmark = 0; int Dijline;
	double alphaij; bool alphaijmark = 0; int alphaijline = 1000;
	double pc1; bool pc1mark = 0; int pc1line = 1000;
	double pc2; bool pc2mark = 0; int pc2line = 1000;
	double pc3; bool pc3mark = 0; int pc3line = 1000;
	double gammaij; bool gammaijmark = 0; int gammaijline = 1000;
	double pboc1; bool pboc1mark = 0; int pboc1line = 1000;
	double pboc2; bool pboc2mark = 0; int pboc2line = 1000;
	double pboc3; bool pboc3mark = 0; int pboc3line = 1000;
	double pboc4; bool pboc4mark = 0; int pboc4line = 1000;
	double pboc5; bool pboc5mark = 0; int pboc5line = 1000;
	double vali; bool valimark = 0; int valiline = 1000;
	double valj; bool valjmark = 0; int valjline = 1000;
	double povun2i; bool povun2imark = 0; int povun2iline = 1000;
	double povun2j; bool povun2jmark = 0; int povun2jline = 1000;
	double povun5i; bool povun5imark = 0; int povun5iline = 1000;
	double povun5j; bool povun5jmark = 0; int povun5jline = 1000;
	double povun6; bool povun6mark = 0; int povun6line = 1000;
	double povun7; bool povun7mark = 0; int povun7line = 1000;
	double qi; int qiline = 1000;
	double qj; int qjline = 1000;
	int Ncoord; int Ncoordline = 1000;
	double Blcry; int Blcryline = 1000;
	double ku = 1.602176565;
	double ke = 8.987;
	double NA = 6.022;
	double rij[100];
	double Etot[100];
	double Etot2[100];
	string line;
	cout << "Import parameter file: ";
	cin >> ParaFile;

	{
		if (ParaFile[0] == '\"')
		{
			ParaFile = ParaFile.substr(1, ParaFile.length() - 1);
			ParaFile = ParaFile.substr(0, ParaFile.length() - 1);
		}
		else
			ParaFile = ParaFile;
	}


	ifstream read1;
	read1.open(ParaFile);
	int lineLocation = 0;
	while (getline(read1, line))
	{
		if (line[0] == 'p'&&line[1] == 'b'&&line[2] == 'o'&&line[3] == '1')
		{
			pbo1line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'b'&&line[2] == 'o'&&line[3] == '2')
		{
			pbo2line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'r'&&line[1] == '0'&&line[2] == 's'&&line[3] == 'i')
		{
			r0sigmaline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'b'&&line[2] == 'e'&&line[3] == '1')
		{
			pbe1line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'b'&&line[2] == 'e'&&line[3] == '2')
		{
			pbe2line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'D'&&line[1] == 'e'&&line[2] == 's'&&line[3] == 'i')
		{
			Desigmaline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'r'&&line[1] == 'v'&&line[2] == 'd'&&line[3] == 'W')
		{
			rvdWline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'v'&&line[2] == 'd'&&line[3] == 'W')
		{
			pvdW1line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'g'&&line[1] == 'a'&&line[2] == 'm'&&line[3] == 'm'&&line[4] == 'a'&&line[5] == 'w')
		{
			gammawline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'D'&&line[1] == 'i'&&line[2] == 'j')
		{
			Dijline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'a'&&line[1] == 'l'&&line[2] == 'p'&&line[3] == 'h'&&line[4] == 'a'&&line[5] == 'i')
		{
			alphaijline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'c'&&line[2] == '1')
		{
			pc1line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'c'&&line[2] == '2')
		{
			pc2line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'c'&&line[2] == '3')
		{
			pc3line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'g'&&line[1] == 'a'&&line[2] == 'm'&&line[3] == 'm'&&line[4] == 'a'&&line[5] == 'i')
		{
			gammaijline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'o'&&line[2] == 'v'&&line[3] == 'u'&&line[4] == 'n'&&line[5] == '2'&&line[6] == 'i')
		{
			povun2iline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'o'&&line[2] == 'v'&&line[3] == 'u'&&line[4] == 'n'&&line[5] == '2'&&line[6] == 'j')
		{
			povun2jline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'o'&&line[2] == 'v'&&line[3] == 'u'&&line[4] == 'n'&&line[5] == '5'&&line[6] == 'i')
		{
			povun5iline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'o'&&line[2] == 'v'&&line[3] == 'u'&&line[4] == 'n'&&line[5] == '5'&&line[6] == 'j')
		{
			povun5jline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'o'&&line[2] == 'v'&&line[3] == 'u'&&line[4] == 'n'&&line[5] == '6')
		{
			povun6line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'o'&&line[2] == 'v'&&line[3] == 'u'&&line[4] == 'n'&&line[5] == '7')
		{
			povun7line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'N'&&line[1] == 'c'&&line[2] == 'o'&&line[3] == 'o'&&line[4] == 'r'&&line[5] == 'd')
		{
			Ncoordline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'B'&&line[1] == 'l'&&line[2] == 'c'&&line[3] == 'r'&&line[4] == 'y')
		{
			Blcryline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'b'&&line[2] == 'o'&&line[3] == 'c'&&line[4] == '1')
		{
			pboc1line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'b'&&line[2] == 'o'&&line[3] == 'c'&&line[4] == '2')
		{
			pboc2line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'b'&&line[2] == 'o'&&line[3] == 'c'&&line[4] == '3')
		{
			pboc3line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'b'&&line[2] == 'o'&&line[3] == 'c'&&line[4] == '4')
		{
			pboc4line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'p'&&line[1] == 'b'&&line[2] == 'o'&&line[3] == 'c'&&line[4] == '5')
		{
			pboc5line = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'v'&&line[1] == 'a'&&line[2] == 'l'&&line[3] == 'i')
		{
			valiline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'v'&&line[1] == 'a'&&line[2] == 'l'&&line[3] == 'j')
		{
			valjline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'q'&&line[1] == 'i')
		{
			qiline = lineLocation;
			lineLocation++;
		}
		else if (line[0] == 'q'&&line[1] == 'j')
		{
			qjline = lineLocation;
			lineLocation++;
		}
		else {
			lineLocation++;
		}

	}
	read1.close();
	pbo1line = pbo1line;
	read1.open(ParaFile);
	lineLocation = 0;
	while (getline(read1, line))
	{//导入初始参数
		if (lineLocation == pbo1line - 1)
		{
			read1 >> unuse>> pbo1>>pbo1mark;
			lineLocation++;
		}
		else if (lineLocation == pbo2line - 1)
		{
			read1 >> unuse >> pbo2 >> pbo2mark;
			lineLocation++;
		}
		else if (lineLocation == r0sigmaline - 1)
		{
			read1 >> unuse >> r0sigma >> r0sigmamark;
			lineLocation++;
		}
		else if (lineLocation == pbe1line - 1)
		{
			read1 >> unuse >> pbe1 >> pbe1mark;
			lineLocation++;
		}		
		else if (lineLocation == pbe2line - 1)
		{
			read1 >> unuse >> pbe2 >> pbe2mark;
			lineLocation++;
		}
		else if (lineLocation == Desigmaline - 1)
		{
			read1 >> unuse >> Desigma >> Desigmamark;
			lineLocation++;
		}
		else if (lineLocation == rvdWline - 1)
		{
			read1 >> unuse >> rvdW >> rvdWmark;
			lineLocation++;
		}
		else if (lineLocation == pvdW1line - 1)
		{
			read1 >> unuse >> pvdW1 >> pvdW1mark;
			lineLocation++;
		}
		else if (lineLocation == gammawline - 1)
		{
			read1 >> unuse >> gammaw >> gammawmark;
			lineLocation++;
		}
		else if (lineLocation == Dijline - 1)
		{
			read1 >> unuse >> Dij >> Dijmark;
			lineLocation++;
		}
		else if (lineLocation == alphaijline - 1)
		{
			read1 >> unuse >> alphaij >> alphaijmark;
			lineLocation++;
		}
		else if (lineLocation == pc1line - 1)
		{
			read1 >> unuse >> pc1 >> pc1mark;
			lineLocation++;
		}
		else if (lineLocation == pc2line - 1)
		{
			read1 >> unuse >> pc2 >> pc2mark;
			lineLocation++;
		}
		else if (lineLocation == pc3line - 1)
		{
			read1 >> unuse >> pc3 >> pc3mark;
			lineLocation++;
		}
		else if (lineLocation == gammaijline - 1)
		{
			read1 >> unuse >> gammaij >> gammaijmark;
			lineLocation++;
		}
		else if (lineLocation == pboc1line - 1)
		{
			read1 >> unuse >> pboc1 >> pboc1mark;
			lineLocation++;
		}
		else if (lineLocation == pboc2line - 1)
		{
			read1 >> unuse >> pboc2 >> pboc2mark;
			lineLocation++;
		}
		else if (lineLocation == pboc3line - 1)
		{
			read1 >> unuse >> pboc3 >> pboc3mark;
			lineLocation++;
		}
		else if (lineLocation == pboc4line - 1)
		{
			read1 >> unuse >> pboc4 >> pboc4mark;
			lineLocation++;
		}
		else if (lineLocation == pboc5line - 1)
		{
			read1 >> unuse >> pboc5 >> pboc5mark;
			lineLocation++;
		}
		else if (lineLocation == valiline - 1)
		{
			read1 >> unuse >> vali >> valimark;
			lineLocation++;
		}
		else if (lineLocation == valjline - 1)
		{
			read1 >> unuse >> valj >> valjmark;
			lineLocation++;
		}
		else if (lineLocation == qiline - 1)
		{
			read1 >> unuse >> qi;
			lineLocation++;
		}
		else if (lineLocation == qjline - 1)
		{
			read1 >> unuse >> qj;
			lineLocation++;
		}
		else if (lineLocation == povun2iline - 1)
		{
			read1 >> unuse >> povun2i >> povun2imark;
			lineLocation++;
		}
		else if (lineLocation == povun2jline - 1)
		{
			read1 >> unuse >> povun2j >> povun2jmark;
			lineLocation++;
		}
		else if (lineLocation == povun5iline - 1)
		{
			read1 >> unuse >> povun5i >> povun5imark;
			lineLocation++;
		}
		else if (lineLocation == povun5jline - 1)
		{
			read1 >> unuse >> povun5j >> povun5jmark;
			lineLocation++;
		}
		else if (lineLocation == povun6line - 1)
		{
			read1 >> unuse >> povun6;
			lineLocation++;
		}
		else if (lineLocation == povun7line - 1)
		{
			read1 >> unuse >> povun7;
			lineLocation++;
		}
		else if (lineLocation == Ncoordline - 1)
		{
			read1 >> unuse >> Ncoord;
			lineLocation++;
		}
		else if (lineLocation == Blcryline - 1)
		{
			read1 >> unuse >> Blcry;
			lineLocation++;
		}
		else
		{
			lineLocation++;
		}
	}
	read1.close();


	
	string scanFile;
	cout << "Import scan file:  ";
	cin >> scanFile;
	{
		if (scanFile[0] == '\"')
		{
			scanFile = scanFile.substr(1, scanFile.length() - 1);
			scanFile = scanFile.substr(0, scanFile.length() - 1);
		}
		else
			scanFile = scanFile;
	}

	ifstream read2;
	lineLocation = 0;
	read2.open(scanFile);
	while (getline(read2, line) && line[0] == '#')
	{
		lineLocation++;
	}
	int dataLine = lineLocation;
	read2.close();

	lineLocation = 0;
	read2.open(scanFile);
	while (getline(read2, line))
	{//导入扫描势能面数据
		if (lineLocation >= (dataLine - 1) && (lineLocation - dataLine) < 99)
		{
			read2 >> rij[lineLocation - dataLine + 1] >> Etot[lineLocation - dataLine + 1];
			lineLocation++;
		}
		else
			lineLocation++;
	}
	read2.close();

	int k = 0;
	double Efar = Etot[99];
	while (k < 100)
	{
		Etot[k] = (Etot[k] - Efar)*2625.5 / 4.184;
		k++;
	}
	
	k = 0;
	int kmin = 0;
	double Etotmin=1000;
	while (k < 100)
	{
		if (Etot[k] < Etotmin)
		{
			Etotmin = Etot[k];
			kmin = k;
			k++;
		}
		else
			k++;
	}
	int kcry1 = 0, kcry2 = 0;
	k = 0;
	while (k < 100)
	{
		if (rij[k] < Blcry)
		{
			kcry1 = k;
			k++;
		}
		else
			k++;
	}
	kcry2 = kcry1 + 1;

	k = 0;//存入原有键能
	while (k < 100)
	{
		Etot2[k] = Etot[k];
		k++;
	}

	int kmid;//处理键能曲线
	k = kmin;
	while (k < 100)
	{
		if (Etot[k] < Etot[kmin]/2)
		{
			kmid = k;
			k++;
		}
		else
			k++;
	}
	k = 0;
	while (k < 100)
	{
		if (k <= kmid)
		{
			Etot[k] = (Etot[k] - Etot[kmin]) * 2 * (Etot[kmin] - (ke*qi*qj*ku*ku / (pow((pow(rij[kmid], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184)) / Etot[kmin] + Etot[kmin];
			k++;
		}
		else
		{
			Etot[k] = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
			k++;
		}
	}




	double Elg[100];
	k = 0;
	while (k < 100)
	{
		Elg[k] = 0;
		k++;
	}

	int maxCycle;
	cout << "Max Cycle = ";
	cin >> maxCycle;
	cout << "\nStart fitting..." << endl;



	double residual;
	double error[100];
	double Tap[100];
	k = 0;
	while (k < 100)
	{
		Tap[k] = 20 * pow((rij[k] / 10), 7) - 70 * pow((rij[k] / 10), 6) + 84 * pow((rij[k] / 10), 5) - 35 * pow((rij[k] / 10), 4) + 1;
		k++;
	}

	double BO;
	double deltaij;
	double EvdW;
	double Eb;
	double f1, f2, f3, f4, f5, f13;
	double Ec;
	double Ecoreh;
	double Eunder;
	double pbo1opt[3], pbo2opt[3], r0sigmaopt[3], pbe1opt[3], pbe2opt[3], Desigmaopt[3], rvdWopt[3];	
	double gammawopt[3], Dijopt[3], alphaijopt[3], pc1opt[3], pc2opt[3], pc3opt[3], gammaijopt[3];
	double pboc3opt[3], pboc4opt[3], pboc5opt[3], povun2iopt[3], povun2jopt[3], povun5iopt[3], povun5jopt[3], povun6opt[3];
	double residualmin;
	double residuallast[10000];
	residuallast[0] = 1000.0;
	residual = 0.0;
	k = 0;
	while (k < 3)
	{
		pbo1opt[k] = pbo1;
		pbo2opt[k] = pbo2;
		r0sigmaopt[k] = r0sigma;
		pbe1opt[k] = pbe1;
		pbe2opt[k] = pbe2;
		Desigmaopt[k] = Desigma;
		rvdWopt[k] = rvdW;
		gammawopt[k] = gammaw;
		Dijopt[k] = Dij;
		alphaijopt[k] = alphaij;
		pc1opt[k] = pc1;
		pc2opt[k] = pc2;
		pc3opt[k] = pc3;
		gammaijopt[k] = gammaij;
		pboc3opt[k] = pboc3;
		pboc4opt[k] = pboc4;
		pboc5opt[k] = pboc5;
		povun2iopt[k] = povun2i;
		povun2jopt[k] = povun2j;
		povun5iopt[k] = povun5i;
		povun5jopt[k] = povun5j;
		povun6opt[k] = povun6;
		k++;
	}
	
	ofstream out1;
	string out1File("FittedParameters.txt");
	out1.open(out1File);
	out1 << "Cycle           R          Rd      pbo1      pbo2   r0sigma      pbe1      pbe2   Desigma      rvdW    gammaw       ";
	out1 << "Dij   alphaij       pc1       pc2       pc3   povun2i   povun2j   povun5i   povun5j   gammaij     pboc3     pboc4     pboc5\n";
	k = 0;
	int m = 0;
	int n = 0;
	while ((n < maxCycle) && (n < 10 || residuallast[max(0, n - 1)] != residual || residuallast[max(0, n - 2)] != residual || residuallast[max(0, n - 3)] != residual || residuallast[max(0, n - 4)] != residual))
	{
		{//优化pc3
			if (pc3mark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 3000)//***
				{
					pc3 = 1.0 + 0.01*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0; Eunder = 0;
					while (k <= kmin)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k]-Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pc3opt[0] = pc3;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					pc3 = pc3opt[0] - 0.01 + 0.0001*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0; Eunder = 0;
					while (k <= kmin)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k]-Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pc3opt[1] = pc3;//***
						m++;
					}
					else
						m++;
				}
				pc3 = pc3opt[1];//***
			}
		}
		{//优化pc1
			if (pc1mark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 400)//***
				{
					pc1 = 0.5 + 0.01*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= kmin)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pc1opt[0] = pc1;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					pc1 = pc1opt[0] - 0.01 + 0.0001*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= kmin)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pc1opt[1] = pc1;//***
						m++;
					}
					else
						m++;
				}
				pc1 = pc1opt[1];//***
			}
		}
		{//优化pc2
			if (pc2mark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					pc2 = 0.01 + 0.01*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= kmin)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pc2opt[0] = pc2;//***
						m++;
					}
					else
						m++;
				}
				m = 10;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					pc2 = pc2opt[0] - 0.01 + 0.0001*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= kmin)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pc2opt[1] = pc2;//***
						m++;
					}
					else
						m++;
				}									
				pc2 = pc2opt[1];//***
			}
		}
		{//优化r0sigma
			if (r0sigmamark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 400)//***
				{
					r0sigma = 0.5 + 0.01*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						r0sigmaopt[0] = r0sigma;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					r0sigma = r0sigmaopt[0] - 0.01 + 0.0001*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						r0sigmaopt[1] = r0sigma;//***
						m++;
					}
					else
						m++;
				}


				r0sigma = r0sigmaopt[1];//***
			}
		}		
		{//优化pbe2
			if (pbe2mark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				pbe2opt[0] = pbe2;
				while (m < 100)//***
				{
					pbe2 = 1.02 + 1.0*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbe2opt[0] = pbe2;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				pbe2opt[1] = pbe2opt[0];
				while (m < 200)//***
				{
					pbe2 = pbe2opt[0] - 1 + 0.01*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbe2opt[1] = pbe2;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				pbe2opt[2] = pbe2opt[1];
				while (m < 200)//***
				{
					pbe2 = pbe2opt[1] - 0.01 + 0.0001*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbe2opt[2] = pbe2;//***
						m++;
					}
					else
						m++;
				}
				pbe2 = pbe2opt[2];//***
			}
		}			
		{//优化pbo2new
			if (1 == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				pbo2opt[0] = pbo2;
				while (m < 12)//***
				{
					pbo2 = 4.0 + 1.0*m;//***
					k = kcry1;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < kcry1 + 2)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						residual = residual + fabs(BO - 1);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbo2opt[0] = pbo2;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				pbo2opt[1] = pbo2opt[0];
				while (m < 200)//***
				{
					pbo2 = pbo2opt[0] - 1 + 0.01*m;//***
					k = kcry1;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < kcry1 + 2)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						residual = residual + fabs(BO - 1);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbo2opt[1] = pbo2;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				pbo2opt[2] = pbo2opt[1];
				while (m < 200)//***
				{
					pbo2 = pbo2opt[1] - 0.01 + 0.0001*m;//***
					k = kcry1;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < kcry1 + 2)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						residual = residual + fabs(BO - 1);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbo2opt[2] = pbo2;//***
						m++;
					}
					else
						m++;
				}
				pbo2 = pbo2opt[2];//***
			}
		}
		{//优化rvdW
			if (rvdWmark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				rvdWopt[0] = rvdW;
				while (m < 700)//***
				{
					rvdW = 0.5 + 0.01*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						rvdWopt[0] = rvdW;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				rvdWopt[1] = rvdWopt[0];
				while (m < 200)//***
				{
					rvdW = rvdWopt[0] - 0.01 + 0.0001*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						rvdWopt[1] = rvdW;//***
						m++;
					}
					else
						m++;
				}
				rvdW = rvdWopt[1];//***				
			}
		}
		{//优化gammaw
			if (gammawmark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				gammawopt[0] = gammaw;
				while (m < 600)//***
				{
					gammaw = 1.0 + 1.0*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= kmin)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						gammawopt[0] = gammaw;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				gammawopt[1] = gammawopt[0];
				while (m < 200)//***
				{
					gammaw = gammawopt[0] - 1 + 0.01*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= kmin)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						gammawopt[1] = gammaw;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				gammawopt[2] = gammawopt[1];
				while (m < 200)//***
				{
					gammaw = gammawopt[1] - 0.01 + 0.0001*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= kmin)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						gammawopt[2] = gammaw;//***
						m++;
					}
					else
						m++;
				}
				gammaw = gammawopt[2];//***
			}
		}
		{//优化pboc3
			if (pboc3mark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 100)//***
				{
					pboc3 = 1.0001 + 1.0*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pboc3opt[0] = pboc3;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					pboc3 = pboc3opt[0] - 1 + 0.01*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pboc3opt[1] = pboc3;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					pboc3 = pboc3opt[1] - 0.01 + 0.0001*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pboc3opt[2] = pboc3;//***
						m++;
					}
					else
						m++;
				}
				pboc3 = pboc3opt[2];//***
			}
		}
		{//优化pboc4
			if (pboc4mark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 300)//***
				{
					pboc4 = 1.0001 + 1.0*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pboc4opt[0] = pboc4;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					pboc4 = pboc4opt[0] - 1 + 0.01*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pboc4opt[1] = pboc4;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					pboc4 = pboc4opt[1] - 0.01 + 0.0001*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pboc4opt[2] = pboc4;//***
						m++;
					}
					else
						m++;
				}
				pboc4 = pboc4opt[2];//***
			}
		}
		{//优化pboc5
			if (pboc5mark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 100)//***
				{
					pboc5 = 1.0001 + 1.0*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pboc5opt[0] = pboc5;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					pboc5 = pboc5opt[0] - 1 + 0.01*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pboc5opt[1] = pboc5;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					pboc5 = pboc5opt[1] - 0.01 + 0.0001*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pboc5opt[2] = pboc5;//***
						m++;
					}
					else
						m++;
				}
				pboc5 = pboc5opt[2];//***
			}
		}
		{//优化pbo1
		if (pbo1mark == 1)//***
			m = 0;
		else
		{
			m = 1;
			residualmin = 9999999.0;
			while (m < 50)//***
			{
				pbo1 = -0.01*m;//***
				k = kmin;
				residual = 0.0;
				BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
				while (k < 100)
				{
					BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
					deltaij = BO - 1;
					f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
					f3 = deltaij;
					f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
					f5 = f4;
					f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
					BO = BO*f1*f4*f5;
					Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
					f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
					EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
					Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
					Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
					Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
					residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
					k++;
				}
				if (residual < residualmin)
				{
					residualmin = residual;
					pbo1opt[0] = pbo1;//***
					m++;
				}
				else
					m++;
			}
			m = 0;
			residualmin = 9999999.0;
			while (m < 200)//***
			{
				pbo1 = pbo1opt[0] - 0.01 + 0.0001*m;//***
				k = kmin;
				residual = 0.0;
				BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
				while (k < 100)
				{
					BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
					deltaij = BO - 1;
					f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
					f3 = deltaij;
					f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
					f5 = f4;
					f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
					BO = BO*f1*f4*f5;
					Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
					f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
					EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
					Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
					Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
					Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
					residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
					k++;
				}
				if (residual < residualmin)
				{
					residualmin = residual;
					pbo1opt[1] = pbo1;//***
					m++;
				}
				else
					m++;
			}
			pbo1 = pbo1opt[1];//***
		}
		}
		{//优化pbo2
			if (pbo2mark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				pbo2opt[0] = pbo2;
				while (m < 12)//***
				{
					pbo2 = 4.0 + 1.0*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbo2opt[0] = pbo2;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				pbo2opt[1] = pbo2opt[0];
				while (m < 200)//***
				{
					pbo2 = pbo2opt[0] - 1 + 0.01*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbo2opt[1] = pbo2;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				pbo2opt[2] = pbo2opt[1];
				while (m < 200)//***
				{
					pbo2 = pbo2opt[1] - 0.01 + 0.0001*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbo2opt[2] = pbo2;//***
						m++;
					}
					else
						m++;
				}
				pbo2 = pbo2opt[2];//***
			}
		}
		{//优化povun2i
			if (povun2imark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 100)//***
				{
					povun2i = -100 + 1.0*m;//***
					povun2j = povun2i;
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						povun2iopt[0] = povun2i;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					povun2i = povun2iopt[0] - 1 + 0.01*m;//***
					povun2j = povun2i;
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						povun2iopt[1] = povun2i;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					povun2i = povun2iopt[1] - 0.01 + 0.0001*m;//***
					povun2j = povun2i;
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						povun2iopt[2] = povun2i;//***
						povun2jopt[2] = povun2j;//***
						m++;
					}
					else
						m++;
				}
				povun2i = povun2iopt[2];//***
				povun2j = povun2jopt[2];//***
			}
		}
		{//优化povun5i
			if (povun5imark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 100)//***
				{
					povun5i = 1 + 1.0*m;//***
					povun5j = povun5i;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						povun5iopt[0] = povun5i;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					povun5i = povun5iopt[0] - 1 + 0.01*m;//***
					povun5j = povun5i;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						povun5iopt[1] = povun5i;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					povun5i = povun5iopt[1] - 0.01 + 0.0001*m;//***
					povun5j = povun5i;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						povun5iopt[2] = povun5i;//***
						povun5jopt[2] = povun5j;//***
						m++;
					}
					else
						m++;
				}
				povun5i = povun5iopt[2];//***
				povun5j = povun5jopt[2];//***
			}
		}		
		{//优化gammaij
			if (gammaijmark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					gammaij = 0.0001 + 0.01*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						gammaijopt[0] = gammaij;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					gammaij = gammaijopt[0] - 0.01 + 0.0001*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						gammaijopt[1] = gammaij;//***
						m++;
					}
					else
						m++;
				}
				gammaij = gammaijopt[1];//***
			}
		}
		{//优化alphaij
			if (alphaijmark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				alphaijopt[0] = alphaij;
				while (m < 1000)//***
				{
					alphaij = 5.0 + 0.01*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						alphaijopt[0] = alphaij;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				alphaijopt[1] = alphaijopt[0];
				while (m < 200)//***
				{
					alphaij = alphaijopt[0] - 0.01 + 0.0001*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						alphaijopt[1] = alphaij;//***
						m++;
					}
					else
						m++;
				}
				alphaij = alphaijopt[1];//***
			}
		}
		{//优化Dij
			if (Dijmark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				Dijopt[0] = Dij;
				while (m < 98)//***
				{
					Dij = 0.0101 + 0.01*m;//***					
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						Dijopt[0] = Dij;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				Dijopt[1] = Dijopt[0];
				while (m < 200)//***
				{
					Dij = Dijopt[0] - 0.0099 + 0.0001*m;//***
					k = 0;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						Dijopt[1] = Dij;//***
						m++;
					}
					else
						m++;
				}
				Dij = Dijopt[1];//***
			}
		}		
		{//优化Desigma
			if (Desigmamark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 500)//***
				{
					Desigma = 0.0001 + 1.0*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						Desigmaopt[0] = Desigma;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					Desigma = Desigmaopt[0] - 1 + 0.01*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						Desigmaopt[1] = Desigma;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					Desigma = Desigmaopt[1] - 0.01 + 0.0001*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k <= 99)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						Desigmaopt[2] = Desigma;//***
						m++;
					}
					else
						m++;
				}
				Desigma = Desigmaopt[2];//***
			}
		}
		{//优化pbo1new
			if (1 == 1)//***
				m = 0;
			else
			{
				m = 1;
				residualmin = 9999999.0;
				while (m < 50)//***
				{
					pbo1 = -0.01*m;//***
					k = kcry1;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < kcry1+2)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						residual = residual + fabs(BO - 1);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbo1opt[0] = pbo1;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 200)//***
				{
					pbo1 = pbo1opt[0] - 0.01 + 0.0001*m;//***
					k = kcry1;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < kcry1 + 2)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						residual = residual + fabs(BO - 1);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbo1opt[1] = pbo1;//***
						m++;
					}
					else
						m++;
				}
				pbo1 = pbo1opt[1];//***
			}
		}
		{//优化pbe1
			if (pbe1mark == 1)//***
				m = 0;
			else
			{
				m = 0;
				residualmin = 9999999.0;
				while (m < 99)//***
				{
					pbe1 = -0.99 + 0.01*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbe1opt[0] = pbe1;//***
						m++;
					}
					else
						m++;
				}
				m = 0;
				residualmin = 9999999.0;
				while (m < 199)//***
				{
					pbe1 = pbe1opt[0] - 0.0099 + 0.0001*m;//***
					k = kmin;
					residual = 0.0;
					BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
					while (k < 100)
					{
						BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
						deltaij = BO - 1;
						f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
						f3 = deltaij;
						f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
						f5 = f4;
						f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
						BO = BO*f1*f4*f5;
						Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
						f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
						EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
						Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
						Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
						Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
						residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
						k++;
					}
					if (residual < residualmin)
					{
						residualmin = residual;
						pbe1opt[1] = pbe1;//***
						m++;
					}
					else
						m++;
				}

				pbe1 = pbe1opt[1];//***
			}
		}
		
		k = 0;
		residual = 0.0;
		BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
		while (k < 100)
		{
			BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
			deltaij = BO - 1;
			f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
			f3 = deltaij;
			f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
			f5 = f4;
			f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
			BO = BO*f1*f4*f5;
			Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
			f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
			EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
			Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
			Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
			Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
			residual = residual + fabs(Etot[k] - EvdW - Eb - Ec - Ecoreh - Elg[k] - Eunder);
			k++;
		}
		n++;
		{
			if ((n < maxCycle) && (n < 10 || residuallast[max(0, n - 1)] != residual || residuallast[max(0, n - 2)] != residual || residuallast[max(0, n - 3)] != residual || residuallast[max(0, n - 4)] != residual))
			{
				n = n;
			}
			else
			{
				out1 << "\n\nFitted Parameters:\nCycle           R          Rd      pbo1      pbo2   r0sigma      pbe1      pbe2   Desigma      rvdW    gammaw       ";
				out1 << "Dij   alphaij       pc1       pc2       pc3   povun2i   povun2j   povun5i   povun5j   gammaij     pboc3     pboc4     pboc5\n";
			}
		}
		cout << "Cycle = " << intToString(n, 4) << "   residual(R) = " << doubleToString(residual, 12)
			<< "   delta residual(Rd) = " << doubleToString(residuallast[max(0, n - 1)] - residual, 12) << " " << endl;
		out1 << intToString(n, 5) << doubleToString(residual, 12) << doubleToString(residuallast[max(n - 1, 0)] - residual, 12) << doubleToString(pbo1, 10) << doubleToString(pbo2, 10) << doubleToString(r0sigma, 10)
			<< doubleToString(pbe1, 10) << doubleToString(pbe2, 10) << doubleToString(Desigma, 10) << doubleToString(rvdW, 10)
			<< doubleToString(gammaw, 10) << doubleToString(Dij, 10) << doubleToString(alphaij, 10) << doubleToString(pc1, 10)
			<< doubleToString(pc2, 10) << doubleToString(pc3, 10) << doubleToString(povun2i,10) << doubleToString(povun2j, 10) << doubleToString(povun5i, 10) << doubleToString(povun5j, 10)
			<<doubleToString(gammaij, 10) << doubleToString(pboc3, 10)
			<< doubleToString(pboc4, 10) << doubleToString(pboc5, 10) << endl;
		residuallast[n] = residual;
	}
	out1.close();
	ofstream out2;
	string out2File = "Fitness.txt";
	out2.open(out2File);

	out2 << " Bond_length    E(T-DFT)    E(O-DFT) E(T-ReaxFF) E(O-ReaxFF)     E(bond)      E(vdW)  E(coulomb)    E(under)  Bond_order\n";
	k = 0;
	residual = 0.0;
	double Ereaxmid = 0.0;
	BO = 0.0; f13 = 0.0; EvdW = 0.0; Eb = 0.0; Ecoreh = 0.0;
	while (k < 100)
	{
		BO = pow(2.7182818284, pbo1*pow((rij[k] / r0sigma), pbo2));
		deltaij = BO - 1;
		f2 = exp(-1 * pboc1*deltaij) + exp(-1 * pboc1*deltaij);
		f3 = deltaij;
		f4 = 1 / (1 + exp(-1 * pboc3*(pboc4*BO*BO - deltaij) + pboc5));
		f5 = f4;
		f1 = 0.5*(vali + f2) / (vali + f2 + f3) + 0.5*(valj + f2) / (valj + f2 + f3);
		BO = BO*f1*f4*f5;
		Eunder = (-1 * povun5i*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2i*(BO - 1.0))) - povun5j*(1 - exp(povun6*(BO - 1.0))) / (1 + exp(-1 * povun2j*(BO - 1.0)))) / (1 + povun7);
		f13 = pow((pow(rij[k], 1.5591) + pow((1 / gammaw), 1.5591)), (1 / 1.5591));
		EvdW = Tap[k] * Dij*(pow(2.7182818284, (alphaij*(1 - (f13 / rvdW)))) - 2 * pow(2.7182818284, (alphaij / 2 * (1 - (f13 / rvdW)))));
		Eb = -1 * Desigma*BO*pow(2.7182818284, (pbe1*(1 - pow(BO, pbe2))));
		Ec = ke*qi*qj*ku*ku / (pow((pow(rij[k], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184;
		Ecoreh = pc2*pow(2.7182818284, pc3*(1 - rij[k] / pc1));
		out2 << doubleToString(rij[k], 12) << doubleToString(Etot[k], 12) << doubleToString(Etot2[k], 12) << doubleToString((EvdW + Eb + Ec + Ecoreh + Eunder), 12);
		{
			if (k < kmid)
			{
				out2 << doubleToString(((EvdW + Eb + Ec + Ecoreh + Eunder) - Etot2[kmin])*Etot2[kmin] / 2 / (Etot2[kmin] - (ke*qi*qj*ku*ku / (pow((pow(rij[kmid], 3) + pow(gammaij, (-1.5))), (1.0 / 3)))*NA * 10 / 4.184)) + Etot2[kmin], 12);
			}
			else
			{
				out2 << doubleToString((EvdW + Eb + Ec + Ecoreh + Eunder)*(k - kmid) / (99 - kmid) + Etot2[k] * (99 - k) / (99 - kmid), 12);
			}
		}			
		out2<< doubleToString(Eb + Ecoreh, 12) << doubleToString(EvdW, 12) << doubleToString(Ec, 12) << doubleToString(Eunder, 12)
			<< doubleToString(BO, 12) << endl;
		k++;
	}
	out2.close();

	{
		if (n == maxCycle)
		{
			cout << "\nMax Cycle reached, iteration terminated." << endl;
		}
		else
		{
			cout << "Residual converged." << endl;
		}
	}

	{//输出参数
		cout << "\nFitted parameters: " << endl;
		cout << "    pbo1=" << doubleToString(pbo1, 9);
		cout << "    pbo2=" << doubleToString(pbo2, 9);
		cout << " r0sigma=" << doubleToString(r0sigma, 9);
		cout << "    pbe1=" << doubleToString(pbe1, 9) << endl;
		cout << "    pbe2=" << doubleToString(pbe2, 9);
		cout << " Desigma=" << doubleToString(Desigma, 9);
		cout << "    rvdW=" << doubleToString(rvdW, 9);
		cout << "  gammaw=" << doubleToString(gammaw, 9) << endl;
		cout << "     Dij=" << doubleToString(Dij, 9);
		cout << " alphaij=" << doubleToString(alphaij, 9);
		cout << "     pc1=" << doubleToString(pc1, 9);
		cout << "     pc2=" << doubleToString(pc2, 9) << endl;
		cout << "     pc3=" << doubleToString(pc3, 9);
		cout << "   pboc3=" << doubleToString(pboc3, 9);
		cout << "   pboc4=" << doubleToString(pboc4, 9);
		cout << "   pboc5=" << doubleToString(pboc5, 9) << endl;
		cout << " povun2i=" << doubleToString(povun2i, 9);
		cout << " povun2j=" << doubleToString(povun2j, 9);
		cout << " povun5i=" << doubleToString(povun5i, 9);
		cout << " povun5j=" << doubleToString(povun5j, 9) << endl;
	}

	cout << "\nJob complete.\n";
	cout << "Press any key to exit.";
	_getch();
	return 0;
}

