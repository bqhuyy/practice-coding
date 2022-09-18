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

void reserve(std::string const &path, int bytes) {
    vector<char> vec;
    vec.reserve(bytes);
    fstream f(path, ios::out);
    if (!f.is_open()) {
        return;
    }
    f.seekp(bytes);
    f << '\0';
    f.close();
}

int main(int argc, char** argv) {
    cout << "Total args: " << argc << endl;
    
    reserve("reserve.txt", 1000*1024);
    fs::path p("reserve.txt");
    cout << "file size = " << fs::file_size(p) << endl;

    return 0;
}