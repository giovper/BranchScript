#include "Parser.h"
#include <iostream>
#include <stdexcept>

bool Parser::eatline(){
	tokenParentElem t;
    if (Tokens.empty()) {
        throw std::runtime_error("Attempting to eat from an empty token stream");
    }
    if (Tokens.front().empty()) {
        Tokens.erase(Tokens.begin());
    	return true;
    } else {
    	return false;
    }
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
		if (LOG) {std::cout<<std::endl<<"Expected "<<expected<<" instead of "<<at().token;}
	}
	return at();
}

tokenParentElem Parser::at(){
	return Tokens.front().front();
}

void Parser::logError(std::string error, int line){
	if (LOG) {std::cout<<std::endl<<line<<": "<<error<<std::endl;}
}

void Parser::logMessage(std::string message, int line){
	if (LOG) {std::cout<<std::endl<<"<msg>> "<<line<< ": "<<message;}
}

bool Parser::isEOL(bool remove){
	logMessage("executing is EOL", 0);
	bool output = (Tokens.front().size() == 0);
	if (remove && output){
		Tokens.erase(Tokens.begin());
		if (Tokens.front().size() == 0){
			isEOL(true);
		}
	}
	return output;
}

bool Parser::notEOF(){
	return at().token != _EOF;
}

Program Parser::produceAST(const std::vector<std::string>& file){
	std::vector<StmtPtr> body;
	Lexer lexer;
	Tokens = lexer.tokenizeMultiLine(file);
	while (notEOF()){
		body.push_back(parseLineStatement());
		isEOL(true);
	}
	return Program{body};
}

StmtPtr Parser::parseLineStatement(){
	logMessage("parseLineStmt => ", 0);
	if (LOG) {std::cout<<at().token;}
	std::vector<tokenParentElem> Modifiers;
	while(at().token == modifier){
		Modifiers.push_back(eat());
	}
	switch (at().token){
	case _function:
		return std::make_shared<FunctionDeclaration>(parseFunctionDec(Modifiers));
		break;
	case _macro:
		return std::make_shared<MacroDeclaration>(parseMacroDec(Modifiers));
		break;
	case _event:
		return std::make_shared<EventDeclaration>(parseEventDec(Modifiers));
		break;
	case _enum:
		return std::make_shared<EnumDeclaration>(parseEnumDec(Modifiers));
		break;
	case _struct:
		return std::make_shared<StructDeclaration>(parseStructDec(Modifiers));
		break;
	case var:
		return std::make_shared<VarDeclaration>(parseVarDec(Modifiers));
		break;
	default:
		return parseExpr();
	}
}

void Parser::PushBody(std::vector<StmtPtr>& bodyref){
	int bracCounter = 0;
	expect(openBrac, "Expected brace");
	eat();
	isEOL(true);
	while(notEOF() && bracCounter >= 0){
		if (at().token == openBrac){
			bracCounter++;
			eat();
		} else if (at().token == closeBrac) {
			bracCounter--;
			eat();
		} else if (bracCounter>=0){
			bodyref.push_back(parseLineStatement());
		}
		isEOL(true);
	}
}

FunctionDeclaration Parser::parseFunctionDec(std::vector<tokenParentElem> Modifiers){
	logMessage("parseFuncDec", 0);
	eat();
	FunctionDeclaration declaration;
	for (int i=0; i<Modifiers.size(); i++){
		if (Modifiers[i].subclass == "public"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPublic = true;
			}
			if (declaration.isInstant || declaration.isAsync){logError("Private/Public should be before instant/async", 0);}
		} else if (Modifiers[i].subclass == "private"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPrivate = true;
			}
			if (declaration.isInstant || declaration.isAsync){logError("Private/Public should be before instant/async", 0);}
		} else if (Modifiers[i].subclass == "instant" || Modifiers[i].subclass == "async"){
			if (declaration.isInstant || declaration.isAsync){
				logError("Already instant/async", 0);
			} else {
				if (declaration.isInstant){
					declaration.isInstant = true;
				} else if (declaration.isAsync){
					declaration.isAsync = true;
				}
			}
		} else {
			logError("Func has unexpected flags", 0);
		}
	}
	declaration.name = expect(other, "there is no name").value;
	eat();
	std::vector<Param> Params = parseParams();
	PushBody(declaration.body);
	logMessage("EndParseFuncDec", 0);
	return declaration;
}

EventDeclaration Parser::parseEventDec(std::vector<tokenParentElem> Modifiers){
	logMessage("parseEventDec", 0);
	eat();
	EventDeclaration declaration;
	for (int i=0; i<Modifiers.size(); i++){
		if (Modifiers[i].subclass == "public"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPublic = true;
			}
		} else if (Modifiers[i].subclass == "private"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPrivate = true;
			}
		} else {
			logError("Var has unexpected flags", 0);
		}
	}
	declaration.name = expect(other, "there is no name").value;
	eat();
	std::vector<Param> Params = parseParams();
	PushBody(declaration.body);
	logMessage("EndParseEventDec", 0);
	return declaration;
}

MacroDeclaration Parser::parseMacroDec(std::vector<tokenParentElem> Modifiers){
	logMessage("parseMacroDec", 0);
	eat();
	MacroDeclaration declaration;
	for (int i=0; i<Modifiers.size(); i++){
		if (Modifiers[i].subclass == "public"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPublic = true;
			}
			if (declaration.isComplex){logError("Private/Public should be before complex", 0);}
		} else if (Modifiers[i].subclass == "private"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPrivate = true;
			}
			if (declaration.isComplex){logError("Private/Public should be before complex", 0);}
		} else if (Modifiers[i].subclass == "complex"){
			if (declaration.isComplex){
				logError("Already complex", 0);
			} else {
				declaration.isComplex = true;
			}
		} else {
			logError("Var has unexpected flags", 0);
		}
	}
	declaration.name = expect(other, "there is no name").value;
	eat();
	std::vector<Param> Params = parseParams();
	PushBody(declaration.body);
	logMessage("EndParseMacroDec", 0);
	return declaration;
}

EnumDeclaration Parser::parseEnumDec(std::vector<tokenParentElem> Modifiers){
	logMessage("parseEnumDec", 0);
	eat();
	EnumDeclaration declaration;
	for (int i=0; i<Modifiers.size(); i++){
		if (Modifiers[i].subclass == "public"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPublic = true;
			}
		} else if (Modifiers[i].subclass == "private"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPrivate = true;
			}
		} else {
			logError("Var has unexpected flags", 0);
		}
	}
	declaration.name = expect(other, "there is no name").value;
	eat();
	expect(openBrac, "Expected brace");
	eat();
	isEOL(true);
	while(notEOF() && at().token != closeBrac){
		StmtPtr currentptr = parseLineStatement();
		if (std::shared_ptr<EnumDeclaration> enumPtr = std::dynamic_pointer_cast<EnumDeclaration>(currentptr)){
			EnumDeclaration& currentvalue = *enumPtr;
			declaration.values.push_back(currentvalue.name);
		} else {
			logError("Enum syntax is wrong", 0);
		}
		isEOL(true);
	}
	logMessage("EndParseEnumDec", 0);
	return declaration;
}

StructDeclaration Parser::parseStructDec(std::vector<tokenParentElem> Modifiers){ //todo
	logMessage("parseEventDec", 0);
	eat();
	StructDeclaration declaration;
	for (int i=0; i<Modifiers.size(); i++){
		if (Modifiers[i].subclass == "public"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPublic = true;
			}
		} else if (Modifiers[i].subclass == "private"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPrivate = true;
			}
		} else {
			logError("Var has unexpected flags", 0);
		}
	}
	
	return declaration;
}

VarDeclaration Parser::parseVarDec(std::vector<tokenParentElem> Modifiers){
	logMessage("parseVarDec", 0);
	eat();
	VarDeclaration declaration;
	for (int i=0; i<Modifiers.size(); i++){
		if (Modifiers[i].subclass == "const"){
			if (declaration.isConst){
				logError("Already const", 0);
			} else {
				declaration.isConst = true;
			}
		} else if (Modifiers[i].subclass == "public"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPublic = true;
			}
			if (declaration.isConst){logError("Private/Public should be before const", 0);}
		} else if (Modifiers[i].subclass == "private"){
			if (declaration.isPublic || declaration.isPrivate){
				logError("Already public/private", 0);
			} else {
				declaration.isPrivate = true;
			}
			if (declaration.isConst){logError("Private/Public should be before const", 0);}
		} else {
			logError("Var has unexpected flags", 0);
		}
	}
	declaration.identifier = expect(other, "there is no name").value;
	eat();
	expect(equals, "there is no equals");
	eat();
	logMessage("Val:", 0);
	declaration.value = parseExpr();
	return(declaration); 
}

std::vector<Param> Parser::parseParams(){
	logMessage("parseParams", 0);
	std::vector<Param> output;
	std::string dataclass;
	std::string name;
	ExprPtr defaultVal;
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
	eat();
	return output;
}

ExprPtr Parser::parseExpr(){
	logMessage("parseExpr", 0);
	return parseAssignmentExpr();
}

ExprPtr Parser::parseAssignmentExpr(){
	logMessage("parseAssign", 0);
	ExprPtr left = parseObjectExpr();
	if(at().token == equals){
		eat();
		ExprPtr val = parseExpr();
		AssignmentExpr ae;
		ae.identifier = left;
		ae.value = val;
		return std::make_shared<AssignmentExpr>(ae);
	}
	return left;
}

ExprPtr Parser::parseObjectExpr(){
	logMessage("parseObjExpr", 0);
	return parseAdditiveExpr();
}

ExprPtr Parser::parseAdditiveExpr() {
    logMessage("parseAdd", 0);
    ExprPtr left = parseMultiplicataveExpr();
    std::shared_ptr<BinaryExpr> leftbe;
    int index = 0;
    while (at().subclass == "+" || at().subclass == "-") {
        std::string op = eat().subclass; //operator
        ExprPtr right = parseMultiplicataveExpr();
        if (index == 0) {
            leftbe = std::make_shared<BinaryExpr>(left, right, op);
        } else {
            leftbe = std::make_shared<BinaryExpr>(leftbe, right, op);
        }
        index++;
    }
    return (index == 0 ? left : leftbe);
}

ExprPtr Parser::parseMultiplicataveExpr() {
    logMessage("parseMult", 0);
    ExprPtr left = parseCallMemberExpr();
    std::shared_ptr<BinaryExpr> leftbe;
    int index = 0;
    while (at().subclass == "*" || at().subclass == "/" || at().subclass == "%") {
        std::string op = eat().subclass; //operator
        ExprPtr right = parseCallMemberExpr();
        if (index == 0) {
            leftbe = std::make_shared<BinaryExpr>(left, right, op);
        } else {
            leftbe = std::make_shared<BinaryExpr>(leftbe, right, op);
        }
        index++;
    }
    return (index == 0 ? left : leftbe);
}

ExprPtr Parser::parseCallMemberExpr(){
	logMessage("parseCallMemb", 0);
	return parseCallExpr();
}

ExprPtr Parser::parseCallExpr(){
	logMessage("parseCalLExpr", 0);
	return parsePrimaryExpr();
}

ExprPtr Parser::parsePrimaryExpr(){
	logMessage("parsePrimExpr", 0);
	switch (at().token) {
	case other:{
		std::string val = at().value;
		eat();
		return std::make_shared<Identifier>(Identifier{val});
		break;}
	case dataValue:{
		std::string val;
		if (at().subclass == "int"){
			val = at().value;
			eat();
			//logMessage("Int>" + at().value, 0);
			return std::make_shared<IntLiteral>(IntLiteral{std::stoi(val)});
		} else if (at().subclass == "float"){
			val = at().value;
			eat();
			return std::make_shared<FloatLiteral>(FloatLiteral{std::stof(val)});
		} else {
			eat();
			logError("No recognized type of val", 0); 
		}
		break;}
	case openParen:{
		eat();
		ExprPtr value = parseExpr();
		expect(closeParen, "Expect close paren");
		eat();
		return value;
		break;}
	default:
		logError("No type", 0);
		if (LOG) {std::cout<<at().token<<"->"<<at().subclass<<"->"<<at().value;}
		eat();
		throw std::runtime_error("Non recognized token (primary)");
	}
	return std::make_shared<Expr>();
}