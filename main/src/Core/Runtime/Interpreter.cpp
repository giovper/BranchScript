#include "Interpreter.h"

RuntimeValPtr evaluate(StmtPtr node, EnvironmentPtr env){
	NodeType type = node->getType();
	if (type == NodeType::IntLiteral){
		std::shared_ptr<IntLiteral> child = std::dynamic_pointer_cast<IntLiteral>(node);
		return std::make_shared<IntVal>(child->value);
	} else if (type == NodeType::FloatLiteral){
		std::shared_ptr<FloatLiteral> child = std::dynamic_pointer_cast<FloatLiteral>(node);
		return std::make_shared<FloatVal>(child->value);
	} else if (type == NodeType::StringLiteral){
		std::shared_ptr<StringLiteral> child = std::dynamic_pointer_cast<StringLiteral>(node);
		return std::make_shared<StringVal>(child->value);
	} else if (type == NodeType::BoolLiteral){
		std::shared_ptr<BoolLiteral> child = std::dynamic_pointer_cast<BoolLiteral>(node);
		return std::make_shared<BoolVal>(child->value);
	} else if (type == NodeType::Identifier) {
		throw std::runtime_error("This node has no setup in evaluate");
	} else if (type == NodeType::Program) {
		evalProgram(node, env);
	} else if (type == NodeType::BinaryExpr) {
		evalBinaryExpr(node, env);
	} else {
		throw std::runtime_error("This node has no setup in evaluate");
	}
}