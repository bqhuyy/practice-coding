#include <iostream>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <fstream>

using namespace std;

int countAnalogousArrays(vector<int> consecutiveDifference, int lowerBound, int upperBound) {
    // adjust upperbound
    int right = upperBound;
    int left = lowerBound;
    int min_val = lowerBound;
    int max_val = upperBound;
    
    int saved_min_val = lowerBound;
    int saved_max_val = upperBound;
    for (int i = 0; i < consecutiveDifference.size(); ++i) {
        min_val -= consecutiveDifference[i];
        if (min_val < saved_min_val) {
            saved_min_val = min_val;
        }
        max_val -= consecutiveDifference[i];
        if (max_val > saved_max_val) {
            saved_max_val = max_val;
        }
    }
    if (saved_min_val < left) {
        left = left+abs(left-saved_min_val);
    }
    if (saved_max_val > right) {
        right = right-abs(right-saved_max_val);
    }
    if (left > right) {
        return 0;
    } else {
        return right-left+1;
    }
}

int main() {
    ifstream f("input.txt");
    vector<int> a;
    int lowerBound;
    int upperBound;
    int n;

    f >> n;
    for (int i = 0; i < n; ++i) {
        int tmp;
        f >> tmp;
        a.push_back(tmp);
    }
    f >> lowerBound;
    f >> upperBound;
    std::cout << countAnalogousArrays(a, lowerBound, upperBound) << std::endl;
}