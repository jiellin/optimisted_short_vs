#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>
#define MAXNUM 2147483647
using namespace std;

int main() {
	int row, column;

	cout << "Please input the number of row and column:" << endl;
	while (scanf("%d%d", &row, &column) != EOF) {
		//LM matrix
		vector<vector<int>> lm(row, vector<int>(column));

		//PM matrix
		vector<vector<int>> pm(row, vector<int>(column));

		//SPM matrix
		vector<vector<int>> spm(row + 1, vector<int>(column));
		for (int i = 0; i < row+1; i++)
			for (int j = 0; j < column; j++)
				spm[i][j] = -1;

		//visited matrix
		vector<vector<bool>> visited(row + 1, vector<bool>(column));
		for (int i = 0; i < row+1; i++)
			for (int j = 0; j < column; j++)
				visited[i][j] = false;

		//tem1 Vector
		vector<int> tem1(column);
		for (int i = 0; i < column; i++)
			tem1[i] = 0;

		//compare Vector
		vector<int> compare(column);

		/**
		*   输入初始矩阵 row行*column列
		*/
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				cin >> lm[i][j];
			}
		}

		/**
		*   Translate LM matrix to PM matrix
		*/
		for (int j = 0; j < column; j++) {
			pm[0][j] = lm[0][j];
			if (lm[0][j] == 0) {
				spm[0][j] = MAXNUM;
				visited[0][j] = true;

				tem1[j] = MAXNUM;   //从上面无法到达j
			}
		}
		for (int i = 1; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (lm[i][j] == 0) {
					pm[i][j] = pm[i - 1][j];
					pm[i - 1][j] = 0;

					spm[i][j] = MAXNUM;
					visited[i][j] = true;
				}
				else {
					pm[i][j] = lm[i][j];
				}
			}
		}

		clock_t start, finish;
		start = clock();
		/**
		*   Optimized Dijkstra Shortest Path Algorithm
		*/
		//SPM矩阵第一行初始化为0
		for (int j = 0; j < column; j++) {
			if (lm[0][j] != 0) {
				spm[0][j] = 0;
				visited[0][j] = true;
			}
		}

		//初始化待比较T集合的SPM——第二行
		for (int j = 0; j < column; j++) {
			int i = 1;
			for (i = 1; i <= row; i++) {
				if (spm[i][j] != MAXNUM) {
					spm[i][j] = pm[i - 1][j] + tem1[j];
					compare[j] = i * column + j;
					break;
				}
				else {
					continue;
				}
			}

			if (j == 0 && spm[i][j] == MAXNUM) {
				visited[i][j] = true;
				spm[i][j] = 0;

				compare[j] = (i + 1) * column + j;
				spm[i + 1][j] = pm[i][j];
			}
		}

		int count = 0;
		int i = 1;
		while (visited[row][column - 1] != true) {
			int min = MAXNUM;
			int index = 0;

			for (int j = 0; j < column; j++) {
				int r = compare[j] / column;
				int c = compare[j] % column;
				if (spm[r][c] < min) {
					min = spm[r][c];
					index = compare[j];
				}
			}

			//using the theorem 3 to search the next vertex and modify S ans T
			int r = index / column;
			for (int j = index%column; j < column; j++) {
				if (visited[r][j] == false) {
					tem1[j] = min;
					spm[r][j] = min;
					visited[r][j] = true;
					compare[j] = index / column*column + j + column;

					while (compare[j] < (row + 1)*column &&  spm[compare[j] / column][compare[j] % column] == MAXNUM) {
						compare[j] += column;
					}
				}
				else {
					break;
				}
			}

			//按照T修改SPM[T]的最短距离
			for (int j = 0; j < column; j++) {
				if (compare[j] < (row + 1)*column) {
					int r = compare[j] / column;
					int c = compare[j] % column;

					if (spm[r][c] == MAXNUM)
						continue;
					else
						spm[r][c] = tem1[j] + pm[r - 1][c];
				}
				else {
					continue;				//可能有错误
				}
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
	}
}
