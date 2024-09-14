// Runtime.h
#ifndef RUNTIME_H
#define RUNTIME_H

#include <string>
#include <iostream>
#include <vector>

class Runtime {
public:
    Runtime();
    void run(const std::vector<std::string>& file);
    void ast(const std::vector<std::string>& file);
    std::string startingPath;

private:

};

#endif // RUNTIME_H
