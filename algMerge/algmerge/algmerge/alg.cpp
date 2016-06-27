#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#define MAXNUM 2147483647
using namespace std;

//return the minimun number, if one is 0, return another number
int Min(int a, int b) {
	if (a == 0)
		return b;
	return a>b ? b : a;
}

struct minNode {
	int row;
	int col;
};

int main() {
	int row, column;

	cout << "*********************************************" << endl;
	cout << "__________________Algorithm__________________" << endl;
	cout << "*********************************************" << endl;
	cout << "Please input the number of row and column:" << endl;
	while (scanf("%d%d", &row, &column) != EOF) {
		//LM matrix
		vector<vector<int> > lm(row, vector<int>(column));
		cout << "LM create successd!" << endl;

		//PM matrix
		vector<vector<int> > pm(row, vector<int>(column));
		cout << "PM create successd!" << endl;

		//SPM matrix
		vector<vector<int> > spm(row + 1, vector<int>(column));
		cout << "SPM create successd!" << endl;


		//tem1 Vector
		vector<int> tem1(column);
		for (int i = 0; i < column; i++)
			tem1[i] = 0;

		//visited matrix
		vector<vector<bool> > visited(row + 1, vector<bool>(column));
		for (int i = 0; i < row + 1; i++)
			for (int j = 0; j < column; j++)
				visited[i][j] = false;
		cout << "Visited create successd!" << endl;

		//compare Vector
		vector<int> compare(column);

		int min = MAXNUM;
		minNode index;


		cout << "Random input the row*column LM metrix:" << endl;
		/**
		*   random the LM matrix, row*column
		*/
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				lm[i][j] = rand() % 10;
				//cin >> lm[i][j];
			}
		}

		cout << "LM metrix:" << endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < column; j++) {
				cout << lm[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl;

		int flag = 0;
		cin >> flag;
		if (flag != 1) {
			cout << "Input LM is illegel, Please continue.";
			continue;
		}

		/**
		*   Translate LM matrix to PM matrix
		*/
		//translate the first row of LM 
		for (int j = 0; j < column; j++) {
			pm[0][j] = lm[0][j];
		}
		//translate other rows of LM to PM
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
		cout << "Translate LM to PM finished!" << endl;


		clock_t start, finish;
		start = clock();

		/**
		* ________________________________________________________________________________________
		* DP algotithm
		* compute the SPM matrix
		* ________________________________________________________________________________________
		*/
		//compute the first row
		for (int i = 0; i < column; i++)
			spm[0][i] = 0;

		//compute the first column
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

		//compute other modes
		for (int i = 1; i < row + 1; i++) {
			for (int j = 1; j < column; j++) {

				if (spm[i][j] == MAXNUM) {
					continue;
				}
				int x, y;
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
		*   Output SPM matrix (row+1)*column
		*/
		cout << "the DPALG running time is: " << (finish - start) << endl;
		for (int j = 0; j < column; j++)
			cout << spm[row][j] << "\t";
		cout << endl;
		/**
		* ________________________________________________________________________________________
		* DP algotithm END!
		* ________________________________________________________________________________________
		*/


		/**
		* ****************************************************************************************
		* ODijkstra Algorithm
		* ****************************************************************************************
		*/

		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++) {
				if (lm[i][j] == 0) 
					spm[i][j] = MAXNUM;
				else
					spm[i][j] = -1;
			}
		for (int j = 0; j < column; j++)
			spm[row][j] = -1;

		for (int i = 0; i < column; i++)
			tem1[i] = 0;


		cout << "SPM IS ok!" << endl;
		/**
		* ****************************************************************************************
		* Find the first normal node of each column
		* store the index into compare[]ÖÐ£¬
		* meadwhile modify spm[unusual node] = 0, where unusual node is above the first normal node
		* ****************************************************************************************
		*/
		start = clock();
		for (int j = 0; j < column; j++) {
			for (int i = 0; i < row; i++) {
				if (lm[i][j] != 0) {
					compare[j] = i;
					spm[i][j] = 0;
					visited[i][j] = true;
					break;
				}
				else {
					spm[i][j] = 0;
					visited[i][j] = true;
				}
			}
		}

		/**
		* ****************************************************************************************
		* Find the second normal node of each column
		* store the index into compare[]ÖÐ
		* meadwhile modify spm[unusual node] = inify, where unusual node is below the first normal node
		* meanwhile initialize spm[][] of T
		* ****************************************************************************************
		*/
		for (int j = 0; j < column; j++) {
			for (int i = compare[j]; i < row; i++) {
				if (pm[i][j] != 0) {
					compare[j] = i + 1;
					spm[i + 1][j] = pm[i][j];
					break;
				}
				else {
					spm[i + 1][j] = MAXNUM;
					visited[i + 1][j] = true;
				}
			}
		}

		while (visited[row][column - 1] != true) {

			min = spm[compare[0]][0];
			index = { compare[0], 0 };
			for (int j = 1; j < column; j++) {
				if (spm[compare[j]][j] < min) {
					min = spm[compare[j]][j];
					index = { compare[j], j };
				}
			}

			//using the theorem 3 to search the next vertex and modify S ans T
			for (int j = index.col; j < column; j++) {
				if (visited[index.row][j] == false) {
					tem1[j] = min;
					spm[index.row][j] = min;
					visited[index.row][j] = true;
					compare[j] = index.row + 1;

					while (compare[j] < row + 1 && spm[compare[j]][j] == MAXNUM) {
						compare[j] ++;
					}
				}
				else {
					break;
				}
			}

			//updete ASPM[T]
			for (int j = index.col; j < column; j++) {
				if (compare[j] < row + 1) {
					spm[compare[j]][j] = tem1[j] + pm[compare[j] - 1][j];
				}
				else {
					break;
				}
			}
		}
		finish = clock();

		/**
		*   Output SPM matrix (row+1)*column
		*/
		cout << "the ODijkstra running time is: " << (finish - start) << endl;
		for (int j = 0; j < column; j++)
			cout << spm[row][j] << "\t";
		cout << endl;
	}
}
