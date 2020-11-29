#pragma once

namespace Lincpp
{
    namespace internal
    {
        template <typename It>
        struct category_resolver
        {
            using _category = typename std::iterator_traits<It>::iterator_category;
            typedef std::conditional_t<
                std::is_base_of_v<std::bidirectional_iterator_tag, _category>,
                std::bidirectional_iterator_tag,
                std::forward_iterator_tag>
                iterator_category;
        };

        // specialization used by base Iterator struct to get traits of derived
        template <typename It, typename TPred>
        struct traits<WhereIterator<It, TPred>>
        {
            typedef It iterator_type;
            typedef typename internal::category_resolver<It>::iterator_category iterator_category;
            typedef typename std::iterator_traits<It>::difference_type difference_type;
            typedef typename std::iterator_traits<It>::value_type value_type;
            typedef typename std::iterator_traits<It>::reference reference;
            typedef typename std::iterator_traits<It>::pointer pointer;
        };
    } // namespace internal

    template <typename It, typename TPred>
    struct WhereIterator : public Iterator<WhereIterator<It, TPred>>
    {
    private:
        typedef Iterator<WhereIterator<It, TPred>> Base;

    public:
        typedef typename internal::category_resolver<It>::iterator_category iterator_category;
        typedef typename std::iterator_traits<It>::difference_type difference_type;
        typedef typename std::iterator_traits<It>::value_type value_type;
        typedef typename std::iterator_traits<It>::reference reference;
        typedef typename std::iterator_traits<It>::pointer pointer;

        explicit WhereIterator(It iterator, It begin, It end, TPred predicate) noexcept
            : Iterator<WhereIterator<It, TPred>>(iterator), _begin(begin), _end(end), _pred(predicate)
        {
            CHECK_PREDICATE(TPred, value_type);
            // prime iterator to the first that passes predicate
            IncrementWhile(this->_current, this->_end, this->_pred);
        }

        // necessary to provide this method for base Iterator struct
        WhereIterator<It, TPred> Clone() const
        {
            return WhereIterator<It, TPred>(this->_current, this->_begin, this->_end, this->_pred);
        }

        // necessary to provide this operator for base Iterator struct
        WhereIterator<It, TPred> &operator=(const WhereIterator<It, TPred> &other)
        {
            this->_begin = other._begin;
            this->_end = other._end;
            this->_current = other._current;
            // this->_pred = other._pred; // cannot copy lambda, but should be equal anyway
            return *this;
        };

        // Forward iterator requirements
        reference operator*()
        {
            IncrementWhile(this->_current, this->_end, this->_pred);
            return *this->_current;
        }
        WhereIterator<It, TPred> &operator++() noexcept // pre
        {
            static_assert(Base::IsForwardIt, "pre-increment operator: iterator is not a forward.");
            if (this->_current == this->_end)
                return *this;
            ++(this->_current);
            IncrementWhile(this->_current, this->_end, this->_pred);
            return *this;
        }
        WhereIterator<It, TPred> operator++(int) noexcept // post
        {
            static_assert(Base::IsForwardIt, "post-increment operator: iterator is not a forward.");
            It res = this->_current;
            if (this->_current == this->_end)
                return res;
            ++(this->_current);
            IncrementWhile(this->_current, this->_end, this->_pred);
            return WhereIterator<It, TPred>(res, _end, _pred);
        }

        // Bidirectional iterator requirements
        WhereIterator<It, TPred> &operator--() noexcept // pre
        {
            static_assert(Base::IsBidirectionalIt, "pre-decrement operator: iterator is not bidirectional iterator.");
            if (this->_current == this->_begin)
                return *this;
            --(this->_current);
            DecrementWhile(this->_current, this->_begin, this->_pred);
            return *this;
        }
        WhereIterator<It, TPred> operator--(int) noexcept // post
        {
            static_assert(Base::IsBidirectionalIt, "pre-decrement operator: iterator is not bidirectional iterator.");
            It res = this->_current;
            if (this->_current == this->_begin)
                return res;
            --(this->_current);
            DecrementWhile(this->_current, this->_begin, this->_pred);
            return WhereIterator<It, TPred>(res, _end, _pred);
        }

    private:
        It _begin;
        It _end;
        const TPred _pred;

        static void IncrementWhile(It &it, const It &end, TPred predicate)
        {
            while (it != end && !predicate(*it))
                ++it;
        }

        static void DecrementWhile(It &it, const It &begin, TPred predicate)
        {
            while (it != begin && !predicate(*it))
                --it;
            // if (it == begin)
            //     --it; // an additional push to make it invalid
        }
    };
} // namespace Lincpp
