#include "MemoryAllocator.h"
#include <cstring>
#include <stdexcept>
#include <algorithm> // Per std::remove_if

bool MemoryAllocator::AddDataClass(const std::string& name, size_t bytesNumber) {
    if (dataClasses.find(name) != dataClasses.end()) {
        return false; // DataClass già esistente
    }
    dataClasses[name] = {name, bytesNumber};
    return true;
}

bool MemoryAllocator::RemoveDataClass(const std::string& name) {
    auto it = dataClasses.find(name);
    if (it != dataClasses.end()) {
        // Rimuove anche le allocazioni con questo tipo di DataClass
        allocations.erase(
            std::remove_if(allocations.begin(), allocations.end(),
                           [&name](const Allocation& alloc) { return alloc.dataClass.name == name; }),
            allocations.end()
        );
        dataClasses.erase(it);
        return true;
    }
    return false; // DataClass non trovata
}

size_t MemoryAllocator::AddNewAllocation(const std::string& dataClass) {
    auto it = dataClasses.find(dataClass);
    if (it == dataClasses.end()) {
        return static_cast<size_t>(-1); // DataClass non trovata
    }

    Allocation newAlloc;
    newAlloc.id = allocations.size();
    newAlloc.dataClass = it->second;
    newAlloc.data = nullptr;

    allocations.push_back(newAlloc);
    return newAlloc.id;
}

bool MemoryAllocator::SetAllocationData(size_t allocationID, const void* data) {
    if (allocationID >= allocations.size()) {
        return false; // ID di allocazione non valido
    }

    Allocation& allocation = allocations[allocationID];
    if (allocation.data == nullptr) {
        allocation.data = new char[allocation.dataClass.size];
    }

    std::memcpy(allocation.data, data, allocation.dataClass.size);
    return true;
}

bool MemoryAllocator::ConvertAllocation(size_t allocationID, const std::string& newDataClass) {
    if (allocationID >= allocations.size()) {
        return false; // ID di allocazione non valido
    }

    auto it = dataClasses.find(newDataClass);
    if (it == dataClasses.end()) {
        return false; // DataClass non trovata
    }

    Allocation& allocation = allocations[allocationID];
    if (allocation.data) {
        delete[] allocation.data;
    }

    allocation.dataClass = it->second;
    allocation.data = new char[allocation.dataClass.size];
    return true;
}

void* MemoryAllocator::GetAllocationData(size_t allocationID) const {
    if (allocationID >= allocations.size()) {
        return nullptr; // ID di allocazione non valido
    }

    const Allocation& allocation = allocations[allocationID];
    return static_cast<void*>(allocation.data);
}

MemoryAllocator::~MemoryAllocator() {
    for (auto& allocation : allocations) {
        delete[] allocation.data;
    }
}
