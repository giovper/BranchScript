#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <map>
#include <set>
#include <string>
#include "Values.h"

class Environment;
using EnvironmentPtr = std::shared_ptr<Environment>;

class Environment {
public:
    ~Environment() = default;
    Environment() : parent(nullptr), global(true) {}
    Environment(EnvironmentPtr parentENV)
        : parent(parentENV), global(parentENV == nullptr) {}
    RuntimeVal declareVar(std::string name, RuntimeVal value, bool isConst);
    RuntimeVal assignVar(std::string name, RuntimeVal value);

private:
    EnvironmentPtr parent;
    std::map<std::string, RuntimeVal> variables;
    std::set<std::string> constants;
    bool global;
};

#endif
