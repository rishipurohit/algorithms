//
//  main.cpp
//  Knapsack Problem
//
//  Created by Rishi Purohit on 4/28/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <boost/unordered_map.hpp>

using namespace std;

int knapsack(vector<pair<int, int>> items, int maxWeight, int minWeight) {
    vector<vector<int>> dp(items.size(), vector<int> (maxWeight - minWeight + 1, 0));
    for (int i = 1; i < items.size(); ++i) {
        pair<int, int> item = items.at(i);
        for (int w = 0; w <= maxWeight - minWeight; ++w) {
            if (item.second <= w + minWeight) {
                int sp = item.second > w ? 0 : (w - item.second);
                dp.at(i).at(w) = max(dp.at(i - 1).at(w), dp.at(i - 1).at(sp) + item.first);
            } else {
                dp.at(i).at(w) = dp.at(i - 1).at(w);
            }
        }
    }
    return dp.at(items.size() - 1).at(maxWeight - minWeight);
}

// vector<vector<int>> dpr;
boost::unordered_map<pair<int, int>, int> hm;
vector<pair<int, int>> items;

int query(int i, int j) {
    boost::unordered_map<pair<int, int>, int>::const_iterator ref = hm.find(make_pair(i, j));
    if (ref != hm.end()) return ref->second;
    return -1;
}

void setVal(int i, int j, int val) {
    hm.insert(make_pair(make_pair(i, j), val));
}

int knapsackRecursive(int prefix, int maxWeight) {
    if (prefix == 0 || maxWeight == 0) return 0;
    // if (dpr.at(prefix).at(maxWeight) != -1) return dpr.at(prefix).at(maxWeight);
    int q = query(prefix, maxWeight);
    if (q != -1) return q;
    int excluded;
    if ((excluded = query(prefix - 1, maxWeight)) == -1) {
        excluded = knapsackRecursive(prefix - 1, maxWeight);
        setVal(prefix - 1, maxWeight, excluded);
    }
    pair<int, int> item = items.at(prefix);
    int included = 0;
    if (item.second <= maxWeight) {
        if ((included = query(prefix - 1, maxWeight - item.second)) == -1) {
            included = knapsackRecursive(prefix - 1, maxWeight - item.second);
            // dpr.at(prefix - 1).at(maxWeight - item.second)
            setVal(prefix - 1, maxWeight - item.second, included);
        }
        included += item.first;
    }
    // dpr.at(prefix).at(maxWeight) = max(included, excluded);
    setVal(prefix, maxWeight, max(included, excluded));
    return max(included, excluded);
}

int main(int argc, const char * argv[]) {
    ifstream knapsackFile;
    knapsackFile.open("/Users/Rishi/Documents/Algorithms/knapsack1.txt");
    if (!knapsackFile) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    int maxWeight, nItems;
    knapsackFile >> maxWeight >> nItems;
    int minWeight = INT_MAX;
    items.push_back(pair<int, int>());
    for (int i = 0; i < nItems; ++i) {
        int val, weight;
        knapsackFile >> val >> weight;
        if (weight < minWeight) {
            minWeight = weight;
        }
        items.push_back(make_pair(val, weight));
    }
    int ans = knapsackRecursive(nItems, maxWeight);
    cout << "ans is " << ans << endl;
    return 0;
}
