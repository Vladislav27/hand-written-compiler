#pragma once

#include "Common.h"

#include <abstr/Exceptions.h>

namespace NSymbolTable {
    class SymbolTableException : public NTree::SyntaxError {
    public:
        explicit SymbolTableException(const std::string& message) : NTree::SyntaxError(message) {
        }
    };

    class RedefinitionException : public SymbolTableException {
    public:
        RedefinitionException(const  NTree::Location& currentLoc
            , const NTree::Symbol* currentId
            , const NTree::Location& shadowedLoc)
            : SymbolTableException("Redefinition: " + currentId->String()
                                   + " on " + currentLoc.ToString() + " shadows " + shadowedLoc.ToString()) {}
    };

    class CyclicDependencyException : public SymbolTableException {
    public:
        CyclicDependencyException(const NTree::Location& loc, const NTree::Symbol* id)
            : SymbolTableException("Cyclic dependency: " + id->String() + " on " + loc.ToString()) {}
    };

    class NonDeclaredSymbolException : public SymbolTableException {
    public:
        NonDeclaredSymbolException(const NTree::Location& loc, const NTree::Symbol* id)
            : SymbolTableException("Identifier is not declared: " + id->String() + " on " + loc.ToString()) {}
    };
}