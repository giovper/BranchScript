#include "Expressions.h"

RuntimeValPtr evalProgram (StmtPtr node, EnvironmentPtr env){
	RuntimeValPtr returnvalue = std::make_shared<NullVal>();
	std::shared_ptr<Program> program = (std::dynamic_pointer_cast<Program>(node));
	for (const auto& nodechild : program->body){
		returnvalue = evaluate(nodechild, env);
	}
	return returnvalue;
}

RuntimeValPtr evalBinaryExpr (StmtPtr node, EnvironmentPtr env){
	std::shared_ptr<BinaryExpr> child = std::dynamic_pointer_cast<BinaryExpr>(node);
	RuntimeValPtr left = evaluate(child->left, env);
	RuntimeValPtr right = evaluate(child->right, env);
	ValueType ltype = left->getType();
	ValueType rtype = right->getType();

	if ((ltype == ValueType::Int || ltype == ValueType::Float) && (rtype == ValueType::Int || rtype == ValueType::Float)){
		return evalNumericBinaryExpr(left, right, child->operatorType, env);
	} else {
		throw std::runtime_error("No binary expression supports dis");
	}
}

RuntimeValPtr evalNumericBinaryExpr (RuntimeValPtr left, RuntimeValPtr right, std::string op, EnvironmentPtr env){
	float left_val;
	float right_val;
	bool isint = true;
	if (left->getType() == ValueType::Int){
		left_val = (std::dynamic_pointer_cast<IntVal>(left))->value;
	} else if (left->getType() == ValueType::Float){
		left_val = (std::dynamic_pointer_cast<FloatVal>(left))->value;
		isint = false;
	} else {
		throw std::runtime_error("left error");
	}
	if (right->getType() == ValueType::Int){
		right_val = (std::dynamic_pointer_cast<IntVal>(right))->value;
	} else if (right->getType() == ValueType::Float){
		right_val = (std::dynamic_pointer_cast<FloatVal>(right))->value;
		isint = false;
	} else {
		throw std::runtime_error("right error");
	}	
	float result;
	if (op == "+"){
		result = left_val+right_val;
	} else if (op == "-"){
		result = left_val-right_val;
	} else if (op == "*"){
		result = left_val*right_val;
	} else if (op == "/"){
		result = left_val/right_val;
	} else if (op == "%"){
		result = int(left_val)%int(right_val);
	}
	if (isint){
		return std::make_shared<IntVal>(int(result));
	} else {
		return std::make_shared<FloatVal>(result);
	}

}

RuntimeValPtr evalIdentifier (StmtPtr node, EnvironmentPtr env){

}

RuntimeValPtr evalAssignment (StmtPtr node, EnvironmentPtr env){

}

RuntimeValPtr evalObjectExpression (StmtPtr node, EnvironmentPtr env){

}

RuntimeValPtr evalCallExpression (StmtPtr node, EnvironmentPtr env){

}