//
//  main.cpp
//  Inversions
//
//  Created by Rishi Purohit on 2/17/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct ArrayVal {
    vector<long> arr;
    long val;
};

void mergeCountSplit(vector<long> fh, vector<long> sh, long lf, long ls, struct ArrayVal *fill) {
    long i = 0, j = 0;
    vector<long> d(lf + ls);
    long inv = 0;
    for (long k = 0; k < lf + ls; ++k) {
        if (i == lf) {
            d[k] = sh[j];
            j++;
        } else if (j == ls || fh[i] <= sh[j]) {
            d[k] = fh[i];
            i++;
        } else {
            d[k] = sh[j];
            j++;
            inv += (lf - i);
        }
    }
    cout << inv << endl;
    fill->arr = d;
    fill->val = inv;
}

struct ArrayVal sortCount(vector<long> array, long n) {
    if (n == 1) {
        vector<long> element;
        element.push_back(array[0]);
        ArrayVal blank = {element, 0};
        return blank;
    } else {
        long firstLength = (n / 2);
        vector<long> fh(array.begin(), array.begin() + firstLength);
        vector<long> sh(array.begin() + firstLength, array.end());
        ArrayVal b = sortCount(fh, firstLength);
        ArrayVal c = sortCount(sh, n - firstLength);
        ArrayVal d;
        mergeCountSplit(b.arr, c.arr, firstLength, n - firstLength, &d);
        ArrayVal ret = {d.arr, b.val + c.val + d.val};
        return ret;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream listFile;
    listFile.open("/Users/Rishi/Documents/Algorithms/IntegerArray.txt");
    if (!listFile) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    vector<long> numbers(100000);
    for (int i = 0; i < 100000; ++i) {
        listFile >> numbers[i];
    }
    ArrayVal sc = sortCount(numbers, 100000);
    cout << sc.val << endl;
    return 0;
}
