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
        // typedef typename std::iterator_traits<It>::iterator_category iterator_category;
        // typedef typename std::iterator_traits<It>::difference_type difference_type;
        // typedef typename std::iterator_traits<It>::value_type value_type;
        // typedef typename std::iterator_traits<It>::reference reference;
        // typedef typename std::iterator_traits<It>::pointer pointer;
        // typedef typename internal::traits<Derived>::iterator_category iterator_category;
        typedef typename internal::traits<Derived>::iterator_type It;
        typedef typename internal::traits<Derived>::iterator_category iterator_category;
        typedef typename internal::traits<Derived>::difference_type difference_type;
        typedef typename internal::traits<Derived>::value_type value_type;
        typedef typename internal::traits<Derived>::reference reference;
        typedef typename internal::traits<Derived>::pointer pointer;

    protected:
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
            ++_current;
            return *static_cast<Derived *>(this);
        }
        Derived operator++(int) noexcept // post
        {
            Derived res = this->derived().Clone();
            ++_current;
            return res;
        }

        // Bidirectional iterator requirements
        value_type
        operator[](difference_type n) const // rather than reference
        {
            return _current[n];
        }
        Derived &operator--() noexcept // pre
        {
            --_current;
            return *static_cast<Derived *>(this);
        }
        Derived operator--(int) noexcept // post
        {
            Derived res = this->derived().Clone();
            --_current;
            return res;
        }

        // Random access iterator requirements
        Derived &operator+=(difference_type n) noexcept
        {
            _current += n;
            return *static_cast<Derived *>(this);
        }
        Derived operator+(difference_type n) const noexcept
        {
            Derived res = this->derived().Clone();
            res.Base() += n;
            return res;
        }
        Derived &operator-=(difference_type n) noexcept
        {
            _current -= n;
            return *static_cast<Derived *>(this);
        }
        Iterator<Derived> operator-(difference_type n) const noexcept
        {
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
