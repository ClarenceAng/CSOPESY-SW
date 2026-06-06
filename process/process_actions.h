#pragma once
#include "process.h"

// Q2: Which attributes and functions are needed for tracking
class ProcessActions : public Process {
    public:
        void printCurrentLine(); // print the current line
        void updateStatus(); // update status of the process
        void executeNext(); // allows execution of the next process
};



