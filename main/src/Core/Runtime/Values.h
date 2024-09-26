#ifndef VALUES_H 
#define VALUES_H

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "Environment.h"

enum class ValueType {
    None,
    Null,
    Bool,
    Int,
    Float,
    String,
    Object,
    NativeFunction,
    Function
};

class RuntimeValParent {
public:
    RuntimeValParent() = default;
    virtual ValueType getType() const = 0;
    virtual ~RuntimeValParent() = default;
};

class RuntimeVal : public RuntimeValParent {
public:
    RuntimeVal() = default;  // Costruttore predefinito
    ValueType getType() const override {
        return ValueType::None;
    }
};

using RuntimeValPtr = std::shared_ptr<RuntimeVal>;

class NullVal : public RuntimeVal {
public:
    NullVal() = default;  // Costruttore per inizializzare il valore
    NullVal(const NullVal& other) {} // Costruttore di copia
    ValueType getType() const override {
        return ValueType::Null;
    }
};

class IntVal : public RuntimeVal {
public:
    int value;

    IntVal(int val) : value(val) {}  // Costruttore per inizializzare il valore
    IntVal(const IntVal& other) : value(other.value) {} // Costruttore di copia
    ValueType getType() const override {
        return ValueType::Int;
    }
};

class FloatVal : public RuntimeVal {
public:
    float value;

    FloatVal(float val) : value(val) {}  // Costruttore per inizializzare il valore
    FloatVal(const FloatVal& other) : value(other.value) {} // Costruttore di copia
    ValueType getType() const override {
        return ValueType::Float;
    }
};

class BoolVal : public RuntimeVal {
public:
    bool value;

    BoolVal(bool val) : value(val) {}  // Costruttore per inizializzare il valore
    BoolVal(const BoolVal& other) : value(other.value) {} // Costruttore di copia
    ValueType getType() const override {
        return ValueType::Bool;
    }
};

class StringVal : public RuntimeVal {
public:
    std::string value;

    StringVal(const std::string& val) : value(val) {}  // Costruttore per inizializzare il valore
    StringVal(const StringVal& other) : value(other.value) {} // Costruttore di copia
    ValueType getType() const override {
        return ValueType::String;
    }
};

class ObjectVal : public RuntimeVal {
public:
    std::map<std::string, RuntimeValPtr> properties;
    ObjectVal() = default;
    ObjectVal(const ObjectVal& other) : properties(other.properties) {} // Costruttore di copia
    ValueType getType() const override {
        return ValueType::Object;
    }
};

//todo: functions, native functions, function value

#endif
