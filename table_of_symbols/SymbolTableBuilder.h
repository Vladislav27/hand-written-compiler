#pragma once

#include "SymbolTable.h"

#include "abstr/tree/Common.h"

#include "abstr/tree/Class.h"
#include "abstr/tree/Program.h"

#include "abstr/tree/MethodDeclaration.h"
#include "abstr/tree/VarDeclaration.h"

#include "abstr/tree/Statement.h"
#include "abstr/Expression.h"

namespace NSymbolTable {
    SymbolTable BuildSymbolTable(const NSyntaxTree::Program &program);
}
