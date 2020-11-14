#pragma once

namespace Lincpp
{
    template <typename Derived>
    struct Queriable
    {
    private:
        typedef typename internal::traits<Derived>::Element TElement;
        typedef typename internal::traits<Derived>::size_type size_type;

    protected:
        Derived &derived() { return *static_cast<Derived *>(this); }
        const Derived &derived() const { return *static_cast<const Derived *>(this); }

    public:
        // TODO: Any() and Any(predicate)
        bool Any() const { return this->derived().Count() != 0; }

        template <typename TPredicate>
        bool Any(TPredicate predicate) const 
        {
            static_assert(std::is_invocable_v<TPredicate, TElement>, "Predicate must be invocable with TElement as argument.");
            static_assert(std::is_same_v<typename std::result_of_t<TPredicate(const TElement &)>, bool>, "Predicate must have bool as return type.");

            Derived derived = this->derived();
            size_type L = derived.Count();
            for (size_type i = 0; i < L; ++i)
                if (predicate(derived.ElementAt(i)))
                    return true;
            return false;
        }

        bool Empty() const { return !this->Any(); }

        template <typename TFunc, typename TReturn = typename std::result_of_t<TFunc(const TElement &)>>
        SelectClause<TElement, Derived, TFunc, TReturn> Select(TFunc selector) const
        {
            return SelectClause<TElement, Derived, TFunc, TReturn>(this->derived(), selector);
        }

        // TODO: std::vector<TElement> ToVector() { this->derived().ToVector(); }

    public:
        // methods that all derived must implement
        size_type Count() const { return this->derived().Count(); }
        const TElement ElementAt(size_type i) const { return this->derived().ElementAt(i); }
    };
} // namespace Lincpp
