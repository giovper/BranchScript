#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <map>
#include <set>
#include <string>
#include "Values.h"
#include <stdexcept>
#include <iostream>
#include<windows.h>

class Environment;
using EnvironmentPtr = std::shared_ptr<Environment>;

class Environment : public std::enable_shared_from_this<Environment>{
public:
    ~Environment() = default;

    Environment() : parent(nullptr), global(true) {}
    
    Environment(EnvironmentPtr parentEnv) //figlio
        : parent(parentEnv), global(parentEnv == nullptr) {}
    
    Environment(std::map<std::string, RuntimeValPtr> variables, std::set<std::string> constants) //copiona
        : parent(nullptr), global(true), variables(variables), constants(constants) {}

    Environment(const Environment& env) //copia
        : parent(env.parent), global(env.parent == nullptr), variables(env.variables), constants(env.constants) {}
    
    Environment(const Environment* env) //copia
        : parent(env->parent), global(env->parent == nullptr), variables(env->variables), constants(env->constants) {}

    RuntimeValPtr declareVar(std::string name, RuntimeValPtr value, bool isConst);
    RuntimeValPtr assignVar(std::string name, RuntimeValPtr value);
    EnvironmentPtr resolve(std::string name);
    RuntimeValPtr readVar(std::string name);

private:
    EnvironmentPtr parent;
    std::map<std::string, RuntimeValPtr> variables;
    std::set<std::string> constants;
    bool global;
};

#endif
