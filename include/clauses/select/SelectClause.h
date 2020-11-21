// #pragma once

// the idea is the following:
/*
in each clause that needs it, the clause can give a specialization to the AnyIterator to manipulate
its return type or whether it should return at all.
For example, SelectClause should manipulate its return type by forcing it through its lambda.
WhereClause should not return if the iterator does not meet expectation, and instead keep looping
*/

// namespace Lincpp
// {
//     namespace internal
//     {
//         template <typename TSource, typename TElement, typename TFunc, typename TReturn>
//         struct traits<SelectClause<TElement, TSource, TFunc, TReturn>>
//         {
//             typedef TReturn Element;
//             typedef typename default_container<TReturn>::size_type Size;
//         };
//     } // namespace internal

//     template <typename TElement, typename TSource, typename TFunc, typename TReturn>
//     struct SelectClause : public Queriable<SelectClause<TElement, TSource, TFunc, TReturn>>
//     {
//     public:
//         typedef typename TSource::size_type size_type;
//         friend struct Queriable<SelectClause<TElement, TSource, TFunc, TReturn>>;

//     public:
//         // FIXME: instead of a generic TSource, should it not be a Queriable ??
//         SelectClause(TSource &source, TFunc selector) : range(source), func(selector)
//         {
//             CHECK_QUERIABLE_BASE(TSource);
//             CHECK_SOURCE_CONTENT(TSource, TElement, true);
//             CHECK_FUNC(TFunc, TElement, TReturn);
//         }

//     public:
//         inline size_type Size() const { return this->range.Size(); }
//         inline TReturn ElementAt(size_type i) const { return this->func(this->range.ElementAt(i)); }

//         inline void RequestCopyOriginalData() const { this->range.RequestCopyOriginalData(); }

//     private:
//         TSource &range;
//         TFunc func;
//     };
// } // namespace Lincpp
