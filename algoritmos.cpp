#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

vector<int> generar_vector(int n) {
    vector<int> v(n);
    for (int &x : v) x = rand() % 100000;
    return v;
}
//parte del algoritmo mergesort
void merge(vector<int>& a, int i, int m, int d) {
    int n1 = m - i + 1, n2 = d - m;
    vector<int> L(n1), R(n2);
    for (int x = 0; x < n1; x++) L[x] = a[i + x];
    for (int y = 0; y < n2; y++) R[y] = a[m + 1 + y];
    int x = 0, y = 0, k = i;
    while (x < n1 && y < n2) {
        if (L[x] <= R[y]) a[k++] = L[x++];
        else a[k++] = R[y++];
    }
    while (x < n1) a[k++] = L[x++];
    while (y < n2) a[k++] = R[y++];
}

void mergeSort(vector<int>& a, int i, int d) {
    if (i < d) {
        int m = i + (d - i) / 2;
        mergeSort(a, i, m);
        mergeSort(a, m + 1, d);
        merge(a, i, m, d);
    }
}
//parte del algoritmo quicksort
int particion(vector<int>& a, int b, int h) {
    int piv = a[h];
    int i = b - 1;
    for (int j = b; j < h; j++) {
        if (a[j] < piv) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[h]);
    return i + 1;
}

void quickSort(vector<int>& a, int b, int h) {
    if (b < h) {
        int pi = particion(a, b, h);
        quickSort(a, b, pi - 1);
        quickSort(a, pi + 1, h);
    }
}

void insertionSort(vector<int>& a) {
    for (int i = 1; i < a.size(); i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void selectionSort(vector<int>& a) {
    for (int i = 0; i < a.size() - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < a.size(); j++)
            if (a[j] < a[min_idx])
                min_idx = j;
        swap(a[min_idx], a[i]);
    }
}

int main() {
    srand(time(0));
    const int N = 10000;
    vector<int> datos = generar_vector(N);

    vector<int> v1 = datos;
    auto t1 = high_resolution_clock::now();
    mergeSort(v1, 0, v1.size() - 1);
    auto t2 = high_resolution_clock::now();
    cout << "MergeSort: " << duration<double, milli>(t2 - t1).count() << " ms" << endl;

    vector<int> v2 = datos;
    t1 = high_resolution_clock::now();
    quickSort(v2, 0, v2.size() - 1);
    t2 = high_resolution_clock::now();
    cout << "QuickSort: " << duration<double, milli>(t2 - t1).count() << " ms" << endl;

    vector<int> v3 = datos;
    t1 = high_resolution_clock::now();
    insertionSort(v3);
    t2 = high_resolution_clock::now();
    cout << "InsertionSort: " << duration<double, milli>(t2 - t1).count() << " ms" << endl;

    vector<int> v4 = datos;
    t1 = high_resolution_clock::now();
    selectionSort(v4);
    t2 = high_resolution_clock::now();
    cout << "SelectionSort: " << duration<double, milli>(t2 - t1).count() << " ms" << endl;

    return 0;
}
