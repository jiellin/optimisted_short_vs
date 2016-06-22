#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>
#define MAXNUM 2147483647
using namespace std;

struct minNode {
	int row;
	int col;
};

int main() {
	int row, column;

	cout << "*********************************************" << endl;
	cout << "____________Algorithm of Myself ____________" << endl;
	cout << "*********************************************" << endl;
	cout << "Please input the number of row and column:" << endl;
	while (scanf("%d%d", &row, &column) != EOF) {
		//LM matrix
		vector<vector<int>> lm(row, vector<int>(column));

		//PM matrix
		vector<vector<int>> pm(row, vector<int>(column));

		//SPM matrix
		vector<vector<int>> spm(row + 1, vector<int>(column));
		for (int i = 0; i < row + 1; i++)
			for (int j = 0; j < column; j++)
				spm[i][j] = -1;

		//visited matrix
		vector<vector<bool>> visited(row + 1, vector<bool>(column));
		for (int i = 0; i < row + 1; i++)
			for (int j = 0; j < column; j++)
				visited[i][j] = false;

		//tem1 Vector
		vector<int> tem1(column);
		for (int i = 0; i < column; i++)
			tem1[i] = 0;

		//compare Vector
		vector<int> compare(column);


		int min = MAXNUM;
		minNode index;

		/**
		*   �����ʼ���� row��*column��
		*/
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				cin >> lm[i][j];
			}
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

		clock_t start, finish;
		start = clock();
		/**
		*   Optimized Dijkstra Shortest Path Algorithm
		*/
		//��ʼ��SPM����ĵ�һ���е�normal node�ľ���Ϊ0
		for (int j = 0; j < column; j++) { 
			spm[0][j] = 0;
			visited[0][j] = true;
		}

		//��ʼ�����Ƚϼ���TΪGMͼ�ĵڶ���
		//compare[j]����Ǵ��Ƚϵ������   
		//��compare[j]�洢��J�еĵ�I�о�OK��
		for (int j = 0; j < column; j++) {
			int i = 1;
			for (i = 1; i <= row; i++) {
				if (spm[i][j] != MAXNUM) {
					spm[i][j] = pm[i - 1][j];   //tem1[]��ʼ��ȫΪ0������Ҫ�ټ�
					compare[j] = i;
					break;
				}
				else {
					spm[i][j] = 0;
					visited[i][j] = true;
					continue;
				}
			}
		}

		//int count = 0;
		//int i = 1;
		while (visited[row][column - 1] != true) {

			//if ((count++) == 1) {
			//	//print PM
			//	cout << "PM!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			//	for (int i = 0; i < row; i++) {
			//		for (int j = 0; j < column; j++)
			//			cout << pm[i][j] << "\t";
			//		cout << endl;
			//	}
			//	cout << "COMPARED!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			//	for (int j = 0; j < column; j++)
			//		cout << compare[j] << "\t";
			//	cout << endl << "SPM!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			//	for (int i = 0; i <= row; i++) {
			//		for (int j = 0; j < column; j++)
			//			cout << spm[i][j] << "\t";
			//		cout << endl;
			//	}
			//	break;
			//}

			min = spm[compare[0]][0];
			index = { compare[0], 0 };
			for (int j = 1; j < column; j++) {
				if (spm[compare[j]][j] < min) {
					min = spm[compare[j]][j];
					index = { compare[j], j };
				}
			}
		
			//cout << count++ << ":" <<  index.row << "\t" << index.col << "\t" << spm[index.row][index.col] << endl;
			if (spm[index.row][index.col] != 0) { 
				int r = index.row;
				//using the theorem 3 to search the next vertex and modify S ans T
				for (int j = index.col; j < column; j++) {
					if (visited[r][j] == false) {
						tem1[j] = min;
						spm[r][j] = min;
						visited[r][j] = true;
						compare[j] = r+1;

						while (compare[j] < row + 1 &&  spm[compare[j]][j] == MAXNUM) {
							compare[j] ++;
						}
					}
					else {
						break;
					}
				}
			}
			else {
				visited[index.row][index.col] = true;
				compare[index.col] = index.row + 1;

				while (compare[index.col] < row + 1 && spm[compare[index.col]][index.col] == MAXNUM) {
					compare[index.col] ++;
				}
			}

			//����T�޸�SPM[T]����̾���
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
		*   ����PM���� (row+1)��*column��
		*/
		cout << "the running time is: " << (finish - start) << endl;
		for (int j = 0; j < column; j++)  
			cout << spm[row][j] << "\t";
		cout << endl;
		/*cout << "output the spm metrix ((row+1)*column):" << endl;
		for (int i = 0; i < row+1; i++) {
			for (int j = 0; j < column; j++) {
				cout << spm[i][j] << "\t";
			}
			cout << endl;
		}*/
	}
}
