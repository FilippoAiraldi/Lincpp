#pragma once

namespace Lincpp
{
    namespace internal
    {
        template <typename TSource, typename TElement, typename TFunc, typename TReturn>
        struct traits<SelectClause<TElement, TSource, TFunc, TReturn>>
        {
            typedef TReturn Element;
            typedef typename default_container<TReturn>::size_type Size;
        };
    } // namespace internal

    template <typename TElement, typename TSource, typename TFunc, typename TReturn>
    struct SelectClause : public Queriable<SelectClause<TElement, TSource, TFunc, TReturn>>
    {
    public:
        typedef typename TSource::size_type size_type;
        friend struct Queriable<SelectClause<TElement, TSource, TFunc, TReturn>>;

    public:
        SelectClause(TSource &source, TFunc selector) : range(source), func(selector)
        {
            CHECK_QUERIABLE_BASE(TSource);
            CHECK_SOURCE_CONTENT(TSource, TElement, true);
            CHECK_FUNC(TFunc, TElement, TReturn);
        }

    public:
        inline size_type Size() const { return this->range.Size(); }
        inline TReturn ElementAt(size_type i) const { return this->func(this->range.ElementAt(i)); }

        inline void RequestCopyOriginalData() const { this->range.RequestCopyOriginalData(); }

    private:
        TSource &range;
        TFunc func;
    };
} // namespace Lincpp
