#pragma once

namespace Lincpp
{
    namespace internal
    {
        // traits info specialization for SelectClause
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
        // friend struct Queriable<SelectClause<TElement, TSource, TFunc, TReturn>>;

    public:
        SelectClause(const TSource &source, TFunc selector) : range(source), func(selector)
        {
            CHECK_QUERIABLE_BASE(TSource);
            CHECK_SOURCE_CONTENT(TSource, TElement);
            CHECK_FUNC(TFunc, TElement, TReturn);
        }

    public:
        size_type Size() const { return this->range.Size(); }
        TReturn ElementAt(size_type i) const { return this->func(this->range.ElementAt(i)); }

    private:
        const TSource &range;
        TFunc func;
    };
} // namespace Lincpp
