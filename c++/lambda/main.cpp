#include <iostream>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv) {
    cout << "Total args: " << argc << endl;
    
    int a = 10;
    int b = 50;

    auto func = [x = a, y = b]{return x < y;};
    bool res = func();
    std::cout << a << " " << b << std::endl;
    std::cout << res << std::endl;

    return 0;
}