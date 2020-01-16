//
//  main.cpp
//  Floyd-Warshall Algorithm
//
//  Created by Rishi Purohit on 5/18/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

long FloydWarshall(vector<vector<pair<int, int>>> graph, int v) {
    vector<vector<vector<long>>> dp(v + 1, vector<vector<long>>(v + 1, vector<long>(v + 1, LONG_MAX)));
    for (int d = 1; d < v + 1; ++d) {
        dp[0][d][d] = 0;
    }
    for (int n = 1; n < v + 1; ++n) {
        for (int c = 0; c < graph.at(n).size(); ++c) {
            dp[0][n][graph.at(n).at(c).first] = graph.at(n).at(c).second;
        }
    }
    cout << "fi done" << endl;
    long m = LONG_MAX;
    cout << "m is " << m << endl;
    for (int k = 1; k < v + 1; ++k) {
        m = LONG_MAX;
        for (int i = 1; i < v + 1; i++) {
            for (int j = 1; j < v + 1; j++) {
                if (dp[k - 1][i][k] != LONG_MAX && dp[k - 1][k][j] != LONG_MAX) {
                    dp[k][i][j] = min(dp[k - 1][i][j], dp[k - 1][i][k] + dp[k - 1][k][j]);
                } else {
                    dp[k][i][j] = dp[k - 1][i][j];
                }
                m = min(m, dp[k][i][j]);
            }
        }
        cout << "m is " << m << endl;
    }
    for (int d = 1; d < v + 1; ++d) {
        if (dp[v][d][d] < 0) {
            return -1;
        }
    }
    return m;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream graphFile;
    graphFile.open("/Users/Rishi/Documents/Algorithms/g1.txt");
    if (!graphFile) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    vector<vector<pair<int, int>>> adjacencies;
    int v, e;
    graphFile >> v >> e;
    for (int i = 0; i < e; ++i) {
        int v1, v2, w;
        graphFile >> v1 >> v2 >> w;
        while (adjacencies.size() <= v1) adjacencies.push_back(vector<pair<int, int>>());
        adjacencies.at(v1).push_back(make_pair(v2, w));
    }
    long sd = FloydWarshall(adjacencies, v);
    cout << "ans is " << sd << endl;
    return 0;
}
