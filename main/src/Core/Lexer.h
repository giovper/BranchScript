#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

enum tokenParent {
    dataValue, //0
    dataClass,
    binaryOperator,
    openParen,
    closeParen,
    openBrac, //5
    closeBrac,
    openSq,
    closeSq,
    quotMarks,
    var, //10
    condition,
    negation,
    equals,
    _enum,
    _struct, //15
    _class,
    include,
    as,
    other,
    _function, //20
    callFunction,
    returnExpr,
    extends,
    _event,
    _macro,//25
    modifier,
    _EOF, 
    comma,
    dot, //29
};

struct tokenParentElem {
    tokenParentElem() = default;
	tokenParent token;
	std::string subclass;
	std::string value;
    tokenParentElem(tokenParent t, std::string s, std::string v);
};
struct tokenizeLineOutput {
	int additive;
	std::vector<tokenParentElem> tokens;
    tokenizeLineOutput(int a, std::vector<tokenParentElem> t);
};

class Lexer {
public:
    static std::map<std::string, tokenParent> KEYWORDS;
    std::vector<std::vector<tokenParentElem>> tokenizeMultiLine(const std::vector<std::string>& file);
    tokenizeLineOutput tokenizeSingleLine(int index, const std::vector<std::string>& file);
    tokenParentElem Token(tokenParent token, std::string subclass, std::string value);
};

#endif