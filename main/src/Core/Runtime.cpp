// Runtime.cpp
#include "Runtime.h"

Runtime::Runtime(){
	std::string exePath = Utilities::getExePath();
	startingPath = exePath.substr(0, (exePath.find_last_of("/\\")));
}

void Runtime::run(const std::vector<std::string>& file) {
	Parser parser;
	EnvironmentPtr globalenv = std::make_shared<Environment>();
	globalenv->declareVar("x", std::make_shared<IntVal>(69), false);
	Program ast = parser.produceAST(file);
	RuntimeValPtr program = evaluate(std::make_shared<Program>(ast), globalenv);
	std::cout<<"\n"<<static_cast<int>(program->getType())<<"\n";
	std::shared_ptr<IntVal> child = std::dynamic_pointer_cast<IntVal>(program);
	std::cout<<child->value;

}

void Runtime::ast(const std::vector<std::string>& file) {
	Parser parser;
	Lexer lexer;
	std::vector<std::vector<tokenParentElem>> l = lexer.tokenizeMultiLine(file);
	std::cout<<"Lexer: ";
	for (int i=0; i<l.size(); i++){
		std::vector<tokenParentElem> li = l[i];
		std::cout<<"\nNext\n";
		for (int j=0; j<li.size(); j++){
			std::cout<<li[j].token<<"->"<<li[j].subclass<<"->"<<li[j].value<<"\n";
		}
	}
	std::cout<<"\nParser\n";
	Program p = parser.produceAST(file);
	if (LOG) {p.print();}
}