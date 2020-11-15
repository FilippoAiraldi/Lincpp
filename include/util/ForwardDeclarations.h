#pragma once

namespace Lincpp
{
    namespace internal
    {
        // structure whose specializations contains type infos on classes that provide one
        template <typename T>
        struct traits;
    } // namespace internal

    // base container type for an Enumerable. Can be easily changed from here. Vector's reserve method usages must be deleted if changed
    // TODO: make the default container smart.
    // If the element it contains are big -> list, if small -> vector. Any advantages?
    template <typename T>
    using default_container = std::vector<T>;

    template <typename Derived>
    struct Queriable;

    template <typename TElement, typename TIterator>
    struct Enumerable;

    template <typename TElement, typename TSource, typename TReturn>
    struct CastClause;

    template <typename TElement, typename TSource, typename TFunc, typename TReturn>
    struct SelectClause;
} // namespace Lincpp
