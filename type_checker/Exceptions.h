#pragma once

#include <abstr/Exceptions.h>
#include <table_of_symbols/TypeInfo.h>
#include <abstr/Location.h>

namespace NTypeChecker {
    class IllegalTypeException: public NTree::SyntaxError {
    public:
        using NTree::SyntaxError::SyntaxError;

        IllegalTypeException(const NTree::Location &loc
            , const NSymbolTable::TypeInfo &found
            , const NSymbolTable::TypeInfo &expected)
            : SyntaxError("Error: expected " + expected.ToString() + ", found " + found.ToString()
                          + " on " + loc.ToString()) {
        }

        IllegalTypeException(const NTree::Location &loc
            , const NSymbolTable::TypeInfo &found
            /* expected non POD type */)
            : SyntaxError("Error: expected object of some class, found " + found.ToString()
                          + " on " + loc.ToString()) {
        }
    };

    class BadArgumentsException: public NTree::SyntaxError {
    public:
        using NTree::SyntaxError::SyntaxError;
        explicit BadArgumentsException(const NTree::Location &loc)
            : SyntaxError("Error: bad arguments on " + loc.ToString()) {
        }
    };

    class PrivateAccessException: public NTree::SyntaxError {
    public:
        using NTree::SyntaxError::SyntaxError;
        PrivateAccessException(const NTree::Location &loc
                , const NTree::Symbol* methodId
                , const NTree::Symbol* classId)
                : SyntaxError("Unexpected access to private method "
                              + methodId->String() + " of class "
                              + classId->String() + " on "
                              + loc.ToString()) {
        }
    };
}
