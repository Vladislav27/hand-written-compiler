#pragma once

#include "Common.h"

#include <abstr/Exceptions.h>

namespace NSymbolTable {
    class SymbolTableException : public NSyntaxTree::SyntaxError {
    public:
        SymbolTableException(const std::string& message) : NSyntaxTree::SyntaxError(message) {
        }
    };

    class RedefinitionException : public SymbolTableException {
    public:
        RedefinitionException(const Location& currentLoc
            , const Symbol* currentId
            , const Location& shadowedLoc)
            : SymbolTableException("Redefinition: " + currentId->String()
                                   + " on " + currentLoc.ToString() + " shadows " + shadowedLoc.ToString()) {}
    };

    class CyclicDependencyException : public SymbolTableException {
    public:
        CyclicDependencyException(const Location& loc, const Symbol* id)
            : SymbolTableException("Cyclic dependency: " + id->String() + " on " + loc.ToString()) {}
    };

    class NonDeclaredSymbolException : public SymbolTableException {
    public:
        NonDeclaredSymbolException(const Location& loc, const Symbol* id)
            : SymbolTableException("Identifier is not declared: " + id->String() + " on " + loc.ToString()) {}
    };
}