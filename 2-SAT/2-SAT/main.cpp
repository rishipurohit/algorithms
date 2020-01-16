//
//  main.cpp
//  2-SAT
//
//  Created by Rishi Purohit on 6/22/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define LEN 2000000

vector<int> sccMap;
vector<int> ft(LEN);
vector<bool> visited(LEN);
vector<int> leaders(LEN);
vector<vector<int>> adj;
int t = -1;
int s = -1;
int cSCC = 0;

int vToIndex(int v, bool neg) {
    if (!neg) {
        return (v - 1) * 2;
    }
    return (v - 1) * 2 + 1;
}

void dfs(int v, bool fp) {
    visited.at(v) = true;
    leaders.at(v) = s;
    sccMap.at(v) = cSCC;
    for (int c : adj.at(v)) {
        if (!visited.at(c)) {
            dfs(c, fp);
        }
    }
    t++;
    if (fp) ft.at(t) = v;
}

void dfsloop(bool fp) {
    for (int i = LEN - 1; i > 0; --i) {
        if (fp) {
            if (!visited.at(i)) {
                s = i;
                dfs(i, fp);
            }
        } else {
            if (!visited.at(ft.at(i))) {
                s = ft.at(i);
                dfs(ft.at(i), fp);
                cSCC++;
            }
        }
    }
}

void reverse() {
    vector<vector<int>> newList;
    for (int i = 0; i < LEN; ++i) {
        newList.push_back(vector<int>());
    }
    for (int v = 0; v < LEN; ++v) {
        for (int c = 0; c < adj.at(v).size(); ++c) {
            newList.at(adj.at(v).at(c)).push_back(v);
        }
    }
    adj = newList;
    vector<vector<int>>().swap(newList);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream clauseFile;
    clauseFile.open("/Users/Rishi/Documents/Algorithms/2sat6.txt");
    if (!clauseFile) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    int len;
    clauseFile >> len;
    for (int i = 0; i < len * 2; ++i) {
        adj.push_back(vector<int>());
    }
    for (int i = 0; i < len; ++i) {
        int var1, var2;
        bool neg1 = false, neg2 = false;
        clauseFile >> var1 >> var2;
        if (var1 < 0) {
            neg1 = true;
            var1 = abs(var1);
        }
        if (var2 < 0) {
            neg2 = true;
            var2 = abs(var2);
        }
        adj.at(vToIndex(var1, !neg1)).push_back(vToIndex(var2, neg2));
        adj.at(vToIndex(var2, !neg2)).push_back(vToIndex(var1, neg1));
    }
    for (int i = 0; i < len * 2; ++i) {
        sccMap.push_back(-1);
    }
    cout << "start" << endl;
    dfsloop(true);
    cout << "done" << endl;
    reverse();
    std::fill(visited.begin(), visited.end(), false);
    std::fill(leaders.begin(), leaders.end(), 0);
    t = 0;
    s = -1;
    dfsloop(false);
    bool soln = true;
    for (int i = 0; i < len * 2; i += 2) {
        if (sccMap.at(i) == sccMap.at(i + 1)) {
            soln = false;
            break;
        }
    }
    cout << "soln is " << soln << endl;
    return 0;
}
