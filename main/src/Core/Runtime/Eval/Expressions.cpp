#include "Expressions.h"

RuntimeValPtr evalProgram (StmtPtr node, EnvironmentPtr env){
	RuntimeValPtr returnvalue = std::make_shared<NullVal>();
	std::shared_ptr<Program> program = (std::dynamic_pointer_cast<Program>(node));
	for (const auto& nodechild : program->body){
		returnvalue = evaluate(nodechild, env);
	}
	return returnvalue;
}

RuntimeValPtr evalIdentifier (StmtPtr node, EnvironmentPtr env){
	std::shared_ptr<Identifier> identifier = std::dynamic_pointer_cast<Identifier>(node);
	RuntimeValPtr val = env->readVar(identifier->name);
	return val;
}

RuntimeValPtr evalObjectExpr (StmtPtr node, EnvironmentPtr env){
	std::shared_ptr<ObjectLiteral> child = std::dynamic_pointer_cast<ObjectLiteral>(node);
	std::shared_ptr<ObjectVal> output = std::make_shared<ObjectVal>();
	for (auto& property : child->properties){
		output->properties.insert({property.key, (property.value == nullptr ? env->readVar(property.key) : evaluate(property.value, env))});
		//std::cout<<property.key<<": "<<std::dynamic_pointer_cast<IntVal>(evaluate(property.value, env))->value;
	}
	return output;
}

RuntimeValPtr evalVarDeclaration (StmtPtr node, EnvironmentPtr env){
	std::shared_ptr<VarDeclaration> var = std::dynamic_pointer_cast<VarDeclaration>(node);
	RuntimeValPtr val = (var->value != nullptr ? evaluate(var->value, env) : std::make_shared<NullVal>());
	env->declareVar(var->identifier, val, var->isConst);
	return val;
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


RuntimeValPtr evalAssignmentExpr (StmtPtr node, EnvironmentPtr env){
	std::shared_ptr<AssignmentExpr> child = std::dynamic_pointer_cast<AssignmentExpr>(node);
	if (child->identifier->getType() != NodeType::Identifier){
		throw std::runtime_error("No identifier as object to assign");
	}
	std::shared_ptr<Identifier> ident = std::dynamic_pointer_cast<Identifier>(child->identifier);
	if (env->constants.count(ident->name)){
		throw std::runtime_error("Cannot re assign const");
	}
	RuntimeValPtr val = evaluate(child->value, env);
	env->assignVar(ident->name, val);
	return val;
}

RuntimeValPtr evalObjectExpression (StmtPtr node, EnvironmentPtr env){

}

RuntimeValPtr evalCallExpression (StmtPtr node, EnvironmentPtr env){

}