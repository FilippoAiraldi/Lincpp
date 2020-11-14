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
            typedef typename default_container<TReturn>::size_type size_type;
        };
    } // namespace internal

    template <typename TElement, typename TSource, typename TFunc, typename TReturn>
    struct SelectClause : public Queriable<SelectClause<TElement, TSource, TFunc, TReturn>>
    {
    public:
        // these allow to instantiate an Enumerable from another a SelectClause
        typedef TReturn value_type;
        typedef typename TSource::size_type size_type;

    public:
        SelectClause(TSource source, TFunc selector) : range(source), func(selector)
        {
            static_assert(std::is_base_of_v<Queriable<TSource>, TSource>, "Clause can only quey from Lincpp classes.");
            static_assert(std::is_invocable_v<TFunc, TElement>, "Clause selector function must be invocable with TElement as argument.");
            static_assert(std::is_same_v<typename TSource::value_type, TElement>, "Clause TSource must contain TElement as value type.");
            static_assert(std::is_same_v<typename std::result_of<TFunc(const TElement &)>::type, TReturn>, "Clause select function must have TResource as return type.");
        }

    public:
        size_type Count() const { return this->range.Count(); }
        const TReturn ElementAt(size_type i) const { return this->func(this->range.ElementAt(i)); }

    private:
        TSource range; // an enumerable or another clause (in other words, a query)
        TFunc func;
    };
} // namespace Lincpp
