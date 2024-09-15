#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "../../AST.h"
#include "../Environment.h"
#include "../Interpreter.h"
#include "../Values.h"
#include <cmath>

RuntimeValPtr evalBinaryExpr (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalNumericBinaryExpr (RuntimeValPtr left, RuntimeValPtr right, std::string op, EnvironmentPtr env);
RuntimeValPtr evalIdentifier (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalAssignment (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalObjectExpression (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalCallExpression (StmtPtr node, EnvironmentPtr env);
RuntimeValPtr evalProgram (StmtPtr node, EnvironmentPtr env);

#endif