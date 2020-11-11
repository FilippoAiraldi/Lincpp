#pragma once

namespace Lincpp
{
    namespace internal
    {
        // structure whose specializations contains type infos on classes that provide one
        template <typename T>
        struct traits;

        // base container type for an Enumerable. Can be easily changed from here
        template <typename T>
        using container = std::vector<T>;
    } // namespace internal

    template <typename TSource, typename TElement, typename TIterator>
    struct Enumerable;
} // namespace Lincpp
