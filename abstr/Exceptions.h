#pragma once

#include <stdexcept>

namespace NSyntaxTree {
    class SyntaxError : public std::runtime_error {
        using std::runtime_error::runtime_error;
    public:
        SyntaxError(const std::string& message) : runtime_error(message) {
        }
    };
}