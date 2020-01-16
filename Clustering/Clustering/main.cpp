//
//  main.cpp
//  Clustering
//
//  Created by Rishi Purohit on 4/25/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct edge {
    int node1;
    int node2;
    int weight;
};

bool compare(const edge &a, const edge &b) {
    return a.weight < b.weight;
}

vector<int> parents;
vector<int> ranks;
vector<bitset<24>> nc;

int clusters;

int findParent(int v) {
    // If the parent of the current node is a self-loop (meaning parent is the root), return that
    // Otherwise, recursively iterate up the tree memoizing the ultimate parent along the way
    return (parents[parents[v]] == parents[v] ? parents[v] : (parents[v] = findParent(parents[v])));
}

bool unionNoCycles(edge e) {
    int px = findParent(e.node1), py = findParent(e.node2);
    if (px == py) return false;
    int rx = ranks[px], ry = ranks[py];
    if (rx > ry) {
        parents[py] = px;
    } else if (rx < ry) {
        parents[px] = py;
    } else {
        parents[py] = px;
        ranks[px]++;
    }
    return true;
}

vector<bitset<24>> permute(bitset<24> set, int p) {
    vector<bitset<24>> ans;
    if (p == 0) {
        ans.push_back(set);
    } else if (p == 1) {
        for (int i = 0; i < 24; ++i) {
            bitset<24> newset = set;
            ans.push_back(newset.flip(i));
        }
    } else {
        for (int i = 0; i < 24; ++i) {
            for (int j = i + 1; j < 24; ++j) {
                bitset<24> newset = set;
                ans.push_back(newset.flip(i).flip(j));
            }
        }
    }
    return ans;
}

vector<edge> findEdgesWithHD(int hd) {
    vector<edge> edges;
    unordered_multimap<bitset<24>, int> list;
    for (int i = 1; i < nc.size(); ++i) {
        bitset<24> node = nc.at(i);
        vector<bitset<24>> candidates = permute(node, hd);
        for (bitset<24> c : candidates) {
            if (list.find(c) != list.end()) {
                auto range = list.equal_range(c);
                for (auto it = range.first; it != range.second; ++it) {
                    edges.push_back({i, it->second, hd});
                }
            }
        }
        list.insert({node, i});
    }
    return edges;
}

int cluster(vector<edge> edgeSet, int nodes) {
    parents.push_back(-1);
    ranks.push_back(-1);
    for (int i = 1; i < nodes + 1; ++i) {
        parents.push_back(i);
        ranks.push_back(0);
    }
    clusters = nodes;
    int ei = 0;
    int ans = INT_MAX;
    while (clusters > 3) {
        while (!unionNoCycles(edgeSet.at(ei))) ei++;
        ans = edgeSet.at(ei).weight;
        clusters--;
    }
    return ans;
}

int clusterHD(int nodes) {
    parents.push_back(-1);
    ranks.push_back(-1);
    for (int i = 1; i < nodes + 1; ++i) {
        parents.push_back(i);
        ranks.push_back(0);
    }
    clusters = nodes;
    int ans = INT_MAX;
    vector<edge> edgeSet;
    vector<edge> d0 = findEdgesWithHD(0);
    vector<edge> d1 = findEdgesWithHD(1);
    vector<edge> d2 = findEdgesWithHD(2);
    edgeSet.insert(edgeSet.end(), d0.begin(), d0.end());
    edgeSet.insert(edgeSet.end(), d1.begin(), d1.end());
    edgeSet.insert(edgeSet.end(), d2.begin(), d2.end());
    int dist = -1;
    int index = 0;
    bool flag = false;
    while (!flag) {
        while (index < edgeSet.size() && !unionNoCycles(edgeSet.at(index))) {
            index++;
        }
        if (index == edgeSet.size()) {
            flag = true;
        }
        clusters--;
    }
    return clusters;
}

int main(int argc, const char * argv[]) {
    ifstream edgeFile;
    edgeFile.open("/Users/Rishi/Documents/Algorithms/clustering_big.txt");
    if (!edgeFile) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    int nodes, bits;
    edgeFile >> nodes >> bits;
    vector<edge> edgeSet;
    //int edges = 124750; // Graph is as dense as possible (given in problem)
    nc.push_back(bitset<24>());
    for (int i = 0; i < nodes; ++i) {
        bitset<24> line;
        for (int b = 0; b < bits; ++b) {
            int v;
            edgeFile >> v;
            line.set(b, v);
        }
        nc.push_back(line);
    }
    sort(edgeSet.begin(), edgeSet.end(), compare);
    int ans = clusterHD(nodes);
    cout << "ans is " << ans << endl;
    return 0;
}
