#pragma once

namespace Lincpp
{
    template <typename It, typename TFunc, typename TReturn>
    struct SelectIterator : public Iterator<It>
    {
    public:
        typedef typename std::iterator_traits<It>::iterator_category iterator_category;
        typedef typename std::iterator_traits<It>::difference_type difference_type;
        typedef TReturn value_type;
        typedef TReturn &reference;
        typedef TReturn *pointer;
        typedef typename std::iterator_traits<It>::value_type TInput;

        explicit SelectIterator(It iterator, TFunc selector) noexcept : Iterator<It>(iterator), _func(selector)
        {
            CHECK_FUNC(TFunc, TInput, TReturn);
        }

        // Forward iterator requirements
        value_type operator*() { return this->_func(*(this->_current)); }

        // Bidirectional iterator requirements
        // Random access iterator requirements

    private:
        TFunc _func;
    };
} // namespace Lincpp
