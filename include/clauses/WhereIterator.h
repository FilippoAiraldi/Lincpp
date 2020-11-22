#pragma once

namespace Lincpp
{
    template <typename It, typename TPred>
    struct WhereIterator : public Iterator<It>
    {
    public:
        // what are the limitations of forcing the category to forward iterator?
        typedef typename std::forward_iterator_tag iterator_category;
        typedef typename std::iterator_traits<It>::difference_type difference_type;
        typedef typename std::iterator_traits<It>::value_type value_type;
        typedef typename std::iterator_traits<It>::reference reference;
        typedef typename std::iterator_traits<It>::pointer pointer;

        explicit WhereIterator(It iterator, It end, TPred predicate) noexcept : Iterator<It>(iterator), _end(end), _pred(predicate)
        {
            CHECK_PREDICATE(TPred, value_type);

            // prime iterator to the first that passes predicate
            MoveIterator(this->_current, this->_end, this->_pred);
        }

        // Forward iterator requirements
        reference operator*()
        {
            MoveIterator(this->_current, this->_end, this->_pred);
            return *this->_current;
        }
        WhereIterator<It, TPred> &operator++() noexcept // pre
        {
            ++(this->_current);
            MoveIterator(this->_current, this->_end, this->_pred);
            return *this;
        }
        WhereIterator<It, TPred> operator++(int) noexcept // post
        {
            It res = this->_current;
            ++(this->_current);
            MoveIterator(this->_current, this->_end, this->_pred);
            return WhereIterator<It, TPred>(res, _end, _pred);
        }

        // Bidirectional iterator requirements
        // Random access iterator requirements

    private:
        It _end;
        TPred _pred;

        void MoveIterator(It &it, const It &end, TPred predicate)
        {
            while (it != end && !predicate(*it))
                ++it;
        }
    };
} // namespace Lincpp
