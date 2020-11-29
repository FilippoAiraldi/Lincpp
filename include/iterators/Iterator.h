#pragma once

namespace Lincpp
{
    /*
    Each derived class must provide its own copy assignment operator.
        - copy assignment, so that it knows what to copy or not (lambda cannot be copied for example)
        - Clone method
        - its own operators to accomplish the purpose of the derived class
        - traits describing the iterator (category, diff type, value type, reference, pointer, internal iterator type)
        - a forward declaration
    */

    // https://en.cppreference.com/w/cpp/iterator/iterator
    // https://stackoverflow.com/questions/9386266/overloading-the-operator-to-increment-an-iterator

    template <typename Derived>
    struct Iterator
    {
    public:
        typedef typename internal::traits<Derived>::iterator_type It;
        typedef typename internal::traits<Derived>::iterator_category iterator_category;
        typedef typename internal::traits<Derived>::difference_type difference_type;
        typedef typename internal::traits<Derived>::value_type value_type;
        typedef typename internal::traits<Derived>::reference reference;
        typedef typename internal::traits<Derived>::pointer pointer;

    protected:
        static constexpr bool IsForwardIt = std::is_base_of_v<std::forward_iterator_tag, iterator_category>;
        static constexpr bool IsBidirectionalIt = std::is_base_of_v<std::bidirectional_iterator_tag, iterator_category>;
        static constexpr bool IsRandomAccessIt = std::is_base_of_v<std::random_access_iterator_tag, iterator_category>;

        inline Derived &derived() { return *static_cast<Derived *>(this); }
        inline const Derived &derived() const { return *static_cast<const Derived *>(this); }

    public:
        explicit Iterator(It iterator) noexcept : _current(iterator) {}

        inline It &Base() noexcept { return _current; }
        inline const It &Base() const noexcept { return _current; }

        Iterator<Derived> &operator=(const Iterator<Derived> &other) { _current = other._current; };

        // Forward iterator requirements
        pointer operator->() const { return _current.operator->(); }
        value_type operator*() const { return *_current; } // rather than reference
        Derived &operator++() noexcept                     // pre
        {
            static_assert(IsForwardIt, "pre-increment operator: iterator is not a forward.");
            ++_current;
            return *static_cast<Derived *>(this);
        }
        Derived operator++(int) noexcept // post
        {
            static_assert(IsForwardIt, "post-increment operator: iterator is not a forward.");
            Derived res = this->derived().Clone();
            ++_current;
            return res;
        }

        // Bidirectional iterator requirements
        Derived &operator--() noexcept // pre
        {
            static_assert(IsBidirectionalIt, "pre-decrement operator: iterator is not bidirectional iterator.");
            --_current;
            return *static_cast<Derived *>(this);
        }
        Derived operator--(int) noexcept // post
        {
            static_assert(IsBidirectionalIt, "post-decrement operator: iterator is not bidirectional iterator.");
            Derived res = this->derived().Clone();
            --_current;
            return res;
        }

        // Random access iterator requirements
        value_type operator[](difference_type n) const // rather than reference
        {
            static_assert(IsRandomAccessIt, "operator[]: iterator is not a random access.");
            return _current[n];
        }
        Derived &operator+=(difference_type n) noexcept
        {
            static_assert(IsRandomAccessIt, "operator+=: iterator is not a random access.");
            _current += n;
            return *static_cast<Derived *>(this);
        }
        Derived operator+(difference_type n) const noexcept
        {
            static_assert(IsRandomAccessIt, "operator+: iterator is not a random access.");
            Derived res = this->derived().Clone();
            res.Base() += n;
            return res;
        }
        Derived &operator-=(difference_type n) noexcept
        {
            static_assert(IsRandomAccessIt, "operator-=: iterator is not a random access.");
            _current -= n;
            return *static_cast<Derived *>(this);
        }
        Derived operator-(difference_type n) const noexcept
        {
            static_assert(IsRandomAccessIt, "operator-: iterator is not a random access.");
            Derived res = this->derived().Clone();
            res.Base() -= n;
            return res;
        }

    protected:
        It _current;
    };

    template <typename Derived>
    inline typename Iterator<Derived>::difference_type operator-(const Iterator<Derived> &lhs, const Iterator<Derived> &rhs) noexcept { return lhs.Base() - rhs.Base(); }

    template <typename Derived>
    inline bool operator==(const Iterator<Derived> &lhs, const Iterator<Derived> &rhs) noexcept { return lhs.Base() == rhs.Base(); }

    template <typename Derived>
    inline bool operator!=(const Iterator<Derived> &lhs, const Iterator<Derived> &rhs) noexcept { return lhs.Base() != rhs.Base(); }
} // namespace Lincpp

// SelectIterator<WhereIterator>> &SelectIterator<WhereIterator>>::operator=(const Lincpp::SelectIterator<Lincpp::WhereIterator<__gnu_cxx::__normal_iterator<int *, std::vector<int>>, main()::<lambda(int)>>, main()::<lambda(int)>, double> &)
