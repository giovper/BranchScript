#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <memory>
#include "AST.h"
#include "Lexer.h"

class Parser {
public:
    Program produceAST(const std::vector<std::string>& file);

    Stmt parseLineStatement();
    FunctionDeclaration parseFunctionDec(std::vector<tokenParentElem> Modifiers);
    EventDeclaration parseEventDec(std::vector<tokenParentElem> Modifiers);
    MacroDeclaration parseMacroDec(std::vector<tokenParentElem> Modifiers);
    EnumDeclaration parseEnumDec(std::vector<tokenParentElem> Modifiers);
    StructDeclaration parseStructDec(std::vector<tokenParentElem> Modifiers);
    VarDeclaration parseVarDec(std::vector<tokenParentElem> Modifiers);
    Expr parseExpr();
    std::vector<Param> parseParams();
    void logError(std::string error, int line);
    void logMessage(std::string message, int line);
    Expr parseAssignmentExpr();
    Expr parseObjectExpr();
    Expr parseAdditiveExpr();
    Expr parseMultiplicitaveExpr();
    Expr parseCallMemberExpr();
    Expr parseCallExpr();
    Expr parsePrimaryExpr();

private:
    tokenParentElem eat();
    tokenParentElem eat(bool removeIfEmpty);
    tokenParentElem expect(tokenParent expected, std::string message);
    tokenParentElem at();
    bool isEOL(bool remove);
    bool notEOF();

    std::vector<std::vector<tokenParentElem>> Tokens;
};

#endif // PARSER_H
