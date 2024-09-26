#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "../../AST.h"
#include "../Environment.h"
#include "../Interpreter.h"
#include "../Values.h"
#include <cmath>
#include <windows.h>

RuntimeValPtr evalBinaryExpr (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalNumericBinaryExpr (RuntimeValPtr left, RuntimeValPtr right, std::string op, EnvironmentPtr env);
RuntimeValPtr evalIdentifier (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalObjectExpression (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalCallExpression (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalProgram (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalVarDeclaration (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalAssignmentExpr (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalObjectExpr (StmtPtr node, EnvironmentPtr env);

#endif