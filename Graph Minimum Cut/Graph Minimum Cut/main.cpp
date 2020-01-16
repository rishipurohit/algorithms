//
//  main.cpp
//  Graph Minimum Cut
//  Uses Karger's algorithm for minimum cut of a graph
//
//  Created by Rishi Purohit on 3/31/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
using namespace std;

int vertexCount = 200;

void merge(vector<vector<int>> &adjList, int v1, int v2) {
    cout << "merging " << v1 << " and " << v2 << endl;
    adjList.at(v1).insert(adjList.at(v1).end(), adjList.at(v2).begin(), adjList.at(v2).end());
    adjList.at(v2).clear();
    for (int i = 1; i < 201; ++i) {
        for (int j = 0; j < adjList.at(i).size(); ++j) {
            if (adjList.at(i).at(j) == v2) { // finish merging
                adjList.at(i).at(j) = v1;
            }
            if (adjList.at(i).at(j) == i) { // remove self-loops
                adjList.at(i).erase(adjList.at(i).begin() + j);
                j -= 1;
            }
        }
    }
    vertexCount--;
}

int mincut(vector<vector<int>> adjList) {
    while (vertexCount > 2) {
        int edgeCount = 0;
        for (vector<int> adj : adjList) {
            edgeCount += adj.size();
        }
        srand(time(NULL));
        cout << vertexCount << endl;
        int num = (rand() % edgeCount); // 0 to number of edges
        for (int v = 1; v < adjList.size(); ++v) {
            //int size = adjList.at(v).size()
            if ((num - (int) adjList.at(v).size()) < 0) {
                // num is the index of the vertex to merge with
                merge(adjList, v, adjList.at(v).at(num));
                break;
            } else {
                num -= (int) adjList.at(v).size();
            }
        }
    }
    for (int i = 1; i < adjList.size(); ++i) {
        if (!adjList.at(i).empty()) {
            return (int) adjList.at(i).size();
        }
    }
    return -1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream adjacencies;
    adjacencies.open("/Users/Rishi/Documents/Algorithms/kargerMinCut.txt");
    if (!adjacencies) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    vector<vector<int>> adjList;
    adjList.push_back(vector<int>()); // Empty vector to act as buffer so vertex numbers and indices are equivalent
    for (int l = 0; l < 200; ++l) {
        string line;
        getline(adjacencies, line);
        istringstream iss(line);
        int index = 0, vertex = -1;
        do {
            string endpoint;
            iss >> endpoint;
            if (endpoint.empty()) continue;
            if (index == 0) {
                vertex = stoi(endpoint);
                adjList.push_back(vector<int>());
            } else {
                adjList.at(vertex).push_back(stoi(endpoint));
            }
            ++index;
        } while (iss);
    }
    int ans = mincut(adjList);
    cout << "ans is " << ans << endl; // RUN OVER AND OVER
    return 0;
}
