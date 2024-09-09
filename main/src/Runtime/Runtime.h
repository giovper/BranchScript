#ifndef RUNTIME_H
#define RUNTIME_H

#include <string>
#include <vector>

class Runtime {
public:
    Runtime();
    ~Runtime();

    void run(const std::vector<std::string>& file);
    void ast(const std::vector<std::string>& file);
    std::string startingPath;
};

#endif // RUNTIME_H
