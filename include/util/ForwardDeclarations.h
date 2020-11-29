#pragma once

namespace Lincpp
{
    namespace internal
    {
        template <typename T>
        struct traits;
    } // namespace internal

    template <typename Derived>
    struct Iterator;

    template <typename It, typename TFunc, typename TReturn>
    struct SelectIterator;

    template <typename It, typename TPred>
    struct WhereIterator;

    template <typename TIterator>
    struct Queriable;

    template <typename TIterator>
    struct Orderable;
} // namespace Lincpp
