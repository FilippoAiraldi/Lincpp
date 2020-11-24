#pragma once

namespace Lincpp
{
    /*
    Each derived class must provide its own copy assignment operator.
    Moreover, it can provide its own other operators to accomplish
    its purpose.
    */

    // https://en.cppreference.com/w/cpp/iterator/iterator
    // https://stackoverflow.com/questions/9386266/overloading-the-operator-to-increment-an-iterator

    template <typename It>
    struct Iterator
    {
    public:
        typedef typename std::iterator_traits<It>::iterator_category iterator_category;
        typedef typename std::iterator_traits<It>::difference_type difference_type;
        typedef typename std::iterator_traits<It>::value_type value_type;
        typedef typename std::iterator_traits<It>::reference reference;
        typedef typename std::iterator_traits<It>::pointer pointer;

        explicit Iterator(It iterator) noexcept : _current(iterator) {}
        Iterator<It> &operator=(const Iterator<It> &other) { _current = other._current; };

        inline const It &base() const noexcept { return _current; }

        // Forward iterator requirements
        pointer operator->() const { return _current.operator->(); }
        value_type operator*() const { return *_current; } // rather than reference
        Iterator<It> &operator++() noexcept                // pre
        {
            ++_current;
            return *this;
        }
        Iterator<It> operator++(int) noexcept // post
        {
            It res = _current;
            ++_current;
            return Iterator<It>(res);
        }

        // Bidirectional iterator requirements
        value_type operator[](difference_type n) const // rather than reference
        {
            return _current[n];
        }
        Iterator<It> &operator--() noexcept // pre
        {
            --_current;
            return *this;
        }
        Iterator<It> operator--(int) noexcept // post
        {
            It res = _current;
            --_current;
            return Iterator<It>(res);
        }

        // Random access iterator requirements
        Iterator<It> &operator+=(difference_type n) noexcept
        {
            _current += n;
            return *this;
        }
        Iterator<It> operator+(difference_type n) const noexcept
        {
            return Iterator<It>(_current + n);
        }
        Iterator<It> &operator-=(difference_type n) noexcept
        {
            _current -= n;
            return *this;
        }
        Iterator<It> operator-(difference_type n) const noexcept
        {
            return Iterator<It>(_current - n);
        }

    protected:
        It _current;
    };

    template <typename It>
    inline typename Iterator<It>::difference_type operator-(const Iterator<It> &lhs, const Iterator<It> &rhs) noexcept { return lhs.base() - rhs.base(); }

    template <typename It>
    inline bool operator==(const Iterator<It> &lhs, const Iterator<It> &rhs) noexcept { return lhs.base() == rhs.base(); }

    template <typename It>
    inline bool operator!=(const Iterator<It> &lhs, const Iterator<It> &rhs) noexcept { return lhs.base() != rhs.base(); }

    template <typename It>
    inline static Iterator<It> MakeIterator(It iterator) { return Iterator<It>(iterator); }
} // namespace Lincpp

// SelectIterator<WhereIterator>> &SelectIterator<WhereIterator>>::operator=(const Lincpp::SelectIterator<Lincpp::WhereIterator<__gnu_cxx::__normal_iterator<int *, std::vector<int>>, main()::<lambda(int)>>, main()::<lambda(int)>, double> &)