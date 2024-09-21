#include "Terminal/Terminal.h"
#include <iostream>
#include <cstring>
//#include <chrono>
//#include <thread>

int main() {
    Terminal terminal;
    terminal.ListenToCLI();
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}