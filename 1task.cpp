#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
int** createMatrix(T n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    return matrix;
}

template <typename T>
int** copyMatrix(T** source, size_t n) {
    int** dest = createMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = source[i][j];
        }
    }
    return dest;
}

void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void saveMatrix(int** matrix, int n, const char* filename = "") {
    ofstream file;
    file.open(filename);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (filename[0] != '\0' && file.is_open()) {
                file << matrix[i][j] << "\t";
            }
        }
        if (filename[0] != '\0' && file.is_open()) {
            file << endl;
        }
    }
    
    if (file.is_open()) {
        file.close();
    }
}

template <typename T>
void bubbleSort(T* M, size_t size) {
    for (size_t j = 0; j < size; j++)
	for (size_t step = 1; step < size; ++step) {
		bool isSorted = true;
		for (size_t i = size - 1; i >= step; --i) {
                if (M[j][i] < M[j][i - 1]) {
                    std::swap(M[j][i], M[j][i - 1]);
				isSorted = false;
			}
		}
		if (isSorted) break;
	}
}

template <typename T>
void selectionSortColumns(T* M, size_t n) {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int k = i + 1; k < n; k++) {
                if (M[k][j] < M[minIdx][j]) {
                    minIdx = k;
                }
            }
            if (minIdx != i) {
                int temp = M[i][j];
                M[i][j] = M[minIdx][j];
                M[minIdx][j] = temp;
            }
        }
    }
}

template <typename T>
void insertionSortMainDiagonals(T* M, size_t n) {
    for (int d = 1; d < n; d++) {
        int* diagonal = new int[n - d];
        for (int i = 0; i < n - d; i++) {
            diagonal[i] = M[i][i + d];
        }
        
        for (int i = 1; i < n - d; i++) {
            int key = diagonal[i];
            int j = i - 1;
            while (j >= 0 && diagonal[j] < key) {
                diagonal[j + 1] = diagonal[j];
                j--;
            }
            diagonal[j + 1] = key;
        }
        
        for (int i = 0; i < n - d; i++) {
            M[i][i + d] = diagonal[i];
        }
        delete[] diagonal;
    }
    
    for (int d = 1; d < n; d++) {
        int* diagonal = new int[n - d];
        for (int i = 0; i < n - d; i++) {
            diagonal[i] = M[i + d][i];
        }
        
        for (int i = 1; i < n - d; i++) {
            int key = diagonal[i];
            int j = i - 1;
            while (j >= 0 && diagonal[j] < key) {
                diagonal[j + 1] = diagonal[j];
                j--;
            }
            diagonal[j + 1] = key;
        }
        
        for (int i = 0; i < n - d; i++) {
            M[i + d][i] = diagonal[i];
        }
        delete[] diagonal;
    }
}

template <typename T>
void shellSortSecondaryDiagonals(T* M, size_t n) {
    for (int s = 0; s < n - 1; s++) {
        int len = s + 1;
        int* diagonal = new int[len];
        
        for (int i = 0; i <= s; i++) {
            diagonal[i] = M[i][s - i];
        }
        
        for (int gap = len / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < len; i++) {
                int temp = diagonal[i];
                int j;
                for (j = i; j >= gap && diagonal[j - gap] > temp; j -= gap) {
                    diagonal[j] = diagonal[j - gap];
                }
                diagonal[j] = temp;
            }
        }
        
        for (int i = 0; i <= s; i++) {
            M[i][s - i] = diagonal[i];
    }
        delete[] diagonal;
    }
    
    for (int s = n; s <= 2 * n - 2; s++) {
        int len = 2 * n - 1 - s;
        int* diagonal = new int[len];
        
        for (int i = 0; i < len; i++) {
            diagonal[i] = M[s - n + 1 + i][n - 1 - i];
        }
        
        for (int gap = len / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < len; i++) {
                int temp = diagonal[i];
            int j;
                for (j = i; j >= gap && diagonal[j - gap] > temp; j -= gap) {
                    diagonal[j] = diagonal[j - gap];
            }
                diagonal[j] = temp;
        }
        }
        
        for (int i = 0; i < len; i++) {
            M[s - n + 1 + i][n - 1 - i] = diagonal[i];
        }
        delete[] diagonal;
    }
}

int main() {
    srand(time(0));
    int n;
    
    cout << "Введите размер матрицы n: ";
    cin >> n;
    
    int** matrix = createMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 41 - 20;
        }
    }
    
    saveMatrix(matrix, n, "matrix.txt");
    
    int** matrix1 = copyMatrix(matrix, n);
    bubbleSort(matrix1, n);
    saveMatrix(matrix1, n, "matrix1.txt");
    
    int** matrix2 = copyMatrix(matrix, n);
    selectionSortColumns(matrix2, n);
    saveMatrix(matrix2, n, "matrix2.txt");
    
    int** matrix3 = copyMatrix(matrix, n);
    insertionSortMainDiagonals(matrix3, n);
    saveMatrix(matrix3, n, "matrix3.txt");
    
    int** matrix4 = copyMatrix(matrix, n);
    shellSortSecondaryDiagonals(matrix4, n);
    saveMatrix(matrix4, n, "matrix4.txt");
    
    deleteMatrix(matrix, n);
    deleteMatrix(matrix1, n);
    deleteMatrix(matrix2, n);
    deleteMatrix(matrix3, n);
    deleteMatrix(matrix4, n);
    
    return 0;
}