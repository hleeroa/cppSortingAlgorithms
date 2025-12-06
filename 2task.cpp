#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

const int SIZE = 10000;

template <typename T>
void fillArray(T* M, size_t size) {
    for (int i = 0; i < size; i++) {
        M[i] = rand() % 10000 + 1;
    }
}

template <typename T>
void copyArray(T* source, T* dest, size_t size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

template <typename T>
void bubbleSort(T* M, size_t size) {
	for (size_t step = 1; step < size; ++step) {
		bool isSorted = true;
		for (size_t i = size - 1; i >= step; --i) {
			if (M[i] < M[i - 1]) {
				std::swap(M[i], M[i - 1]);
				isSorted = false;
			}
		}
		if (isSorted) break;
	}
}

template <typename T>
void insertionSort(T* M, size_t size) {
    for (int i = 1; i < size; i++) {
        int key = M[i];
        int j = i - 1;
        
        while (j >= 0 && M[j] > key) {
            M[j + 1] = M[j];
            j--;
        }
        M[j + 1] = key;
    }
}

template <typename T>
void selectionSort(T* M, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (M[j] < M[min_idx]) {
                min_idx = j;
            }
        }
        int temp = M[i];
        M[i] = M[min_idx];
        M[min_idx] = temp;
    }
}

template <typename T>
void shellSort(T* M, size_t size) {
    int gap = 1;
    while (gap < size / 3) {
        gap = gap * 3 + 1;
    }
    
    while (gap > 0) {
        for (int i = gap; i < size; i++) {
            int temp = M[i];
            int j;
            for (j = i; j >= gap && M[j - gap] > temp; j -= gap) {
                M[j] = M[j - gap];
            }
            M[j] = temp;
        }
        gap = (gap - 1) / 3;
    }
}

int main() {
    srand(time(NULL));
    
    int originalArray[SIZE];
    fillArray(originalArray, SIZE);
    
    int array1[SIZE], array2[SIZE], array3[SIZE], array4[SIZE];
    
    copyArray(originalArray, array1, SIZE);
    copyArray(originalArray, array2, SIZE);
    copyArray(originalArray, array3, SIZE);
    copyArray(originalArray, array4, SIZE);

    
    clock_t start, end;
    double time_taken;

    start = clock();
    bubbleSort(array1, SIZE);
    end = clock();
    cout << "Сортировка пузырьком: " << double(end - start) / CLOCKS_PER_SEC << " с\n";

    start = clock();
    insertionSort(array2, SIZE);
    end = clock();
    cout << "\nСортировка вставками: " << double(end - start) / CLOCKS_PER_SEC << " с\n";

    start = clock();
    selectionSort(array3, SIZE);
    end = clock();
    cout << "\nСортировка выбором: " << double(end - start) / CLOCKS_PER_SEC << " с\n";

    start = clock();
    shellSort(array4, SIZE);
    end = clock();
    cout << "\nСортировка Шелла: " << double(end - start) / CLOCKS_PER_SEC << " с\n";

    
    return 0;
}