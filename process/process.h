#pragma once
#include <string>
#include <cstdint>

enum class Status { // possible statuses of a Process
    READY,
    RUNNING,
    FINISHED
};
// Q1: How is a process represented in your emulator?
class Process {
    using String = std::string; //to make code more readable

    private: 
        uint64_t pid; // process id
        String name; // name of process
        String date; // date of process
        String time; // time of process
        uint64_t core_number; // which core the process is utilizing
        uint64_t currentInstruction; // current instructions of the process
        uint64_t totalInstruction; // total instructions of the process
        Status status; // status of process as of call

    public:
        Process(int pid, String name); // constructor
        
};


