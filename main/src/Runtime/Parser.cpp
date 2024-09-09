#include "Parser.h"
#include <iostream>
#include <stdexcept>

tokenParentElem Parser::eat(bool removeIfEmpty){
	tokenParentElem t;
    if ((Tokens.empty() || Tokens.front().empty()) && !removeIfEmpty) {
        throw std::runtime_error("Attempting to eat from an empty token stream");
    }
    if (!(Tokens.empty() || Tokens.front().empty())) {
    	t = Tokens.front().front();
    	Tokens.front().erase(Tokens.front().begin());
    }
    if (Tokens.front().empty() && removeIfEmpty) {
        Tokens.erase(Tokens.begin());
    }
    return t;
}

tokenParentElem Parser::eat(){
    if (Tokens.empty() || Tokens.front().empty()) {
        throw std::runtime_error("Attempting to eat from an empty token stream");
    }
    tokenParentElem t = Tokens.front().front();
    Tokens.front().erase(Tokens.front().begin());
    return t;
}


tokenParentElem Parser::expect(tokenParent expected, std::string message){
	if (at().token != expected){
		std::cout<<std::endl<<"Expected "<<expected<<" instead of "<<at().token;
	}
	return at();
}

tokenParentElem Parser::at(){
	return Tokens.front().front();
}

void Parser::logError(std::string error, int line){
	std::cout<<std::endl<<line<<": "<<error<<std::endl;
}

void Parser::logMessage(std::string message, int line){
	std::cout<<std::endl<<"<msg>> "<<line<< ": "<<message;
}

bool Parser::isEOL(bool remove){
	logMessage("executing is EOL", 0);
	bool output = (Tokens.front().size() == 0);
	if (remove && output){
		Tokens.erase(Tokens.begin());
		//eat(true);
	}
	return output;
}

bool Parser::notEOF(){
	return at().token != _EOF;
}

Program Parser::produceAST(const std::vector<std::string>& file){
	Lexer lexer;
	Tokens = lexer.tokenizeMultiLine(file);
	Program Root;
	while (notEOF()){
		Root.body.push_back(parseLineStatement());
		isEOL(true);
	}
	return Root;
}

Stmt Parser::parseLineStatement(){
	logMessage("parseLineStmt", 0);
	std::vector<tokenParentElem> Modifiers;
	while(at().token == modifier){
		Modifiers.push_back(eat());
	}
	switch (at().token){
	case _function:
		return parseFunctionDec(Modifiers);
		break;
	case _macro:
		return parseMacroDec(Modifiers);
		break;
	case _event:
		return parseEventDec(Modifiers);
		break;
	case _enum:
		return parseEnumDec(Modifiers);
		break;
	case _struct:
		return parseStructDec(Modifiers);
		break;
	case var:
		return parseVarDec(Modifiers);
		break;
	default:
		return parseExpr();
	}
}

FunctionDeclaration Parser::parseFunctionDec(std::vector<tokenParentElem> Modifiers){
	logMessage("parseFuncDec", 0);
	eat();
	int bracCounter = 0;
	FunctionDeclaration functiondeclaration;
	for (int i=0; i<Modifiers.size(); i++){
		if (Modifiers[i].subclass == "const"){
			functiondeclaration.isConst = true;
		} else if (Modifiers[i].subclass == "public"){
			functiondeclaration.isPublic = true;
		} else if (Modifiers[i].subclass == "private"){
			functiondeclaration.isPrivate = true;
		}
	}
	if (functiondeclaration.isPrivate && functiondeclaration.isPublic){
		logError("Var can't be both public and private", 0);
	}
	functiondeclaration.name = expect(other, "there is no name").value;
	std::vector<Param> Params = parseParams();
	expect(openBrac, "Expected brace in function declaration");
	eat();
	while(notEOF() || (not(at().token == closeBrac && bracCounter <= 0))){
		if (at().token == openBrac){
			bracCounter++;
		} else if (at().token == closeBrac) {
			bracCounter--;
		}
		if (bracCounter>=0){
			functiondeclaration.body.push_back(parseLineStatement());
			isEOL(true);
		}
	}
	return functiondeclaration;
}

EventDeclaration Parser::parseEventDec(std::vector<tokenParentElem> Modifiers){

}

MacroDeclaration Parser::parseMacroDec(std::vector<tokenParentElem> Modifiers){

}

EnumDeclaration Parser::parseEnumDec(std::vector<tokenParentElem> Modifiers){

}

StructDeclaration Parser::parseStructDec(std::vector<tokenParentElem> Modifiers){

}

VarDeclaration Parser::parseVarDec(std::vector<tokenParentElem> Modifiers){
	logMessage("parseVarDec", 0);
	eat();
	VarDeclaration vardeclaration;
	for (int i=0; i<Modifiers.size(); i++){
		if (Modifiers[i].subclass == "const"){
			vardeclaration.isConst = true;
		} else if (Modifiers[i].subclass == "public"){
			vardeclaration.isPublic = true;
		} else if (Modifiers[i].subclass == "private"){
			vardeclaration.isPrivate = true;
		}
	}
	if (vardeclaration.isPrivate && vardeclaration.isPublic){
		logError("Var can't be both public and private", 0);
	}
	vardeclaration.identifier = expect(other, "there is no name").value;
	eat();
	expect(equals, "there is no equals");
	eat();
	logMessage("Val:", 0);
	vardeclaration.value = parseExpr();
	return(vardeclaration); 
}

std::vector<Param> Parser::parseParams(){
	logMessage("parseParams", 0);
	std::vector<Param> output;
	std::string dataclass;
	std::string name;
	Expr defaultVal;
	expect(openParen, "Expected parenthesis");
	eat();
	while(at().token != closeParen && notEOF()){
		if (at().token == dataClass){
			eat();
			if (dataclass == "" && name == ""){
				dataclass = at().subclass;
			} else {
				logError("Wrong param decl", 0);
			}
		} else if (at().token == other){
			eat();
			if (name == ""){
				name = at().value;
			} else {
				logError("Name already exists", 0);
			}
		} else if (at().token == comma){
			eat();
			if (name != ""){
				output.push_back(Param{name, dataclass, defaultVal});
			} else {
				logError("Unexisting name", 0);
			}
			name = "";
			dataclass = "";
		} else if (at().token == equals){
			eat();
			if (name != ""){
				defaultVal = parseExpr();
			} else {
				logError("value for no name", 0);
			}
		}
	}
	return output;
}

Expr Parser::parseExpr(){
	logMessage("parseExpr", 0);
	return parseAssignmentExpr();
}

Expr Parser::parseAssignmentExpr(){
	logMessage("parseAssign", 0);
	Expr left = parseObjectExpr();
	if(at().token == equals){
		eat();
		Expr val = parseExpr();
		AssignmentExpr ae;
		ae.identifier = left;
		ae.value = val;
		return ae;
	}
	return left;
}

Expr Parser::parseObjectExpr(){
	logMessage("parseObjExpr", 0);
	return parseAdditiveExpr();
}

Expr Parser::parseAdditiveExpr(){
	logMessage("parseAdd", 0);
    Expr left = parseMultiplicitaveExpr();
    while (at().subclass == "+" || at().subclass == "-") {
        std::string addoperator = eat().subclass;
        Expr right = parseMultiplicitaveExpr();

        left = BinaryExpr(left, right, addoperator); 
    }
    return left;
}

Expr Parser::parseMultiplicitaveExpr(){
	logMessage("parseMult", 0);
    Expr left = parseCallMemberExpr();
    while (at().subclass == "*" || at().subclass == "/" || at().subclass == "%") {
        std::string multoperator = eat().subclass;
        Expr right = parseCallMemberExpr();

        left = BinaryExpr(left, right, multoperator); 
    }
    return left;
}

Expr Parser::parseCallMemberExpr(){
	logMessage("parseCallMemb", 0);
	return parseCallExpr();
}

Expr Parser::parseCallExpr(){
	logMessage("parseCalLExpr", 0);
	return parsePrimaryExpr();
}

Expr Parser::parsePrimaryExpr(){
	logMessage("parsePrimExpr", 0);
	switch (at().token) {
	case other:
		eat();
		return Identifier{at().value};
		break;
	case dataValue:
		if (at().subclass == "int"){
			eat();
			return IntLiteral{std::stoi(at().value)};
		} else if (at().subclass == "float"){
			eat();
			return FloatLiteral{std::stof(at().value)};
		} else {
			eat();
			logError("No recognized type of val", 0); 
		}
	default:
		logError("No type", 0);
		std::cout<<at().token<<"->"<<at().subclass<<"->"<<at().value;
		eat();
		return Identifier{};
	}
}