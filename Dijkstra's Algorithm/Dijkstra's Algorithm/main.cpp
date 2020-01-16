//
//  main.cpp
//  Dijkstra's Algorithm
//
//  Created by Rishi Purohit on 4/14/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>

using namespace std;

vector<vector<pair<int, int>>> adjList;
pair<int, int> NULLPAIR(INT_MAX, INT_MAX);

class DijkstraHeap {
    public:
    vector<pair<int, int>> data;
    
    DijkstraHeap() {};
    
    DijkstraHeap(vector<pair<int, int>> array) {
        for (pair<int, int> element : array) {
            push(element);
        }
    }
    
    pair<int, int> pop() {
        pair<int, int> val = data.at(0);
        pair<int, int> newest = data.at(data.size() - 1);
        data.erase(data.begin() + (data.size() - 1));
        if (data.size() != 0) {
            data.at(0) = newest;
            bubbleDown(0);
        }
        return val;
    }
    
    void swap(int a, int b) {
        pair<int, int> t = data.at(a);
        data.at(a) = data.at(b);
        data.at(b) = t;
    }
    
    void remove(int vertex) {
        int i;
        for (i = 0; i < data.size(); ++i) {
            if (data.at(i).second == vertex) break;
        }
        swap(i, data.size() - 1);
        data.erase(data.begin() + (data.size() - 1));
        if (i != data.size()) {
            if (!bubbleUp(i)) bubbleDown(i);
        }
    }
    
    bool bubbleDown(int index) {
        pair<int, int> r = rightChild(index), l = leftChild(index);
        int min = INT_MAX;
        if (r.first > l.first) {
            min = 2 * index + 1;
        } else {
            min = 2 * index + 2;
        }
        if (min < data.size() && data.at(min) < data.at(index)) {
            swap(min, index);
            bubbleDown(min);
            return true;
        }
        return false;
    }
    
    bool bubbleUp(int index) {
        pair<int, int> p = parent(index);
        if (p != NULLPAIR && p.first > data.at(index).first) {
            swap((index - 1) / 2, index);
            bubbleUp((index - 1) / 2);
            return true;
        }
        return false;
    }
    
    pair<int, int> rightChild(int index) {
        int ridx = 2 * index + 2;
        if (data.size() > ridx) {
            return data.at(ridx);
        }
        return NULLPAIR;
    }
    
    pair<int, int> leftChild(int index) {
        int lidx = 2 * index + 1;
        if (data.size() > lidx) {
            return data.at(lidx);
        }
        return NULLPAIR;
    }
    
    pair<int, int> parent(int index) {
        int pidx = (index - 1) / 2;
        if (index != 0) {
            return data.at(pidx);
        }
        return NULLPAIR;
    }
    
    void push(pair<int, int> element) {
        data.push_back(element);
        bubbleUp(data.size() - 1);
    }
    
    bool empty() {
        return data.empty();
    }
};

void Dijkstra(int source) {
    DijkstraHeap heap;
    int key[201], dist[201];
    for (int i = 0; i < 201; ++i) {
        key[i] = INT_MAX;
    }
    unordered_set<int> X;
    key[source] = 0;
    for (int i = 1; i < 201; ++i) {
        heap.push(make_pair(key[i], i));
    }
    while (!heap.empty()) {
        pair<int, int> sv = heap.pop();
        //cout << "popped is " << sv.second << endl;
        X.insert(sv.second);
        dist[sv.second] = sv.first;
        for (pair<int, int> c : adjList.at(sv.second)) {
            //cout << "child is " << c.first << endl;
            if (X.find(c.first) != X.end()) {
                continue;
            }
            heap.remove(c.first);
            key[c.first] = min(key[c.first], sv.first + c.second);
            heap.push(make_pair(key[c.first], c.first));
        }
    }
    for (int i = 1; i < 201; ++i) {
        cout << "dist is for " << i << " and is " << dist[i] << endl;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream adjacencies;
    adjacencies.open("/Users/Rishi/Documents/Algorithms/dijkstraData.txt");
    if (!adjacencies) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    adjList.push_back(vector<pair<int, int>>()); // Empty vector to act as buffer so vertex numbers and indices are equivalent
    string line;
    char lc[1000];
    while (getline(adjacencies, line)) {
        istringstream iss(line);
        adjList.push_back(vector<pair<int, int>>());
        string vpair;
        iss >> vpair;
        while (iss >> vpair) {
            int comma = vpair.find(",");
            if (comma != string::npos) {
                int vertex = stoi(vpair.substr(0, comma));
                int weight = stoi(vpair.substr(comma + 1));
                adjList.at(adjList.size() - 1).push_back(make_pair(vertex, weight));
            }
            //cout << vpair << endl;
        }
    }
    Dijkstra(1);
    return 0;
}
