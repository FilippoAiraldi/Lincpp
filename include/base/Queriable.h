#pragma once

namespace Lincpp
{
    template <typename Derived>
    struct Queriable
    {
    private:
        // all derived structs must register these traits
        // typedef typename internal::traits<Derived>::Iterator DerivedIterator;
        typedef typename internal::traits<Derived>::Element TElement;

    protected:
        inline Derived &derived() { return *static_cast<Derived *>(this); }
        inline const Derived &derived() const { return *static_cast<const Derived *>(this); }

        // methods that all derived structs must implement
        // inline DerivedIterator cbegin() const { return static_cast<DerivedIterator>(this->derived().cbegin()); }
        // inline DerivedIterator cend() const { return static_cast<DerivedIterator>(this->derived().cend()); }

    public:
        // template <typename TPredicate>
        // bool All(TPredicate predicate) const
        // {
        //     CHECK_PREDICATE(TPredicate, TElement);
        //     DerivedIterator end = this->cend();
        //     for (DerivedIterator it = this->cbegin(); it != end; it++)
        //         if (!predicate(*it))
        //             return false;
        //     return true;
        // }

        // TElement ElementAt(std::size_t i) const requires std::indirectly_readable<DerivedIterator> &&std::incrementable<DerivedIterator>
        // {
        //     return *this->cbegin().Move(this->cbegin(), this->cend(), i);
        // }

        constexpr std::size_t Count() const { return std::distance(this->cbegin(), this->cend()); }
    };
} // namespace Lincpp

// namespace Lincpp
// {
//     template <typename Derived>
//     struct Queriable
//     {
//     private:
//         typedef typename internal::traits<Derived>::Element TElement;
//         typedef typename internal::traits<Derived>::Size TSize;

//     protected:
//         inline Derived &derived() { return *static_cast<Derived *>(this); }
//         inline const Derived &derived() const { return *static_cast<const Derived *>(this); }

//     public:
//         template <typename TPredicate>
//         bool All(TPredicate predicate) const
//         {
//             CHECK_PREDICATE(TPredicate, TElement);
//             TSize L = this->Size();
//             for (TSize i = 0; i < L; ++i)
//                 if (!predicate(this->ElementAt(i)))
//                     return false;
//             return true;
//         }

//         template <typename TPredicate>
//         bool Any(TPredicate predicate) const
//         {
//             CHECK_PREDICATE(TPredicate, TElement);
//             TSize L = this->Size();
//             for (TSize i = 0; i < L; ++i)
//                 if (predicate(this->ElementAt(i)))
//                     return true;
//             return false;
//         }
//         inline bool Any() const { return this->derived().Size() != 0; }

//         // TODO: make this a clause
//         // Enumerable<TElement> Append(const TElement &element) const
//         // {
//         //     std::list<TElement> tmp = this->ToList();
//         //     tmp.push_back(element);
//         //     return Enumerable<TElement>(tmp);
//         // }

//         double Average() const requires internal::Averageable<TElement>
//         {
//             TSize L = this->Size();
//             if (L == 0)
//                 throw std::range_error("sequence contains no element.");

//             if constexpr (std::is_integral_v<TElement> || std::is_floating_point_v<TElement>)
//             {
//                 double avg = this->ElementAt(0);
//                 for (TSize i = 1; i < L; ++i)
//                     avg = (avg * (double)i + this->ElementAt(i)) / (double)(i + 1);
//                 return avg;
//             }
//             else
//             {
//                 TElement tot = this->ElementAt(0);
//                 for (TSize i = 1; i < L; ++i)
//                     tot = tot + ElementAt(i);
//                 return tot / L;
//             }
//         }

//         // TODO: Cast

//         // TODO: make this a clause
//         // Enumerable<TElement> Concat(const Enumerable<TElement> &other) const
//         // {
//         //     TSize L1 = this->Size();
//         //     TSize L2 = other.Size();
//         //     Enumerable<TElement> res;
//         //     res.data.reserve(L1 + L2);
//         //     for (TSize i = 0; i < L1; ++i)
//         //         res.data.push_back(this->ElementAt(i));
//         //     for (TSize i = 0; i < L2; ++i)
//         //         res.data.push_back(other.ElementAt(i));
//         //     return res;
//         // }

//         template <typename TPredicate>
//         TSize Count(TPredicate predicate) const
//         {
//             CHECK_PREDICATE(TPredicate, TElement);
//             TSize cnt = 0;
//             TSize L = this->Count();
//             for (TSize i = 0; i < L; ++i)
//                 if (predicate(this->ElementAt(i)))
//                     ++cnt;
//             return cnt;
//         }
//         inline TSize Count() const { return this->Size(); }

//         template <typename TPredicate>
//         bool Empty(TPredicate predicate) const
//         {
//             return !this->Any<TPredicate>(predicate);
//         }
//         inline bool Empty() const { return !this->Any(); }

//         // TODO: make this a clause
//         // Enumerable<TElement> DefaultIfEmpty(TElement defaultValue) const
//         // {
//         //     Enumerable<TElement> res;
//         //     TSize L = this->Count();
//         //     if (L != 0)
//         //     {
//         //         res.data.reserve(L);
//         //         for (TSize i = 0; i < L; ++i)
//         //             res.data.push_back(this->ElementAt(i));
//         //     }
//         //     else
//         //         res.data.push_back(defaultValue);

//         //     return res;
//         // }

//         template <typename TFunc, typename TReturn = typename std::result_of_t<TFunc(const TElement &)>>
//         SelectClause<TElement, Derived, TFunc, TReturn> Select(TFunc selector)
//         {
//             return SelectClause<TElement, Derived, TFunc, TReturn>(this->derived(), selector);
//         }

//         std::unique_ptr<TElement[]> ToArray() const
//         {
//             this->RequestCopyOriginalData();
//             TSize L = this->Size();
//             auto p = std::make_unique<TElement[]>(L);
//             for (TSize i = 0; i < L; ++i)
//                 p[i] = this->ElementAt(i);
//             return p;
//         }

//         std::list<TElement> ToList() const
//         {
//             this->RequestCopyOriginalData();
//             std::list<TElement> l;
//             TSize L = this->Size();
//             for (TSize i = 0; i < L; ++i)
//                 l.push_back(this->ElementAt(i));
//             return l;
//         }

//         std::vector<TElement> ToVector() const
//         {
//             this->RequestCopyOriginalData();
//             TSize L = this->Size();
//             std::vector<TElement> v(L);
//             for (TSize i = 0; i < L; ++i)
//                 v[i] = this->ElementAt(i);
//             return v;
//         }

//     public:
//         // methods that all derived structs must implement
//         inline TSize Size() const { return this->derived().Size(); }
//         inline TElement ElementAt(TSize i) const { return this->derived().ElementAt(i); }

//         inline void RequestCopyOriginalData() const { return this->derived().RequestCopyOriginalData(); }
//     };
// } // namespace Lincpp
