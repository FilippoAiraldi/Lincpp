#pragma once

namespace Lincpp
{
    namespace internal
    {
        template <typename Iter>
        Iter MoveImpl(Iter begin, Iter end, Iter iter, typename std::iterator_traits<Iter>::difference_type n = 1) noexcept requires std::input_iterator<Iter>
        {
            if (n != 0)
            {
                iter = n > 0
                           ? IncrementIteratorImpl<Iter>(begin, end, iter, n)
                           : DecrementIteratorImpl<Iter>(begin, end, iter, -n);
            }
            return iter;
        }

        template <typename Iter>
        static Iter IncrementIteratorImpl(Iter, Iter end, Iter iter, std::size_t n) noexcept requires std::random_access_iterator<Iter>
        {
#ifdef LINCPP_DEBUG
            if (n >= static_cast<std::size_t>(std::distance(iter, end)))
                return end;
#endif
            return iter + n;
        }

        template <typename Iter>
        static Iter IncrementIteratorImpl(Iter, Iter end, Iter iter, std::size_t n) noexcept requires std::input_iterator<Iter>
        {
            while (n != 0)
            {
                n--;
                iter++;
#ifdef LINCPP_DEBUG
                if (iter == end)
                    return end;
#endif
            }
            return iter;
        }

        template <typename Iter>
        static Iter DecrementIteratorImpl(Iter begin, Iter, Iter iter, std::size_t n) noexcept requires std::random_access_iterator<Iter>
        {
#ifdef LINCPP_DEBUG
            if (n > static_cast<std::size_t>(std::distance(begin, iter)))
                return begin;
#endif
            return iter - n;
        }

        template <typename Iter>
        static Iter DecrementIteratorImpl(Iter begin, Iter, Iter iter, std::size_t n) noexcept requires std::bidirectional_iterator<Iter>
        {
            while (n != 0)
            {
                n--;
                iter--;
#ifdef LINCPP_DEBUG
                if (i == begin)
                    return begin;
#endif
            }
            return iter;
        }

        template <typename Iter>
        static Iter DecrementIteratorImpl(Iter begin, Iter, Iter iter, std::size_t n) noexcept requires std::input_iterator<Iter>
        {
            auto L = (std::size_t)std::distance(begin, iter);
#ifdef LINCPP_DEBUG
            if (n >= L)
                return begin;
#endif
            while (n != L)
            {
                begin++;
                n++;
            }
            return begin;
        }
    } // namespace internal

    // https://en.cppreference.com/w/cpp/iterator/iterator
    // https://stackoverflow.com/questions/9386266/overloading-the-operator-to-increment-an-iterator

    /*
    Base class for all Lincpp iterators that exposes various operators on inner base iterator.
    As minimum requirement, base iterator must be incrementable and dereferenciable.
    */
    template <typename Derived>
    struct QueriableIterator
    {
    public:
        typedef std::iterator_traits<Derived>::iterator_category iterator_category;
        typedef std::iterator_traits<Derived>::difference_type difference_type;
        typedef std::iterator_traits<Derived>::value_type value_type;
        typedef std::iterator_traits<Derived>::reference reference;
        typedef std::iterator_traits<Derived>::pointer pointer;

        QueriableIterator(Derived begin, Derived end, Derived iterator) : begin(begin), end(end), iter(iterator) {}
        QueriableIterator(const QueriableIterator<Derived> &) = default;

        reference operator*() const { return *iter; }
        bool operator==(QueriableIterator<Derived> other) const { return iter == other.iter; }
        bool operator!=(QueriableIterator<Derived> other) const { return iter != other.iter; }
        bool operator==(Derived other) const { return iter == other; }
        bool operator!=(Derived other) const { return iter != other; }

        QueriableIterator<Derived> &operator++() noexcept // pre
        {
            iter = MoveImpl(begin, end, iter, 1);
            return *this;
        }
        QueriableIterator<Derived> operator++(int) noexcept // post
        {
            QueriableIterator<Derived> res = *this;
            iter = MoveImpl(begin, end, iter, 1);
            return res;
        }

        QueriableIterator<Derived> &operator--() noexcept // pre
        {
            iter = MoveImpl(begin, end, iter, -1);
            return *this;
        }
        QueriableIterator<Derived> operator--(int) noexcept // post
        {
            QueriableIterator<Derived> res = *this;
            iter = MoveImpl(begin, end, iter, -1);
            return res;
        }
        // QueriableIterator<Derived> &operator+=(difference_type n) noexcept
        // {
        //     iter = MoveImpl(begin, end, iter, n);
        //     return *this;
        // }
        // QueriableIterator<Derived> operator+(difference_type n) const noexcept
        // {
        //     return QueriableIterator<Derived>(begin, end, MoveImpl(begin, end, iter, n));
        // }
        // QueriableIterator<Derived> &operator-=(difference_type n) noexcept
        // {
        //     iter = MoveImpl(begin, end, iter, -n);
        //     return *this;
        // }
        // QueriableIterator<Derived> operator-(difference_type n) const noexcept
        // {
        //     return QueriableIterator<Derived>(begin, end, MoveImpl(begin, end, iter, -n));
        // }

    protected:
        Derived begin, end, iter;

    private:
        QueriableIterator() = delete;
    };

    template <typename Derived>
    static QueriableIterator<Derived> MakeQueriableIterator(Derived begin, Derived end, Derived iterator)
    {
        return QueriableIterator<Derived>(begin, end, iterator);
    }
} // namespace Lincpp
