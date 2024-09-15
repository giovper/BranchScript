// Runtime.cpp
#include "Runtime.h"
#include "../Utilities/Utilities.h"
#include "Lexer.h"
#include "Parser.h"
#include "Runtime/Interpreter.h"

Runtime::Runtime(){
	std::string exePath = Utilities::getExePath();
	startingPath = exePath.substr(0, (exePath.find_last_of("/\\")));
}

void Runtime::run(const std::vector<std::string>& file) {
	Parser parser;
	EnvironmentPtr globalenv = std::make_shared<Environment>();
	Program program = parser.produceAST(file);
	std::cout<<evaluate(std::make_shared<Program>(program), globalenv);

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
	p.print();
}