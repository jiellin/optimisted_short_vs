#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <ctime>
#define MAXNUM 2147483647
using namespace std;

//返回最小值,如果其中一个为0则直接返回另一个。
int Min(int a, int b) {
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	return a>b ? b : a;
}

int main() {
	int row, column;
	//ifstream cin("1.txt");
	cout << "Please input the number of row and column:" << endl;
	while (scanf("%d%d", &row, &column) != EOF) {		
		//LM matrix
		vector<vector<int>> lm(row, vector<int>(column));

		//PM matrix
		vector<vector<int>> pm(row, vector<int>(column));

		//SPM matrix
		vector<vector<int>> spm(row + 1, vector<int>(column));
		for (int i = 0; i < column; i++)
			spm[0][i] = 0;

		//tem1 Vector
		vector<int> tem1(column);
		for (int i = 0; i < column; i++)
			tem1[i] = 0;

		cout << "Please input the row*column LM metrix:" << endl;
		/**
		*   输入初始矩阵 row行*column列
		*/
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				cin >> lm[i][j];
			}
		}

		/**
		*   转换LM矩阵到PM矩阵
		*/
		for (int j = 0; j < column; j++) {
			pm[0][j] = lm[0][j];
			if (lm[0][j] == 0) {
				spm[0][j] = MAXNUM;
				tem1[j] = MAXNUM;
			}
		}
		for (int i = 1; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (lm[i][j] == 0) {
					pm[i][j] = pm[i - 1][j];
					pm[i - 1][j] = 0;

					spm[i][j] = MAXNUM;
				}
				else {
					pm[i][j] = lm[i][j];
				}
			}
		}

		clock_t start, finish;
		start = clock();
		/**
		*   生成SPM矩阵
		*/
		//处理第一列
		int temp = 0;
		for (int i = 1; i < row + 1; i++) {
			if (pm[i - 1][0] == 0) {
				continue;
			}
			else {
				spm[i][0] = temp + pm[i - 1][0];
				temp = spm[i][0];
			}
		}

		//处理矩阵内部
		for (int i = 1; i < row + 1; i++) {
			for (int j = 1; j < column; j++) {
				if (spm[i][j] == MAXNUM) {
					continue;
				}
				int x, y;
				if (spm[i][j - 1] == MAXNUM)
					x = MAXNUM;
				else
					x = spm[i][j - 1];

				if (tem1[j] == MAXNUM)
					y = MAXNUM;
				else
					y = tem1[j] + pm[i - 1][j];
				
				spm[i][j] = Min(x, y);
				tem1[j] = spm[i][j];
			}
		}
		finish = clock();

		/**
		*   输入PM矩阵 (row+1)行*column列
		*/
		cout << "the running time is: " << (finish - start) << endl;
		for (int j = 0; j < column; j++)
			cout << spm[row][j] << "\t";
		cout << endl;
		/*cout << "Output the SPM metrix ((row+1)*column):" << endl;
		for (int i = 0; i < row+1; i++) {
			for (int j = 0; j < column; j++) {
				cout << spm[i][j] << "\t";
			}
			cout << endl;
		}*/
	}
}
