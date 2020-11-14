#pragma once

namespace Lincpp
{
    template <typename Derived>
    struct Queriable
    {
    private:
        typedef typename internal::traits<Derived>::Element TElement;
        typedef typename internal::traits<Derived>::Size TSize;

    protected:
        Derived &derived() { return *static_cast<Derived *>(this); }
        const Derived &derived() const { return *static_cast<const Derived *>(this); }

    public:
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

        template <typename TPredicate>
        bool Empty(TPredicate predicate) const { return !this->Any<TPredicate>(predicate); }
        bool Empty() const { return !this->Any(); }

        template <typename TFunc, typename TReturn = typename std::result_of_t<TFunc(const TElement &)>>
        SelectClause<TElement, Derived, TFunc, TReturn> Select(TFunc selector) const
        {
            return SelectClause<TElement, Derived, TFunc, TReturn>(this->derived(), selector);
        }

        // TODO: std::vector<TElement> ToVector() { this->derived().ToVector(); }

    public:
        // methods that all derived must implement
        TSize Count() const { return this->derived().Count(); }
        const TElement ElementAt(TSize i) const { return this->derived().ElementAt(i); }
    };
} // namespace Lincpp
