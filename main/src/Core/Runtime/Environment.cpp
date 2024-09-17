#include "Environment.h"

RuntimeValPtr Environment::declareVar(std::string name, RuntimeValPtr value, bool isConst){
	if (variables.count(name)){
		throw std::runtime_error("Already declared var");
	}
	variables.insert({name, value});
	
	if (isConst){
		constants.insert(name);
	}
	return value;
}

RuntimeValPtr Environment::assignVar(std::string name, RuntimeValPtr value){
	EnvironmentPtr env = resolve(name);
	if (env->constants.count(name) != 0){
		throw std::runtime_error("Cannot assign const var");
	}
	env->variables[name] = value;
	return value;
}

RuntimeValPtr Environment::readVar(std::string name){
	EnvironmentPtr env = resolve(name);
	return env->variables[name];
}

EnvironmentPtr Environment::resolve(std::string name){
	if (variables.count(name) != 0){
		std::shared_ptr a = std::make_shared<Environment>(variables, constants);
		return a;
	}
	if (global){
		throw std::runtime_error("Variable \"" + name + "\" not declared in scope");
	}
	return parent->resolve(name);
}