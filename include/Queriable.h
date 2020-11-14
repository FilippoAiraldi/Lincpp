#pragma once

namespace Lincpp
{
    template <typename Derived>
    struct Queriable
    {
    public:
        enum class CastType : unsigned char
        {
            Static,
            Dynamic,
            Reinterpreted
        };

    private:
        typedef typename internal::traits<Derived>::Element TElement;
        typedef typename internal::traits<Derived>::Size TSize;

    protected:
        Derived &derived() { return *static_cast<Derived *>(this); }
        const Derived &derived() const { return *static_cast<const Derived *>(this); }

    public:
        template <typename TPredicate>
        bool All(TPredicate predicate) const
        {
            CHECK_PREDICATE(TPredicate, TElement);
            Derived derived = this->derived();
            TSize L = derived.Count();
            for (TSize i = 0; i < L; ++i)
                if (!predicate(derived.ElementAt(i)))
                    return false;
            return true;
        }

        template <typename TPredicate>
        bool Any(TPredicate predicate) const
        {
            CHECK_PREDICATE(TPredicate, TElement);
            Derived derived = this->derived();
            TSize L = derived.Count();
            for (TSize i = 0; i < L; ++i)
                if (predicate(derived.ElementAt(i)))
                    return true;
            return false;
        }
        bool Any() const { return this->derived().Count() != 0; }

        Enumerable<TElement> Append(TElement element) const
        {
            std::list<TElement> tmp = this->ToList();
            tmp.push_back(element);
            return Enumerable<TElement>(tmp);
        }

        // TODO: Average

        // template <typename TOtherElement, CastType Type>
        // Enumerable<TOtherElement> Cast();
        // // {
        // //     std::list<TElement> tmp = this->ToList();
        // //     Enumerable
        // // }

        // template <typename TOtherElement>
        // Enumerable<TOtherElement> Cast<TOtherElement, CastType::Dynamic>()
        // {
        //     std::unique_ptr<TElement[]> tmp = this->ToArray();

        // }

        template <typename TPredicate>
        bool Empty(TPredicate predicate) const
        {
            return !this->Any<TPredicate>(predicate);
        }
        bool Empty() const { return !this->Any(); }

        template <typename TFunc, typename TReturn = typename std::result_of_t<TFunc(const TElement &)>>
        SelectClause<TElement, Derived, TFunc, TReturn> Select(TFunc selector) const
        {
            return SelectClause<TElement, Derived, TFunc, TReturn>(this->derived(), selector);
        }

        std::unique_ptr<TElement[]> ToArray() const
        {
            Derived derived = this->derived();
            TSize L = derived.Count();
            auto p = std::make_unique<TElement[]>(L);
            for (TSize i = 0; i < L; ++i)
                p[i] = derived.ElementAt(i);
            return p;
        }

        std::list<TElement> ToList() const
        {
            std::list<TElement> l;
            Derived derived = this->derived();
            TSize L = derived.Count();
            for (TSize i = 0; i < L; ++i)
                l.push_back(derived.ElementAt(i));
            return l;
        }

        std::vector<TElement> ToVector() const
        {
            Derived derived = this->derived();
            TSize L = derived.Count();
            std::vector<TElement> v(L);
            for (TSize i = 0; i < L; ++i)
                v[i] = derived.ElementAt(i);
            return v;
        }

    public:
        // methods that all derived structs must implement
        TSize Count() const { return this->derived().Count(); }
        const TElement ElementAt(TSize i) const { return this->derived().ElementAt(i); }
    };
} // namespace Lincpp
