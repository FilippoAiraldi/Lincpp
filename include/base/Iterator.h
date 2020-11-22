#pragma once

namespace Lincpp
{
    // https://en.cppreference.com/w/cpp/iterator/iterator
    // https://stackoverflow.com/questions/9386266/overloading-the-operator-to-increment-an-iterator

    // 1. make Iterator take a "Derived" template, so that it can static cast *this to Derived
    // 2. put It typename inside the traits, cleaner than passing it as a template
    //      2.1. requires ForwardDeclarations
    //      2.2. requires use of traits
    // 3. In each derived class, create a common interface MakeIterator function that creates
    //      a new iterator from an original iterator

    template <typename It>
    struct Iterator /* : public std::iterator<typename std::iterator_traits<It>::iterator_category,
                                           typename std::iterator_traits<It>::value_type,
                                           typename std::iterator_traits<It>::difference_type,
                                           typename std::iterator_traits<It>::pointer,
                                           typename std::iterator_traits<It>::reference> */
    {
    public:
        // std::iterator deprecated
        typedef typename std::iterator_traits<It>::iterator_category iterator_category;
        typedef typename std::iterator_traits<It>::difference_type difference_type;
        typedef typename std::iterator_traits<It>::value_type value_type;
        typedef typename std::iterator_traits<It>::reference reference;
        typedef typename std::iterator_traits<It>::pointer pointer;

        explicit Iterator(It iterator) noexcept : _current(iterator) {}

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
    inline Iterator<It>::difference_type operator-(const Iterator<It> &lhs, const Iterator<It> &rhs) noexcept { return lhs.base() - rhs.base(); }

    template <typename It>
    inline bool operator==(const Iterator<It> &lhs, const Iterator<It> &rhs) noexcept { return lhs.base() == rhs.base(); }

    template <typename It>
    inline static Iterator<It> MakeIterator(It iterator) { return Iterator<It>(iterator); }
} // namespace Lincpp
