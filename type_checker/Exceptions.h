#pragma once

#include <abstr/Exceptions.h>
#include <table_of_symbols/TypeInfo.h>
#include <abstr/Location.h>

namespace NTypeChecker {
    class IllegalTypeException: public NSyntaxTree::SyntaxError {
    public:
        using NSyntaxTree::SyntaxError::SyntaxError;

        IllegalTypeException(const NUtil::Location &loc
            , const NSymbolTable::TypeInfo &found
            , const NSymbolTable::TypeInfo &expected)
            : SyntaxError("Error: expected " + expected.ToString() + ", found " + found.ToString()
                          + " on " + loc.ToString()) {
        }

        IllegalTypeException(const NUtil::Location &loc
            , const NSymbolTable::TypeInfo &found
            /* expected non POD type */)
            : SyntaxError("Error: expected object of some class, found " + found.ToString()
                          + " on " + loc.ToString()) {
        }
    };

    class BadArgumentsException: public NSyntaxTree::SyntaxError {
    public:
        using NSyntaxTree::SyntaxError::SyntaxError;
        explicit BadArgumentsException(const NUtil::Location &loc)
            : SyntaxError("Error: bad arguments on " + loc.ToString()) {
        }
    };

    class PrivateAccessException: public NSyntaxTree::SyntaxError {
    public:
        using NSyntaxTree::SyntaxError::SyntaxError;
        PrivateAccessException(const NUtil::Location &loc
                , const NSymbolTable::Symbol* methodId
                , const NSymbolTable::Symbol* classId)
                : SyntaxError("Unexpected access to private method "
                              + methodId->String() + " of class "
                              + classId->String() + " on "
                              + loc.ToString()) {
        }
    };
}
