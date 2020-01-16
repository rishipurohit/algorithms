//
//  main.cpp
//  Strongly Connected Components
//
//  Created by Rishi Purohit on 4/4/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define LEN 875715

vector<int> ft(LEN);
vector<bool> visited(LEN);
vector<int> leaders(LEN);
vector<vector<int>> adjList;
vector<int> sccSizes;
int t = 0;
int s = -1;
int sccCount = 0;

void dfs(int v, bool fp) {
    visited.at(v) = true;
    leaders.at(v) = s;
    sccCount++;
    for (int c : adjList.at(v)) {
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
                sccSizes.push_back(sccCount);
                sccCount = 0;
            }
        }
    }
}

void reverse() {
    vector<vector<int>> newList;
    for (int i = 0; i < LEN; ++i) {
        newList.push_back(vector<int>());
    }
    for (int v = 1; v < LEN; ++v) {
        for (int c = 0; c < adjList.at(v).size(); ++c) {
            newList.at(adjList.at(v).at(c)).push_back(v);
        }
    }
    adjList = newList;
    vector<vector<int>>().swap(newList);
}

int main(int argc, const char * argv[]) {
    ifstream adjacencies;
    adjacencies.open("/Users/Rishi/Documents/Algorithms/SCC.txt");
    if (!adjacencies) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    adjList.push_back(vector<int>()); // Empty vector to act as buffer so vertex numbers and indices are equivalent
    int v1, v2;
    while (adjacencies >> v1 >> v2) {
        while (adjList.size() <= v1) {
            adjList.push_back(vector<int>());
        }
        adjList.at(v1).push_back(v2);
    }
    cout << "start" << endl;
    dfsloop(true);
    cout << "done" << endl;
    reverse();
    std::fill(visited.begin(), visited.end(), false);
    std::fill(leaders.begin(), leaders.end(), 0);
    t = 0;
    s = -1;
    sccCount = 0;
    dfsloop(false);
    std::sort(sccSizes.begin(), sccSizes.end(), std::greater<>());
    cout << sccSizes[0] << endl;
    cout << sccSizes[1] << endl;
    cout << sccSizes[2] << endl;
    cout << sccSizes[3] << endl;
    cout << sccSizes[4] << endl;
    return 0;
}
