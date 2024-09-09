#ifndef AST_H
#define AST_H

#include <vector>
#include <string>
#include <iostream>
#include <memory> // Per std::shared_ptr

enum class NodeType {
    Program,
    VarDeclaration,
    FunctionDeclaration,
    ClassDeclaration,
    EnumDeclaration,
    StructDeclaration,
    EventDeclaration,
    MacroDeclaration,
    AssignmentExpr,
    CallExpr,
    BinaryExpr,
    MemberExpr,
    Identifier,
    IntLiteral,
    FloatLiteral,
    StringLiteral,
    BoolLiteral,
    Property,
    ObjectLiteral
};

// Base class for all AST nodes
class ParentStmt {
public:
    virtual ~ParentStmt() = default;
    virtual NodeType getType() const = 0;
    virtual void print() const = 0; // Funzione print per stampa
};

using ParentStmtPtr = std::shared_ptr<ParentStmt>;

class Stmt : public ParentStmt {
public:
    Stmt() = default;
    NodeType getType() const override {
        return NodeType::Program; // Imposta un valore predefinito o personalizzato
    }
    void print() const override {
        std::cout << "Stmt\n";
    }
};

class Expr : public Stmt {
public:
    Expr() = default;
    virtual ~Expr() = default;
    void print() const override {
        std::cout << "Expr\n";
    }
};

using ExprPtr = std::shared_ptr<Expr>;

// Statement nodes
class Program : public Stmt {
public:
    Program() = default;
    Program(const std::vector<ParentStmtPtr>& body) : body(body) {}
    NodeType getType() const override { return NodeType::Program; }
    
    void print() const override {
        std::cout << "\nProgram w/ size: " << body.size() << "\n";
        for (const auto& stmt : body) {
            stmt->print();
        }
    }

    std::vector<ParentStmtPtr> body;
};

class Param : public Stmt {
public:
    Param() = default;
    Param(const std::string& name, const std::string& type, const ExprPtr& defaultVal)
        : name(name), type(type), defaultVal(defaultVal) {}

    std::string name;
    std::string type;
    ExprPtr defaultVal;

    void print() const override {
        std::cout << "Param\n" << name << " : " << type;
    }
};

class VarDeclaration : public Stmt {
public:
    VarDeclaration() = default;
    VarDeclaration(bool isConst, bool isPublic, bool isPrivate, const std::string& identifier, const ExprPtr& value)
        : isConst(isConst), isPublic(isPublic), isPrivate(isPrivate), identifier(identifier), value(value) {}

    NodeType getType() const override { return NodeType::VarDeclaration; }
    
    void print() const override {
        std::cout << "VarDeclaration\n";
        std::cout << "  isConst: " << (isConst ? "true" : "false") << "\n";
        std::cout << "  isPublic: " << (isPublic ? "true" : "false") << "\n";
        std::cout << "  isPrivate: " << (isPrivate ? "true" : "false") << "\n";
        std::cout << "  identifier: " << identifier << "\n";
        value->print();
    }

    bool isConst = false;
    bool isPublic = false;
    bool isPrivate = false;
    std::string identifier;
    ExprPtr value;
};

class FunctionDeclaration : public Stmt {
public:
    FunctionDeclaration() = default;
    FunctionDeclaration(bool isConst, bool isPublic, bool isPrivate, const std::string& name, const std::vector<std::shared_ptr<Param>>& parameters, const std::vector<ParentStmtPtr>& body)
        : isConst(isConst), isPublic(isPublic), isPrivate(isPrivate), name(name), parameters(parameters), body(body) {}

    NodeType getType() const override { return NodeType::FunctionDeclaration; }
    
    void print() const override {
        std::cout << "FunctionDeclaration\n";
        std::cout << "  isConst: " << (isConst ? "true" : "false") << "\n";
        std::cout << "  isPublic: " << (isPublic ? "true" : "false") << "\n";
        std::cout << "  isPrivate: " << (isPrivate ? "true" : "false") << "\n";
        std::cout << "  name: " << name << "\n";
        std::cout << "  parameters: ";
        for (const auto& param : parameters) {
            std::cout << param->name << " : " << param->type << "\n";
        }
        std::cout << "\n";
        for (const auto& line : body) {
            line->print();
        }
    }

    bool isConst = false;
    bool isPublic = false;
    bool isPrivate = false;
    std::vector<std::shared_ptr<Param>> parameters;
    std::string name;
    std::vector<ParentStmtPtr> body;
};

class ClassDeclaration : public Stmt {
public:
    ClassDeclaration() = default;
    ClassDeclaration(const std::string& name, const std::vector<ParentStmtPtr>& members)
        : name(name), members(members) {}

    NodeType getType() const override { return NodeType::ClassDeclaration; }
    
    void print() const override {
        std::cout << "UNSUPPORTED PRINT CLASSES" << "\n";
    }

    std::string name;
    std::vector<ParentStmtPtr> members;
};

class EnumDeclaration : public Stmt {
public:
    EnumDeclaration() = default;
    EnumDeclaration(const std::string& name, const std::vector<std::string>& values)
        : name(name), values(values) {}

    NodeType getType() const override { return NodeType::EnumDeclaration; }
    
    void print() const override {
        std::cout << "UNSUPPORTED PRINT CLASSES" << "\n";
    }

    std::string name;
    std::vector<std::string> values;
};

class StructDeclaration : public Stmt {
public:
    StructDeclaration() = default;
    StructDeclaration(const std::string& name, const std::vector<ParentStmtPtr>& members)
        : name(name), members(members) {}

    NodeType getType() const override { return NodeType::StructDeclaration; }
    
    void print() const override {
        std::cout << "UNSUPPORTED PRINT CLASSES" << "\n";
    }

    std::string name;
    std::vector<ParentStmtPtr> members;
};

class EventDeclaration : public Stmt {
public:
    EventDeclaration() = default;
    EventDeclaration(const std::string& name, const std::vector<std::string>& parameters, const std::vector<ParentStmtPtr>& body)
        : name(name), parameters(parameters), body(body) {}

    NodeType getType() const override { return NodeType::EventDeclaration; }
    
    void print() const override {
        std::cout << "UNSUPPORTED PRINT CLASSES" << "\n";
    }

    std::string name;
    std::vector<std::string> parameters;
    std::vector<ParentStmtPtr> body;
};

class MacroDeclaration : public Stmt {
public:
    MacroDeclaration() = default;
    MacroDeclaration(const std::string& name, const std::vector<std::string>& parameters, const std::vector<ParentStmtPtr>& body)
        : name(name), parameters(parameters), body(body) {}

    NodeType getType() const override { return NodeType::MacroDeclaration; }
    
    void print() const override {
        std::cout << "UNSUPPORTED PRINT CLASSES" << "\n";
    }

    std::string name;
    std::vector<std::string> parameters;
    std::vector<ParentStmtPtr> body;
};

// Expression nodes

class AssignmentExpr : public Expr {
public:
    AssignmentExpr() = default;
    AssignmentExpr(const ExprPtr& identifier, const ExprPtr& value)
        : identifier(identifier), value(value) {}

    NodeType getType() const override { return NodeType::AssignmentExpr; }
    
    void print() const override {
        std::cout << "AssignmentExpr\n";
        std::cout << "  identifier: ";
        identifier->print();
        std::cout << "value: ";
        value->print();
    }

    ExprPtr identifier;
    ExprPtr value;
};

class CallExpr : public Expr {
public:
    CallExpr() = default;
    CallExpr(const std::string& identifier, const std::vector<ExprPtr>& arguments)
        : identifier(identifier), arguments(arguments) {}

    NodeType getType() const override { return NodeType::CallExpr; }
    
    void print() const override {
        std::cout << "CallExpr\n";
        std::cout << "  identifier: " << identifier << "\n" << "args: ";
        for (const auto& arg : arguments) {
            arg->print();
        }
    }

    std::string identifier;
    std::vector<ExprPtr> arguments;
};

class BinaryExpr : public Expr {
public:
    BinaryExpr() = default;
    BinaryExpr(const ExprPtr& left, const ExprPtr& right, const std::string& operatorType)
        : left(left), right(right), operatorType(operatorType) {}

    NodeType getType() const override { return NodeType::BinaryExpr; }
    
    void print() const override {
        std::cout << "BinaryExpr\n";
        std::cout << "  operatorType: " << operatorType << "\n" << "left";
        left->print();
        std::cout << "right";
        right->print();
    }

    ExprPtr left;
    ExprPtr right;
    std::string operatorType;
};

class MemberExpr : public Expr {
public:
    MemberExpr() = default;
    MemberExpr(const ExprPtr& object, const std::string& property)
        : object(object), property(property) {}

    NodeType getType() const override { return NodeType::MemberExpr; }
    
    void print() const override {
        std::cout << "UNSUPPORTED PRINT CLASSES" << "\n";
    }

    ExprPtr object;
    std::string property;
};

class Identifier : public Expr {
public:
    Identifier() = default;
    Identifier(const std::string& name) : name(name) {}

    NodeType getType() const override { return NodeType::Identifier; }
    
    void print() const override {
        std::cout << "Identifier\n";
        std::cout << "  name: " << name << "\n";
    }

    std::string name;
};

class IntLiteral : public Expr {
public:
    IntLiteral() = default;
    IntLiteral(int value) : value(value) {}

    NodeType getType() const override { return NodeType::IntLiteral; }
    
    void print() const override {
        std::cout << "IntLiteral\n";
        std::cout << "  value: " << value << "\n";
    }

    int value;
};

class FloatLiteral : public Expr {
public:
    FloatLiteral() = default;
    FloatLiteral(float value) : value(value) {}

    NodeType getType() const override { return NodeType::FloatLiteral; }
    
    void print() const override {
        std::cout << "FloatLiteral\n";
        std::cout << "  value: " << value << "\n";
    }

    float value;
};

class StringLiteral : public Expr {
public:
    StringLiteral() = default;
    StringLiteral(const std::string& value) : value(value) {}

    NodeType getType() const override { return NodeType::StringLiteral; }
    
    void print() const override {
        std::cout << "StringLiteral\n";
        std::cout << "  value: " << value << "\n";
    }

    std::string value;
};

class BoolLiteral : public Expr {
public:
    BoolLiteral() = default;
    BoolLiteral(bool value) : value(value) {}

    NodeType getType() const override { return NodeType::BoolLiteral; }
    
    void print() const override {
        std::cout << "BoolLiteral\n";
        std::cout << "  value: " << (value ? "true" : "false") << "\n";
    }

    bool value;
};

class Property : public Expr {
public:
    Property() = default;
    Property(const std::string& key, const ExprPtr& value) : key(key), value(value) {}

    NodeType getType() const override { return NodeType::Property; }
    
    void print() const override {
        std::cout << "Property\n";
        std::cout << "  key: " << key << "\n";
        value->print();
    }

    std::string key;
    ExprPtr value;
};

class ObjectLiteral : public Expr {
public:
    ObjectLiteral() = default;
    ObjectLiteral(const std::vector<Property>& properties) : properties(properties) {}

    NodeType getType() const override { return NodeType::ObjectLiteral; }
    
    void print() const override {
        std::cout << "ObjectLiteral\n";
        for (const auto& property : properties) {
            property.print();
        }
    }

    std::vector<Property> properties;
};

#endif // AST_H
