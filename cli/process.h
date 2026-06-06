#pragma once
#include <string>
#include <cstdint>

// Process class
class Process {
    using String = std::string; 

    private:
        uint64_t gpuID;
        String giID;
        String ciID;
        uint64_t pid; 
        String type;
        String name; 
        String gpuMemoryUsage;

    public:
        Process(uint64_t gpuID, String giID, String ciID, uint64_t pid,
                String type, String name, String gpuMemoryUsage)
            : gpuID(gpuID), giID(giID), ciID(ciID), pid(pid),
              type(type), name(name), gpuMemoryUsage(gpuMemoryUsage) {}

        // getters: read-only access used by the layout renderer
        uint64_t getGpuID()          const { return gpuID; }
        String   getGiID()           const { return giID; }
        String   getCiID()           const { return ciID; }
        uint64_t getPid()            const { return pid; }
        String   getType()           const { return type; }
        String   getName()           const { return name; }
        String   getGpuMemoryUsage() const { return gpuMemoryUsage; }
};
