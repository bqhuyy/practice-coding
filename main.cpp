#include <iostream>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
#include <thread>
#include <chrono>

void func() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << std::this_thread::get_id() << " " << std::endl;
}

int main() {
    /* STRING ADDRESS */
    // std::string a = "hello";
    // std::string c = "a";
    // std::string b = a;
    // b = c;
    // b += "x";
    // std::cout << &a << " " << &b << " " << &c << std::endl;
    // std::cout << a << " " << b << std::endl;

    /* THREAD */
    // std::thread t1(func);
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // std::thread t2(func);

    // while (1) {
    //     if (t1.joinable()) {
    //         t1.join();
    //     }
    //     if (t2.joinable()) {
    //         t2.join();
    //     }
    // }

    /* CHRONO */
    std::int64_t current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << current_time << std::endl;
    std::int64_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::minutes(1)).count();
    std::cout << duration << std::endl;

    return 0;
}