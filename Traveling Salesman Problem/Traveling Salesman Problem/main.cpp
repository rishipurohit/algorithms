//
//  main.cpp
//  Traveling Salesman Problem
//
//  Created by Rishi Purohit on 6/9/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/unordered_map.hpp>

using namespace std;
boost::unordered_map<pair<int, int>, double> distCache;

vector<vector<int>> generateSets(int n, int cardinality) {
    n--;
    vector<bool> flags(n);
    int r = cardinality - 1;
    fill(flags.end() - r, flags.end(), true);
    int sn = 0;
    vector<vector<int>> ret;
    do {
        ret.push_back(vector<int>());
        ret.at(sn).push_back(1);
        for (int i = 0; i < n; ++i) {
            if (flags[i]) {
                ret.at(sn).push_back(i + 2);
            }
        }
        sn++;
    } while (next_permutation(flags.begin(), flags.end()));
    return ret;
}

double dist(vector<pair<double, double>> cities, int x, int y) {
    if (distCache.find(make_pair(x, y)) != distCache.end()) {
        return distCache.at(make_pair(x, y));
    }
    double ret = sqrt(pow((cities.at(x).first - cities.at(y).first), 2) +
                     pow((cities.at(x).second - cities.at(y).second), 2));
    distCache.insert(make_pair(make_pair(x, y), ret));
    return ret;
}

double TravelingSalesman(vector<pair<double, double>> cities) {
    boost::unordered_map<pair<vector<int>, int>, double> pdp; //dp[S, i] represents the cost of a path from vertex 1 to vertex i using all the vertices in S
    boost::unordered_map<pair<vector<int>, int>, double> cdp;
    for (int c = 2; c < cities.size(); ++c) { // iterate over possible cardinalities of sets
        printf("c is %d\n", c);
        vector<vector<int>> sets = generateSets(cities.size() - 1, c);
        printf("generated\n");
        int s = 0;
        for (vector<int> set : sets) {
            if (s % 10000 == 0) {
                printf("s is %d\n", s);
            }
            for (int l : set) { // iterating over all possible destination vertices
                if (l == 1) continue;
                vector<int> ls = set;
                ls.erase(remove(ls.begin(), ls.end(), l), ls.end());
                double min = INT_MAX;
                for (int stl : ls) { // iterating over all possible second-to-last vertices
                    if (stl == l) continue;
                    double query = -1;
                    if (stl != 1) {
                        query = pdp.at(make_pair(ls, stl));
                    } else if (ls.size() == 1 && ls.at(0) == 1) {
                        query = 0;
                    } else {
                        query = INT_MAX;
                    }
                    double cost = query + dist(cities, stl, l);
                    if (cost < min) {
                        min = cost;
                    }
                }
                cdp.insert(make_pair(make_pair(set, l), min));
            }
            s++;
        }
        pdp.clear();
        pdp = cdp;
        cdp.clear();
    }
    vector<int> fs;
    for (int i = 1; i < cities.size(); ++i) {
        fs.push_back(i);
    }
    double min = INT_MAX;
    for (int i = 2; i < cities.size(); ++i) {
        double tour = pdp.at(make_pair(fs, i)) + dist(cities, 1, i);
        if (tour < min) {
            min = tour;
        }
    }
    return min;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream cityList;
    cityList.open("/Users/Rishi/Documents/Algorithms/tsp.txt");
    if (!cityList) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    int nCities;
    cityList >> nCities;
    vector<pair<double, double>> cities;
    cities.push_back(pair<double, double>());
    for (int i = 0; i < nCities; ++i) {
        double x, y;
        cityList >> x >> y;
        cities.push_back(make_pair(x, y));
    }
    printf("ans is %f\n", TravelingSalesman(cities));
    return 0;
}
