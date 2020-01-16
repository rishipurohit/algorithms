//
//  main.cpp
//  Scheduling
//
//  Created by Rishi Purohit on 4/23/19.
//  Copyright © 2019 Rishi Purohit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct task {
    int weight;
    int length;
};

bool compare(task &a, task &b) {
    float cmpa = ((float) a.weight) / a.length;
    float cmpb = ((float) b.weight) / b.length;
    if (cmpa > cmpb) {
        return true;
    } else if (cmpa == cmpb) {
        return a.weight < b.weight;
    } else {
        return false;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream stream;
    stream.open("/Users/Rishi/Documents/Algorithms/jobs.txt");
    if (!stream) {
        cerr << "Fail opening file" << endl;
        exit(1);
    }
    int n;
    stream >> n;
    vector<task> tasks;
    for (int i = 0; i < n; ++i) {
        int length, weight;
        stream >> weight >> length;
        tasks.push_back({(int) weight, (int) length});
    }
    std::sort(tasks.begin(), tasks.end(), compare);
    long long ftTotal = 0;
    long long ans = 0;
    for (task t : tasks) {
        ftTotal += t.length;
        ans += t.weight * ftTotal;
    }
    cout << fixed << "ans is " << ans << endl;
    return 0;
}
