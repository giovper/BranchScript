#include "MemoryAllocator/MemoryAllocator.h"
#include "Terminal/Terminal.h"
#include <iostream>
#include <cstring>
//#include <chrono>
//#include <thread>

int main() {
    MemoryAllocator allocator;
    Terminal terminal;
    terminal.ListenToCLI();
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}

/*MemoryAllocator example code
    // Aggiungi classi di dati
    allocator.AddDataClass("int", sizeof(int));
    allocator.AddDataClass("float", sizeof(float));

    // Crea una nuova allocazione per int
    size_t intAllocID = allocator.AddNewAllocation("int");
    if (intAllocID == static_cast<size_t>(-1)) {
        std::cerr << "Failed to add new allocation for 'int'" << std::endl;
        return 1;
    }

    // Imposta i dati per l'allocazione 'int'
    int value = 42;
    if (!allocator.SetAllocationData(intAllocID, &value)) {
        std::cerr << "Failed to set allocation data for 'int'" << std::endl;
        return 1;
    }

    // Ottieni i dati dell'allocazione
    int* retrievedValue = static_cast<int*>(allocator.GetAllocationData(intAllocID));
    if (retrievedValue) {
        std::cout << "Retrieved value: " << *retrievedValue << std::endl;
    } else {
        std::cerr << "Failed to retrieve allocation data" << std::endl;
        return 1;
    }

    // Converti l'allocazione a un altro tipo di DataClass
    if (!allocator.ConvertAllocation(intAllocID, "float")) {
        std::cerr << "Failed to convert allocation to 'float'" << std::endl;
        return 1;
    }

    // Imposta nuovi dati per la conversione
    float floatValue = 3.14f;
    if (!allocator.SetAllocationData(intAllocID, &floatValue)) {
        std::cerr << "Failed to set allocation data for 'float'" << std::endl;
        return 1;
    }

    // Ottieni i dati dell'allocazione dopo la conversione
    float* retrievedFloatValue = static_cast<float*>(allocator.GetAllocationData(intAllocID));
    if (retrievedFloatValue) {
        std::cout << "Retrieved float value: " << *retrievedFloatValue << std::endl;
    } else {
        std::cerr << "Failed to retrieve allocation data after conversion" << std::endl;
        return 1;
    }
*/