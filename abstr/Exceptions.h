#pragma once

#include <stdexcept>

namespace NTree {
    class SyntaxError : public std::runtime_error {
        using std::runtime_error::runtime_error;
    public:
        explicit SyntaxError(const std::string& message) : runtime_error(message) {
        }
    };
}