#include <iostream>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>

using namespace std;

long long a[1000][1000][100];

int main() {
    long long tmp = 0;
    int max_i = 1000;
    int max_j = 1000;
    int max_k = 100;
    int iter_k = 50; // for 1/2 max k
    std::chrono::high_resolution_clock::time_point start_point, end_point;
    std::chrono::duration<double, std::milli> delta;

    start_point = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < max_i; ++i) {
        for (int j = 0; j < max_j; ++j) {
            for (int k = 0; k < iter_k; ++k) {
                a[i][j][k] = tmp;
                tmp++;
            }
        }
    }
    end_point = std::chrono::high_resolution_clock::now();
    delta = end_point - start_point;
    std::cout << "naive approach: " << delta.count() << " ms" << std::endl;
    std::cout << "1st element, last element = " << a[0][0][0] << ", " << a[0][1][2] << std::endl;
}