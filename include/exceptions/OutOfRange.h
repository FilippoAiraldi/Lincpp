#pragma once

namespace Lincpp
{
    struct OutOfRange : public std::out_of_range
    {
        explicit OutOfRange(const char *what_arg) : std::out_of_range(what_arg) {}
        OutOfRange(const OutOfRange &) = default;
        OutOfRange(OutOfRange &&) = default;
        OutOfRange &operator=(const OutOfRange &) = default;
        OutOfRange &operator=(OutOfRange &&) = default;
    };
} // namespace Lincpp
