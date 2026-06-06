#pragma once
#include <unordered_map>
#include "process.h"

// Q3: how processes are stored and traversed
class ProcessList{
    using String = std::string;

    public:
        std::unordered_map<std::string, Process> process_list;

        void append(const Process& process); // Q4: Storing a process
        void getProcess(const String name); // Q4: Retrieving a process
        void traverse_list(); // Q3: Traversing map in O(n) time
};