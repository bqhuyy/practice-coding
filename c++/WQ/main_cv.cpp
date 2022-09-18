/*
    README: GENERAL DATA TYPE IN C++
        - in most case, ptr indexing will faster than array indexing
        - command to run multiple times: for i in {1..10}; do echo $i && ./main; done
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>

#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/opencv.hpp"

using namespace std;

cv::Mat a = cv::Mat::zeros(1000,1000,CV_32FC3);
cv::Mat b = cv::Mat::zeros(1000,1000,CV_32FC3);

int main() {
    int max_i = 1000;
    int max_j = 1000;
    int max_k = 3;
    std::chrono::high_resolution_clock::time_point start_point, end_point;
    std::chrono::duration<double, std::milli> delta_1, delta_2;

    start_point = std::chrono::high_resolution_clock::now();
    float tmp = 0;
    
    for (int i = 0; i < max_i; ++i) {
        for (int j = 0; j < max_j; ++j) {
            for (int k = 0; k < max_k; ++k) {
                a.at<cv::Vec3f>(i, j)[k] = tmp;
                tmp++;
            }
        }
    }
    end_point = std::chrono::high_resolution_clock::now();
    delta_1 = end_point - start_point;
    std::cout << "naive approach: " << delta_1.count() << " ms" << std::endl;
    std::cout << "1st element, last element = " << a.at<cv::Vec3f>(0, 0)[0] << ", " << a.at<cv::Vec3f>(0, 1)[2] << std::endl;

    start_point = std::chrono::high_resolution_clock::now();
    float tmp_1 = 0;
    float* b_ptr = b.ptr<float>();
    for (int i = 0; i < max_i; ++i) {
        for (int j = 0; j < max_j; ++j) {
            for (int k = 0; k < max_k; ++k) {
                *b_ptr = tmp_1;
                b_ptr++;
                tmp_1++;
            }
        }
    }
    end_point = std::chrono::high_resolution_clock::now();
    delta_2 = end_point - start_point;
    std::cout << "my approach: " << delta_2.count() << " ms" << std::endl;
    std::cout << "1st element, last element = " << b.at<cv::Vec3f>(0, 0)[0] << ", " << b.at<cv::Vec3f>(0, 1)[2] << std::endl;
}