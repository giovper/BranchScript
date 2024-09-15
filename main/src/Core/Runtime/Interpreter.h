#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "../AST.h"
#include "Environment.h"
#include "Values.h"
#include "Eval/Statements.h"
#include "Eval/Expressions.h"

RuntimeValPtr evaluate(StmtPtr node, EnvironmentPtr env);

#endif