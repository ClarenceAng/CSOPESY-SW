#include <atomic>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

// running flag is the program is running or not
std::atomic<bool> running{true};

// worker function to print the thread
void worker(int id) {
    while (running.load(std::memory_order_relaxed)) {
        std::cout << "This is a hello world in a thread # " << id << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main(int argc, char* argv[]) {
    int n = (argc > 1) ? std::atoi(argv[1]) : 20;
    int seconds = (argc > 2) ? std::atoi(argv[2]) : 2;
    if (n <= 0){
        n = 20;
    } 

    // spawn N threads given the parameter in the CLI command func and detach them
    for (int i = 0; i < n; ++i) {
        std::thread(worker, i).detach();
    }

    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    // signal the detached threads to stop, then give them a bit to finish
    running.store(false, std::memory_order_relaxed);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    return 0;
}