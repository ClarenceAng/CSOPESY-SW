#include <atomic>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

// running flag if the program is running or not
std::atomic<bool> running{true};

// worker function to print output of threads
void worker(int id) {
    while (running.load(std::memory_order_relaxed)) {
        std::cout << "This is a hello world in a thread # " << id << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main(int argc, char* argv[]) {
    // just parsing command line output and if none specified spawn 20
    int n = (argc > 1) ? std::atoi(argv[1]) : 20;
    if (n <= 0){
        n = 20;
    } 

    // spawn N threads, execute, then detach them
    for (int i = 0; i < n; ++i) {
        std::thread(worker, i).detach();
    }

    //run forever until stop/ctrl+c
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}