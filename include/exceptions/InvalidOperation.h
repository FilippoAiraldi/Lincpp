#pragma once

namespace Lincpp
{
    struct InvalidOperation : public std::runtime_error
    {
        explicit InvalidOperation(const char *what_arg) : std::runtime_error(what_arg) {}
        InvalidOperation(const InvalidOperation &) = default;
        InvalidOperation(InvalidOperation &&) = default;
        InvalidOperation &operator=(const InvalidOperation &) = default;
        InvalidOperation &operator=(InvalidOperation &&) = default;
    };
} // namespace Lincpp
