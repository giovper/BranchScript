#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include <string>
#include <unordered_map>
#include <vector>

class MemoryAllocator {
public:
    struct DataClass {
        std::string name;
        size_t size;
    };

    bool AddDataClass(const std::string& name, size_t bytesNumber);
    bool RemoveDataClass(const std::string& name);
    size_t AddNewAllocation(const std::string& dataClass);
    bool SetAllocationData(size_t allocationID, const void* data);
    bool ConvertAllocation(size_t allocationID, const std::string& newDataClass);
    void* GetAllocationData(size_t allocationID) const;

    ~MemoryAllocator();

private:
    struct Allocation {
        size_t id;
        DataClass dataClass;
        char* data;
    };

    std::unordered_map<std::string, DataClass> dataClasses;
    std::vector<Allocation> allocations;
};

#endif // MEMORY_ALLOCATOR_H
