//
//  main.cpp
//  Two-Sum Problem
//
//  Created by Rishi Purohit on 4/21/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>

using namespace std;

vector<long> vals;

int sumExists(long sum) {
    unordered_set<long> hashset;
    for (long elem : vals) {
        if (hashset.find(sum - elem) != hashset.end()) {
            return 1;
        } else {
            hashset.insert(elem);
        }
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    ifstream listFile;
    listFile.open("/Users/Rishi/Documents/Algorithms/algo1-programming_prob-2sum.txt");
    if (!listFile) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    for (int i = 0; i < 1000000; ++i) {
        long val = 0;
        listFile >> val;
        vals.push_back(val);
    }
    /*string line;
    while (getline(listFile, line)) {
        cout << stol(line) << endl;
    }*/
    cout << "size is " << vals.size() << endl;
    int total = 0;
    for (int i = -10000; i <= 10000; ++i) {
        total += sumExists(i);
        if (i % 10 == 0) cout << ".";
    }
    //total = sumExists(2930);
    cout << "total is: " << total << endl;
    return 0;
}
