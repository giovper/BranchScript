/*#include "Environment.h"

RuntimeVal Environment::declareVar(std::string name, RuntimeVal value, bool const){
	if (variables.count(name)){
		throw std::runtime_error("Already declared var");
	}
	variables[name] = value;
	
	if (const){
		constants.insert(name)
	}
}

RuntimeVal Environment::assignVar(std::string name, RuntimeVal value){
}*/