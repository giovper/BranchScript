#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <memory>  // Aggiungi per std::unique_ptr
#include "Lexer.h"
#include "AST.h"

class Parser {
public:
    Parser();
    ~Parser();

    std::unique_ptr<Program> produceAST(const std::vector<std::string>& file);  // Modifica
    std::unique_ptr<Stmt> parseLineStatement();  // Modifica
    std::unique_ptr<FunctionDeclaration> parseFunctionDec(std::vector<tokenParentElem> Modifiers);  // Modifica
    std::unique_ptr<EventDeclaration> parseEventDec(std::vector<tokenParentElem> Modifiers);  // Modifica
    std::unique_ptr<MacroDeclaration> parseMacroDec(std::vector<tokenParentElem> Modifiers);  // Modifica
    std::unique_ptr<EnumDeclaration> parseEnumDec(std::vector<tokenParentElem> Modifiers);  // Modifica
    std::unique_ptr<StructDeclaration> parseStructDec(std::vector<tokenParentElem> Modifiers);  // Modifica
    std::unique_ptr<VarDeclaration> parseVarDec(std::vector<tokenParentElem> Modifiers);  // Modifica
    std::vector<std::unique_ptr<Param>> parseParams();  // Modifica
    std::unique_ptr<Expr> parseExpr();  // Modifica
    std::unique_ptr<Expr> parseAssignmentExpr();  // Modifica
    std::unique_ptr<Expr> parseObjectExpr();  // Modifica
    std::unique_ptr<Expr> parseAdditiveExpr();  // Modifica
    std::unique_ptr<Expr> parseMultiplicitaveExpr();  // Modifica
    std::unique_ptr<Expr> parseCallMemberExpr();  // Modifica
    std::unique_ptr<Expr> parseCallExpr();  // Modifica
    std::unique_ptr<Expr> parsePrimaryExpr();  // Modifica

private:
    std::vector<std::vector<tokenParentElem>> Tokens;
    tokenParentElem eat(bool removeIfEmpty = false);
    tokenParentElem eat();
    tokenParentElem expect(tokenParent expected, std::string message);
    tokenParentElem at();
    void logError(std::string error, int line);
    void logMessage(std::string message, int line);
    bool isEOL(bool remove = false);
    bool notEOF();
};

#endif // PARSER_H
