//
//  main.cpp
//  Quicksort
//
//  Created by Rishi Purohit on 3/3/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int findMedian(vector<int> &arr, int v1, int v2, int v3) { // v1, v2, v3, and return value are all indices
    int x = arr[v1] - arr[v2];
    int y = arr[v2] - arr[v3];
    int z = arr[v1] - arr[v3];
    if(x * y > 0) return v2;
    if(x * z > 0) return v3;
    return v1;
}

void swap(vector<int> &arr, int i1, int i2) {
    if (i1 == i2) return;
    int t = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = t;
}

int quicksort(vector<int> &arr, int f, int l) {
    if ((l - f) < 1) return 0;
    int c = (l - f);
    int mi = findMedian(arr, f, (l + f) / 2, l);
    int pivot = arr[mi];
    swap(arr, mi, f);
    int partition = f; // Points to last value smaller than pivot
    if (arr[f + 1] < pivot) partition++;
    for (int i = f + 2; i <= l; ++i) {
        if (arr[i] > pivot) continue;
        swap(arr, i, partition + 1);
        partition++;
    }
    swap(arr, f, partition);
    c += quicksort(arr, f, partition - 1);
    c += quicksort(arr, partition + 1, l);
    return c;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream listFile;
    listFile.open("/Users/Rishi/Documents/Algorithms/QuickSort.txt");
    if (!listFile) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    vector<int> arr;
    for (int i = 0; i < 10000; ++i) {
        int num = 0;
        listFile >> num;
        arr.push_back(num);
    }
    int compNum = quicksort(arr, 0, 9999);
    for (int i = 0; i < 10000; ++i) {
        cout << arr[i] << endl;
    }
    cout << "ans: " << compNum << endl;
    return 0;
}
