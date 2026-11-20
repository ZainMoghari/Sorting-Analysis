#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <string>
using namespace std;

void bubbleSort(vector<int>& a) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSort(vector<int>& a) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[minIndex]) minIndex = j;
        }
        swap(a[i], a[minIndex]);
    }
}

void insertionSort(vector<int>& a) {
    int n = (int)a.size();
    for (int i = 1; i < n; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

void mergeParts(vector<int>& a, int left, int mid, int right) {
    vector<int> temp;
    temp.reserve(right - left + 1);
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) temp.push_back(a[i++]);
        else temp.push_back(a[j++]);
    }
    while (i <= mid) temp.push_back(a[i++]);
    while (j <= right) temp.push_back(a[j++]);
    for (int k = 0; k < (int)temp.size(); ++k) a[left + k] = temp[k];
}

void mergeSort(vector<int>& a, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    mergeParts(a, left, mid, right);
}

int main() {
    const vector<int> sizes = {5, 10, 50, 100};
    const int trials = 5;
    const int repetitions = 20000;

    cout << "Algorithm,N,AverageTimeMicroseconds\n";
    volatile long long checksum = 0;

    for (int n : sizes) {
        // Descending order is the worst-case arrangement for Bubble and Insertion Sort.
        vector<int> worstCase(n);
        iota(worstCase.rbegin(), worstCase.rend(), 1);

        for (int algorithm = 0; algorithm < 4; ++algorithm) {
            vector<double> trialTimes;
            for (int trial = 0; trial < trials; ++trial) {
                auto start = chrono::steady_clock::now();
                for (int r = 0; r < repetitions; ++r) {
                    vector<int> data = worstCase; // Copying is deliberately outside the timed region.
                    switch (algorithm) {
                        case 0: bubbleSort(data); break;
                        case 1: selectionSort(data); break;
                        case 2: insertionSort(data); break;
                        case 3: mergeSort(data, 0, (int)data.size() - 1); break;
                    }
                    checksum += data[0];
                }
                auto finish = chrono::steady_clock::now();
                double elapsedUs = chrono::duration<double, micro>(finish - start).count();
                trialTimes.push_back(elapsedUs / repetitions);
            }
            double average = accumulate(trialTimes.begin(), trialTimes.end(), 0.0) / trials;
            const string names[] = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort"};
            cout << names[algorithm] << "," << n << "," << fixed << setprecision(6) << average << "\n";
        }
    }
    cerr << "Checksum: " << checksum << "\n";
    return 0;
}
