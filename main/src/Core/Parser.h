#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <memory>
#include "AST.h"
#include "Lexer.h"

const bool LOG = true;

class Parser {
public:
    Program produceAST(const std::vector<std::string>& file);

    StmtPtr parseLineStatement();
    void PushBody(std::vector<StmtPtr>& bodyref);
    FunctionDeclaration parseFunctionDec(std::vector<tokenParentElem> Modifiers);
    EventDeclaration parseEventDec(std::vector<tokenParentElem> Modifiers);
    MacroDeclaration parseMacroDec(std::vector<tokenParentElem> Modifiers);
    EnumDeclaration parseEnumDec(std::vector<tokenParentElem> Modifiers);
    StructDeclaration parseStructDec(std::vector<tokenParentElem> Modifiers);
    VarDeclaration parseVarDec(std::vector<tokenParentElem> Modifiers);
    ExprPtr parseExpr();
    std::vector<Param> parseParams();
    void logError(std::string error, int line);
    void logMessage(std::string message, int line);
    ExprPtr parseAssignmentExpr();
    ExprPtr parseObjectExpr();
    ExprPtr parseAdditiveExpr();
    ExprPtr parseMultiplicataveExpr();
    ExprPtr parseCallMemberExpr();
    ExprPtr parseCallExpr();
    ExprPtr parsePrimaryExpr();

private:
    tokenParentElem eat();
    bool eatline();
    tokenParentElem expect(tokenParent expected, std::string message);
    tokenParentElem at();
    bool isEOL(bool remove);
    bool notEOF();

    std::vector<std::vector<tokenParentElem>> Tokens;
};

#endif // PARSER_H
