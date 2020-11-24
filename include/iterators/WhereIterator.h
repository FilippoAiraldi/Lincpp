#pragma once

namespace Lincpp
{
    namespace internal
    {
        template <typename It, typename TPred>
        struct traits<WhereIterator<It, TPred>>
        {
            typedef It iterator_type;
            typedef typename std::forward_iterator_tag iterator_category;
            typedef typename std::iterator_traits<It>::difference_type difference_type;
            typedef typename std::iterator_traits<It>::value_type value_type;
            typedef typename std::iterator_traits<It>::reference reference;
            typedef typename std::iterator_traits<It>::pointer pointer;
        };
    } // namespace internal

    template <typename It, typename TPred>
    struct WhereIterator : public Iterator<WhereIterator<It, TPred>>
    {
    public:
        typedef typename std::forward_iterator_tag iterator_category;
        typedef typename std::iterator_traits<It>::difference_type difference_type;
        typedef typename std::iterator_traits<It>::value_type value_type;
        typedef typename std::iterator_traits<It>::reference reference;
        typedef typename std::iterator_traits<It>::pointer pointer;

        explicit WhereIterator(It iterator, It end, TPred predicate) noexcept : Iterator<WhereIterator<It, TPred>>(iterator), _end(end), _pred(predicate)
        {
            CHECK_PREDICATE(TPred, value_type);
            // prime iterator to the first that passes predicate
            IncrementWhile(this->_current, this->_end, this->_pred);
        }

        WhereIterator<It, TPred> Clone() const { return WhereIterator<It, TPred>(this->_current, this->_end, this->_pred); }

        WhereIterator<It, TPred> &operator=(const WhereIterator<It, TPred> &other)
        {
            this->_current = other._current;
            this->_end = other._end;
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
            ++(this->_current);
            IncrementWhile(this->_current, this->_end, this->_pred);
            return *this;
        }
        WhereIterator<It, TPred> operator++(int) noexcept // post
        {
            It res = this->_current;
            ++(this->_current);
            IncrementWhile(this->_current, this->_end, this->_pred);
            return WhereIterator<It, TPred>(res, _end, _pred);
        }

        // Bidirectional iterator requirements
        // Random access iterator requirements

    private:
        It _end;
        const TPred _pred;

        static void IncrementWhile(It &it, const It &end, TPred predicate)
        {
            while (it != end && !predicate(*it))
                ++it;
        }
    };
} // namespace Lincpp
